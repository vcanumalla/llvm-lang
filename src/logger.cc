#include "logger/logger.h"

std::unique_ptr<ExprAST> logError(const char *Str) {
  fprintf(stderr, "Error; %s\n", Str);
  return nullptr;
}

std::unique_ptr<PrototypeAST> logErrorP(const char *Str) {
  logError(Str);
  return nullptr;
}