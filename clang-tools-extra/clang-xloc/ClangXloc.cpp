// ===---- ClangXloc.cpp - clang-tool demo --------------===//
//
// ===---------------------------------------------------===//


#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Error.h"

using namespace clang;
using CommonOptionsParser = clang::tooling::CommonOptionsParser;
using ClangTool = clang::tooling::ClangTool;

static llvm::cl::OptionCategory ClangXlocCategory("clang-xloc options");

int main(int argc, const char **argv) {
    llvm::Expected<CommonOptionsParser> OptionsParser =
	CommonOptionsParser::create(argc, argv, ClangXlocCategory,
			            llvm::cl::OneOrMore);
    
    if (!OptionsParser) {
	llvm::errs() << llvm::toString(OptionsParser.takeError());
	return 1;
    }

    ClangTool Tool(OptionsParser->getCompilations(),
		   OptionsParser->getSourcePathList());

    return 0;
}

