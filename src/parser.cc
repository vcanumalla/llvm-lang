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
  getNextToken();
  return std::make_unique<CallExprAST>(idName, std::move(args));
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

static int getTokPrecedence() {
  if (!isascii(CurTok)) {
    return -1;
  }
  int tokPrec = binopPrecedence[CurTok];
  if (tokPrec <= 0) {
    return -1;
  }
  return tokPrec;

}

static unique_ptr<ExprAST> parseExpression() {
  auto lhs = parsePrimary();
  if (!lhs) return nullptr;
  return parseBinOpRHS(0, std::move(lhs));
}

static unique_ptr<ExprAST> parseBinOpRHS(int exprPrec,
    unique_ptr<ExprAST> lhs) {
      while (true) {
        int tokPrec = getTokPrecedence();
        // if the precedence is lower, evaluate the lower
        if (tokPrec < exprPrec) {
          return lhs;
        }
        int binOp = CurTok;
        getNextToken();

        auto rhs = parsePrimary();
        if (!rhs) {
          return nullptr;
        }

        int nextPrec = getTokPrecedence();
        if (tokPrec < nextPrec) {
          rhs = parseBinOpRHS(tokPrec+1, std::move(rhs));
          if (!rhs) {
            return nullptr;
          }
        }
        lhs = std::make_unique<BinaryExprAST>(binOp, std::move(lhs), 
            std::move(rhs));
        
      }
}

static unique_ptr<PrototypeAST> parsePrototype() {
  if (CurTok != tok_identifier) {
    return logErrorP("Expected function name in prototype");
  }

  string fnName = IdentifierStr;
  getNextToken();

  if (CurTok != '(') {
    return logErrorP("Expected '(' in prototype");
  }
  vector<string> argNames;

  while (getNextToken() == tok_identifier) {
    argNames.push_back(IdentifierStr);
  }

  if (CurTok != ')') {
    return logErrorP("Expected ')' in prototype");
  }

  getNextToken();

  return std::make_unique<PrototypeAST>(fnName, std::move(argNames));
}

static unique_ptr<FunctionAST> parseDefinition() {
  getNextToken();
  auto proto = parsePrototype();
  if (!proto) {
    return nullptr;
  }
  if (auto E = parseExpression()) {
    return std::make_unique<FunctionAST>(std::move(proto), std::move(E));
  }
  return nullptr;
}

static std::unique_ptr<PrototypeAST> parseExtern() {
  getNextToken();
  return parsePrototype();
}

static std::unique_ptr<FunctionAST> parseTopLevelExpr() {
  if (auto E = parseExpression()) {
    auto proto = std::make_unique<PrototypeAST>("__anon_expr", vector<string>());
    return std::make_unique<FunctionAST>(std::move(proto), std::move(E));
  }
  return nullptr;
}

void handleDefinition() {
  if (parseDefinition()) {
    fprintf(stderr, "Parsed a function definition.\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

void handleExtern() {
  if (parseExtern()) {
    fprintf(stderr, "Parsed an extern\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

void handleTopLevelExpression() {
  // Evaluate a top-level expression into an anonymous function.
  if (parseTopLevelExpr()) {
    fprintf(stderr, "Parsed a top-level expr\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}