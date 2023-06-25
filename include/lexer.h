#ifndef LEXER
#define LEXER

#include<string>

using std::string;

const int SYNTAX_ERROR = -9999;
// Lexer returns a token for each part of the input. 
// Token represents the "type" of input: eof, number, function, etc.
enum Token {
  tok_eof = -1,
  
  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary: no keyword, just some identifier (like a variable name)
  tok_identifier = -4,
  tok_num = -5
};
// string built up for identifier tokens
static string IdentifierStr;
static string NumStr;
static double NumVal;

// gets the curent token and returns the identifier: 
// either the ascii character or the Token enum variant.
static int gettok();

#endif