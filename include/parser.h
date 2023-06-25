#ifndef PARSER
#define PARSER

#include "./ast.h" 

static int CurTok;
static int getNextToken();
using std::unique_ptr;

unique_ptr<ExprAST> logError(const char *Str);
unique_ptr<PrototypeAST> logErrorP(const char *Str);
static unique_ptr<ExprAST> parseNumberExpr();
static unique_ptr<ExprAST> parseExpression();
static unique_ptr<ExprAST> parseParenExpr();
static unique_ptr<ExprAST> parseIdentifierExpr();
static unique_ptr<ExprAST> parsePrimary();

#endif
