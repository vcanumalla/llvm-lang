#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "ast/ExprAST.h"
#include "ast/PrototypeAST.h"

std::unique_ptr<ExprAST> logError(const char *str);
std::unique_ptr<PrototypeAST> logErrorP(const char *str);


#endif