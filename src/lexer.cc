#include "llvm-lang/include/lexer.h"

static int gettok() {
  static int lastChar = ' ';

  // Skip whitespace
  while (isspace(lastChar)) {
    lastChar = getchar();
  }
  bool seenDecimal = (lastChar == '.');
  // get tokens that are more than one character with looper
  // alphanumeric tokens [a-zA-Z][a-zA-Z0-9]*
  if (isalpha(lastChar)) {
    IdentifierStr = lastChar;
    lastChar = getchar();
    // create the identifier
    while (isalnum(lastChar)) {
      IdentifierStr += lastChar;
      lastChar = getchar();
    }

    // for keywords, return the token value
    if (IdentifierStr == "def") {
      return tok_def;
    }

    else if (IdentifierStr == "extern") {
      return tok_extern;
    }

    else return tok_identifier;
  }
  //numeric tokens [0-9.]+ (numbers followed by dot followed by numbers)
  
  if (isdigit(lastChar) || lastChar == '.') {
    while (isdigit(lastChar) || lastChar == '.') {
      NumStr += lastChar;
      lastChar = getchar();
      if (seenDecimal && lastChar == '.') return SYNTAX_ERROR;
    }
    NumVal = strtod(NumStr.c_str(), 0);
    return tok_num;
  }
  if (lastChar == '#') {
    while (lastChar != EOF && lastChar != '\n' && lastChar != '\r') {
      lastChar = getchar();
    }
    if (lastChar == EOF) {
      return gettok();
    }
  }
  else if (lastChar == EOF) {
    return tok_eof;
  }
  int thisChar = lastChar;
  lastChar = getchar();
  return thisChar;
}
