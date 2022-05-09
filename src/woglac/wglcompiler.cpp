// Must place before everything else because of antlr
#include "supp/wglinclude.h"

#include <fstream>
#include <format>

#include "util/iterators.h"

#include "wglcompiler.h"

#include "supp/wglmodule.h"
#include "supp/wglcontext.h"
#include "supp/wglerror.h"
#include "supp/wgldeclarationpass.h"
#include "supp/wglimplementationpass.h"

class ANTLRErrorHandler : public antlr4::BaseErrorListener {
	virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override {
		throw WGLError(std::format("Syntax error: {} on line {} ({})", msg.c_str(), line, charPositionInLine), nullptr);
	}
};


WGLCompiler::WGLCompiler() {
	context_ = std::make_unique<WGLContext>();
	context_->compiler = this;

	openSteamFunction_ = [this](const std::string &filename, antlr4::ParserRuleContext *ctx) -> std::unique_ptr<std::istream> {
		std::string file = lookupFile(filename, ctx);

		auto f = std::make_unique<std::ifstream>();
		f->open(file, std::ios::in | std::ios::binary);

		if(!f->good())
			throw std::exception(std::format("Could not open VOX file '{}' for reading.", file).c_str());

		return f;
	};
}

void WGLCompiler::clear() {
	modules_.clear();
	context_->clear();
}

void WGLCompiler::addFile(const std::string &file) {
	files_.push_back(file);
}

std::string WGLCompiler::lookupFile(const std::string &filename, antlr4::ParserRuleContext *ctx) {
	for(const std::string &dirn: lookupDirectories_) {
		const std::string filePath = dirn + "/" + filename;
		if(std::ifstream f(filePath); f.good())
			return filePath;
	}

	throw WGLError(std::format("Failed to lookup file '{}' in directories:\n{}", filename, iterator(lookupDirectories_).join('\n')), ctx);
}

std::unique_ptr<std::istream> WGLCompiler::getFileStream(const std::string &filename, antlr4::ParserRuleContext *ctx) {
	if (openSteamFunction_ == nullptr)
		throw std::exception("Stream function not set !");

	return openSteamFunction_(filename, ctx);
}

void WGLCompiler::compile() {
	clear();

	try {

		// Parse files
		for(const std::string &s: files_) {
			try {
				auto m = std::make_shared<WGLModule>();
				m->stream = getFileStream(s, nullptr);

				m->input.reset(new antlr4::ANTLRInputStream(*m->stream));
				m->lexer.reset(new WoglacLexer(m->input.get()));
				m->tokens.reset(new antlr4::CommonTokenStream(m->lexer.get()));
				m->parser.reset(new WoglacParser(m->tokens.get()));

				m->parser->setBuildParseTree(true);
				m->parser->getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::SLL);

				ANTLRErrorHandler errHandler;
				m->parser->removeErrorListeners();
				m->parser->addErrorListener(&errHandler);
				m->ast = m->parser->module();

				modules_.push_back(m);
			}
			catch(const WGLError &e) {
				throw std::exception(std::format("Error when compiling WOGLAC source '{}': {}", s, e.message()).c_str());
			}
		}

		// Declaration pass
		{
			WGLDeclarationPass dps;
			dps.setContext(context_.get());

			for(auto &m: modules_)
				dps.execute(m->ast);
		}

		// Implementation pass
		{
			WGLImplementationPass ips;
			ips.setContext(context_.get());

			for(auto &m: modules_)
				ips.execute(m->ast);
		}

		context_->checkCircularDependencies();
	}
	catch(const WGLError &e) {
		throw std::exception(std::format("WOGLAC error: {}", e.message()).c_str());
	}
}

std::unordered_map<std::string, WGA_Value *> WGLCompiler::construct(WorldGenAPI &api) {
	WGLAPIContext ctx;
	ctx.api = &api;

	for(const auto &cmd: context_->apiCommands())
		cmd(ctx);

	std::unordered_map<std::string, WGA_Value *> r;
	for(const auto &i: context_->rootSymbol->childrenByName()) {
		const WGLSymbol *sym = i.second;

		if(!sym->isExport)
			continue;

		if(sym->symbolType() != WGLSymbol::Type::FieldVariable)
			continue;

		r[sym->name()] = ctx.map<WGA_Value>(sym);
	}

	return r;
}
