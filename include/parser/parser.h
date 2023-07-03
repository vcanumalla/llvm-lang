#ifndef __PARSER_H__
#define __PARSER_H__

#include "ast/ExprAST.h"
#include "ast/NumberExprAST.h"
#include "ast/VariableExprAST.h"
#include "ast/BinaryExprAST.h"
#include "ast/CallExprAST.h"
#include "ast/PrototypeAST.h"
#include "ast/FunctionAST.h"
#include "lexer/lexer.h"
#include "lexer/token.h"

#include<map>
#include<string>
#include<memory>
#include<vector>

extern std::map<char, int> binopPrecedence;
std::unique_ptr<ExprAST> parseNumberExpr();
std::unique_ptr<ExprAST> parseParenExpr();
std::unique_ptr<ExprAST> parseIdentifierExpr();
std::unique_ptr<ExprAST> parsePrimary();
std::unique_ptr<ExprAST> parseExpression();
std::unique_ptr<ExprAST> parseBinOpRHS(int exprPrec,
    std::unique_ptr<ExprAST> LHS);
std::unique_ptr<PrototypeAST> parsePrototype();
std::unique_ptr<FunctionAST> parseDefinition();
std::unique_ptr<PrototypeAST> parseExtern();
std::unique_ptr<FunctionAST> parseTopLevelExpr();

#endif