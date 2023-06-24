#include "../include/parser.h"
#include "../include/lexer.h"

int getNextToken() {
  return CurTok = gettok();
}

unique_ptr<ExprAST> logError(const char *Str) {
  fprintf(stderr, "Error; %s\n", Str);
  return nullptr;
}

unique_ptr<PrototypeAST> logErrorP(const char *Str) {
  logError(Str);
  return nullptr;
}

// parse every type of expr

// called when curToken is a number token
static std::unique_ptr<ExprAST> ParseNumberExpr() {
  unique_ptr<NumberExprAST> result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken();
  return std::move(result);
}
