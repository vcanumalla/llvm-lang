#ifndef PARSER
#define PARSER

#include "./ast.h" 

static int CurTok;
static int getNextToken();

unique_ptr<ExprAST> logError(const char *Str);
unique_ptr<PrototypeAST> logErrorP(const char *Str);
static std::unique_ptr<ExprAST> ParseNumberExpr();

#endif
