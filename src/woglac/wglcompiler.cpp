// Must place before everything else because of antlr
#include "supp/wglinclude.h"

#include <QDir>
#include <QFile>

#include "wglcompiler.h"

#include "supp/wglmodule.h"
#include "supp/wglcontext.h"
#include "supp/wglerror.h"
#include "supp/wgldeclarationpass.h"
#include "supp/wglimplementationpass.h"

class ANTLRErrorHandler : public antlr4::BaseErrorListener {
	virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override {
		Q_UNUSED(recognizer)
		Q_UNUSED(offendingSymbol)
		Q_UNUSED(e)
		Q_UNUSED(charPositionInLine);
		throw WGLError(std::format("Syntax error: {} on line {} ({})", msg.c_str(), line, charPositionInLine), nullptr);
	}
};


WGLCompiler::WGLCompiler() {
	context_ = std::make_unique<WGLContext>();
	context_->compiler = this;
}

void WGLCompiler::clear() {
	modules_.clear();
	context_->clear();
}

void WGLCompiler::addFile(const WGLFilePtr &file) {
	files_.push_back(file);
}

QString WGLCompiler::lookupFile(const std::string &filename, antlr4::ParserRuleContext *ctx) {
	for(const QString &dirn: lookupDirectories_) {
		if(ifstream f(dirn + "/" + filename); f.good())
			return f.fileName();
	}

	throw WGLError(std::format("Failed to lookup file '{}'", filename), ctx);
}

void WGLCompiler::compile() {
	clear();

	try {

		// Parse files
		for(const WGLFilePtr &f: files_) {
			try {
				auto m = std::make_shared<WGLModule>();

				m->stream.reset(new std::ifstream());
				m->stream->open(f->fileName(), std::ifstream::in);
				if(!m->stream->is_open())
					throw WGLError(std::format("Error opening file '{}'", f->fileName()), nullptr);

				m->input.reset(new antlr4::ANTLRInputStream(*m->stream));
				m->lexer.reset(new WoglacLexer(m->input.data()));
				m->tokens.reset(new antlr4::CommonTokenStream(m->lexer.data()));
				m->parser.reset(new WoglacParser(m->tokens.data()));

				m->parser->setBuildParseTree(true);
				m->parser->getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::SLL);

				ANTLRErrorHandler errHandler;
				m->parser->removeErrorListeners();
				m->parser->addErrorListener(&errHandler);
				m->ast = m->parser->module();

				modules_.push_back(m);
			}
			catch(const WGLError &e) {
				throw std::exception(std::format("Error when compiling WOGLAC file '{}': {}", f->fileName(), e.message()));
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
		qWarning().noquote() << "WOGLAC error: " << e.message();

		clear();
	}
}

std::unordered_map<std::string, WGA_Value *> WGLCompiler::construct(WorldGenAPI &api) {
	WGLAPIContext ctx;
	ctx.api = &api;

	for(const auto &cmd: context_->apiCommands())
		cmd(ctx);

	std::unordered_map<std::string, WGA_Value *> r;
	for(WGLSymbol *sym: context_->rootSymbol->childrenByName()) {
		if(!sym->isExport)
			continue;

		if(sym->symbolType() != WGLSymbol::Type::FieldVariable)
			continue;

		r[sym->name()] = ctx.map<WGA_Value>(sym);
	}

	return r;
}
