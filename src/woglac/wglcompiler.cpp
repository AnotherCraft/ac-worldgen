// Must place before everything else because of antlr
#include "supp/wglinclude.h"

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
		throw WGLError(QStringLiteral("Syntax error: %1 on line %2 (%3)").arg(msg.c_str(), QString::number(line), QString::number(charPositionInLine)), nullptr);
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
	ASSERT(!files_.contains(file));
	files_ += file;
}

QString WGLCompiler::lookupFile(const QString &filename) {
	// TODO
	throw;
}

void WGLCompiler::compile() {
	clear();

	try {

		// Parse files
		for(const WGLFilePtr &f: files_) {
			try {
				QSharedPointer<WGLModule> m(new WGLModule());

				m->stream.reset(new std::ifstream());
				m->stream->open(f->fileName().toStdString(), std::ifstream::in);
				if(!m->stream->is_open())
					qWarning() << "Error opening file" << f->fileName();

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

				modules_ += m;
			}
			catch(const WGLError &e) {
				qWarning().noquote() << "Error when compiling WOGLAC file " << f->fileName() << ": " << e.message();

				clear();
				return;
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
