#ifndef __BINARY_EXPR_AST__
#define __BINARY_EXPR_AST__

#include "./ExprAST.h"
#include <memory>

class BinaryExprAST : public ExprAST {
  char op_;
  std::unique_ptr<ExprAST> lhs_, rhs_;
 public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs) : 
      op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
};

#endif