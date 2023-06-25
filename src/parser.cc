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
static unique_ptr<ExprAST> parseNumberExpr() {
  unique_ptr<NumberExprAST> result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken();
  return std::move(result);
}

static unique_ptr<ExprAST> parseParenExpr() {
  getNextToken();
  auto V = parseExpression();
  if (!V) return nullptr;
  if (CurTok != ')') return logError("expected ')'");
  getNextToken();
  return V;
}

static unique_ptr<ExprAST> parseIdentifierExpr() {
  // name of identifier parse
  string idName = IdentifierStr;
  getNextToken();
  if (CurTok != '(') {
    return std::make_unique<VariableExprAST>(idName);
  }

  // function call ast node
  getNextToken();
  std::vector<unique_ptr<ExprAST>> args;
  if (CurTok != ')') {
    while (true) {
      if (auto arg = parseExpression())
        args.push_back(std::move(arg));
      else
        return nullptr;

      if (CurTok == ')')
        break;

      if (CurTok != ',')
        return logError("Expected ')' or ',' in argument list");
      getNextToken();
    }
  }
}

static unique_ptr<ExprAST> parsePrimary() {
  switch (CurTok) {
    default:
      return logError("unknown token when expecting an expression");
    case tok_identifier:
      return parseIdentifierExpr();
    case tok_num:
      return parseNumberExpr();
    case '(':
      return parseParenExpr();
  }
}