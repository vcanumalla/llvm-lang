#ifndef __VARIABLE_EXPR_AST_H__
#define __VARIABLE_EXPR_AST_H__

#include <string>
#include "./ExprAST.h"

class VariableExprAST : public ExprAST {
  std::string name_;
 public:
  VariableExprAST(const std::string& name) : name_(name) {};
};

#endif