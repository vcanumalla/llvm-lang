#ifndef __CALL_EXPR_AST__
#define __CALL_EXPR_AST__

#include "./ExprAST.h"
#include <memory>
#include <string>
#include <vector>

class CallExprAST : public ExprAST {
  std::string callee_;
  std::vector<std::unique_ptr<ExprAST>> args_;
 public:
  CallExprAST(const std::string& callee, std::vector<std::unique_ptr<ExprAST>> args) : 
      callee_(callee), args_(std::move(args)) {}
};

#endif