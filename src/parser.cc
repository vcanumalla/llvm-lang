#include "parser/parser.h"
#include "logger/logger.h"
std::map<char, int> binopPrecedence;


std::unique_ptr<ExprAST> parseNumberExpr() {
  std::unique_ptr<NumberExprAST> result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken();
  return std::move(result);
}

std::unique_ptr<ExprAST> parseParenExpr() {
  getNextToken();
  auto V = parseExpression();
  if (!V) return nullptr;
  if (CurTok != ')') return logError("expected ')'");
  getNextToken();
  return V;
}

std::unique_ptr<ExprAST> parseIdentifierExpr() {
  // name of identifier parse
  std::string idName = IdentifierStr;
  getNextToken();
  if (CurTok != '(') {
    return std::make_unique<VariableExprAST>(idName);
  }

  // function call ast node
  getNextToken();
  std::vector<std::unique_ptr<ExprAST>> args;
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

std::unique_ptr<ExprAST> parsePrimary() {
  switch (CurTok) {
    default:
      return logError("unknown token when expecting an expression");
    case tok_identifier:
      return parseIdentifierExpr();
    case tok_number:
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

std::unique_ptr<ExprAST> parseExpression() {
  auto lhs = parsePrimary();
  if (!lhs) return nullptr;
  return parseBinOpRHS(0, std::move(lhs));
}

std::unique_ptr<ExprAST> parseBinOpRHS(int exprPrec,
    std::unique_ptr<ExprAST> lhs) {
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

std::unique_ptr<PrototypeAST> parsePrototype() {
  if (CurTok != tok_identifier) {
    return logErrorP("Expected function name in prototype");
  }

  std::string fnName = IdentifierStr;
  getNextToken();

  if (CurTok != '(') {
    return logErrorP("Expected '(' in prototype");
  }
  std::vector<std::string> argNames;

  while (getNextToken() == tok_identifier) {
    argNames.push_back(IdentifierStr);
  }

  if (CurTok != ')') {
    return logErrorP("Expected ')' in prototype");
  }

  getNextToken();

  return std::make_unique<PrototypeAST>(fnName, std::move(argNames));
}

std::unique_ptr<FunctionAST> parseDefinition() {
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

std::unique_ptr<PrototypeAST> parseExtern() {
  getNextToken();
  return parsePrototype();
}

std::unique_ptr<FunctionAST> parseTopLevelExpr() {
  if (auto E = parseExpression()) {
    auto proto = std::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>());
    return std::make_unique<FunctionAST>(std::move(proto), std::move(E));
  }
  return nullptr;
}