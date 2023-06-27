#ifndef EXPR_AST
#define EXPR_AST

#include<string>
#include<memory>
#include<vector>

using std::string;
using std::unique_ptr;
using std::vector;

class ExprAST {
 public:
  virtual ~ExprAST() = default;
};

class NumberExprAST : public ExprAST {
  double val_;
 public:
  NumberExprAST(double val) : val_(val) {};
};

class VariableExprAST : public ExprAST {
  string name_;
 public:
  VariableExprAST(const string& name) : name_(name) {};
};

class BinaryExprAST : public ExprAST {
  char op_;
  unique_ptr<ExprAST> lhs_, rhs_;
 public:
  BinaryExprAST(char op, unique_ptr<ExprAST> lhs, unique_ptr<ExprAST> rhs) : 
      op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
};

class CallExprAST : public ExprAST {
  string callee_;
  vector<unique_ptr<ExprAST>> args;
 public:
  CallExprAST(const string& callee, vector<unique_ptr<ExprAST>> args) :
      callee_(callee), args(std::move(args)) {}
};

// a loose typing of functions based on number of arguments
class PrototypeAST {
  string name_;
  vector<string> args;
 public:
  PrototypeAST(const string& name, vector<string> args)
      : name_(name), args(std::move(args)) {}
  const string& getName() const {
    return name_;
  }
};

// Function is a combination of its prototype and its body
class FunctionAST {
  unique_ptr<PrototypeAST> proto_;
  unique_ptr<FunctionAST> body_;
 public:
  FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<FunctionAST> body) 
      : proto_(std::move(proto)), body_(std::move(body)) {}
};
#endif
