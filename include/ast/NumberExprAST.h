#ifndef __NUMBER_EXPR_AST_H__
#define __NUMBER_EXPR_AST_H__

#include "./ExprAST.h"

class NumberExprAST : public ExprAST {
  double val_;
 public:
  NumberExprAST(double val) : val_(val) {};
};

#endif