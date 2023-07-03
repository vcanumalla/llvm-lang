#ifndef __FUNCTION_AST_H__
#define __FUNCTION_AST_H__

#include "./ExprAST.h"
#include "./PrototypeAST.h"
#include <memory>

class FunctionAST {
  std::unique_ptr<PrototypeAST> proto_;
  std::unique_ptr<ExprAST> body_;
 public:
  FunctionAST(std::unique_ptr<PrototypeAST> proto, 
      std::unique_ptr<ExprAST> body) : 
      proto_(std::move(proto)), body_(std::move(body)) {}
};
#endif
