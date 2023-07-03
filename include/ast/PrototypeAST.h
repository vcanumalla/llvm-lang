#ifndef __PROTOTYPE_AST_H__
#define __PROTOTYPE_AST_H__

#include "./ExprAST.h"
#include <memory>
#include <string>
#include <vector>

class PrototypeAST {
  std::string name_;
  std::vector<std::string> args;
 public:
  PrototypeAST(const std::string& name, std::vector<std::string> args)
      : name_(name), args(std::move(args)) {}
  const std::string& getName() const {
    return name_;
  }
};

#endif