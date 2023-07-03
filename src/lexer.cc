#include "lexer/lexer.h"
#include "lexer/token.h"
int CurTok;
std::string IdentifierStr;
double NumVal;

int gettok() {
  static int lastChar = ' ';

  // Skip whitespace
  while (isspace(lastChar)) {
    lastChar = getchar();
  }
  // get tokens that are more than one character with looper
  // alphanumeric tokens [a-zA-Z][a-zA-Z0-9]*
  if (isalpha(lastChar)) {
    IdentifierStr = lastChar;
    // create the identifier
    while (isalnum((lastChar = getchar()))) {
      IdentifierStr += lastChar;
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
    std::string NumStr;
    do {
      NumStr += lastChar;
      lastChar = getchar();
    } while (isdigit(lastChar) || lastChar == '.');

    // Convert numeric string to numeric value
    // that we are store in NumVal
    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }
  if (lastChar == '#') {
    while (lastChar != EOF && lastChar != '\n' && lastChar != '\r') {
      lastChar = getchar();
    }
    if (lastChar != EOF) {
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

int getNextToken() {
  return CurTok = gettok();
}
