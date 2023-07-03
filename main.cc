#include "parser/parser.h"
#include "lexer/lexer.h"
#include "lexer/token.h"

// AST headers
#include "ast/BinaryExprAST.h"
#include "ast/CallExprAST.h"
#include "ast/ExprAST.h"
#include "ast/FunctionAST.h"
#include "ast/NumberExprAST.h"
#include "ast/PrototypeAST.h"
#include "ast/VariableExprAST.h"

static void handleDefinition() {
  if (parseDefinition()) {
    fprintf(stderr, "Parsed a function definition.\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void handleExtern() {
  if (parseExtern()) {
    fprintf(stderr, "Parsed an extern\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void handleTopLevelExpression() {
  // Evaluate a top-level expression into an anonymous function.
  if (parseTopLevelExpr()) {
    fprintf(stderr, "Parsed a top-level expr\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void MainLoop() {
  while (true) {
    fprintf(stderr, "ready> ");
    switch (CurTok) {
    case tok_eof:
      return;
    case ';': // ignore top-level semicolons.
      getNextToken();
      break;
    case tok_def:
      handleDefinition();
      break;
    case tok_extern:
      handleExtern();
      break;
    default:
      handleTopLevelExpression();
      break;
    }
  }
}

int main() {
  binopPrecedence['<'] = 10;
  binopPrecedence['+'] = 20;
  binopPrecedence['-'] = 20;
  binopPrecedence['*'] = 40;
  fprintf(stderr, "ready> ");
  getNextToken();

  MainLoop();
  
  return 0;
}