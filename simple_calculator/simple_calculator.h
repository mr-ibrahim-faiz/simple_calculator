#pragma once

#include "token.h"

#include<map>
using std::map;

// defines a token stream which provides get() and putback()
extern Token_stream ts;

// defines a container for user-defined variables
extern map<string, Token> variables;

// reads and evaluates a statement
Token statement();

// reads and evaluates a declaration
Token declaration();

// initializes variables
void initialize_variables();

// evaluates an assignment
Token assignment(const string&);

// reads and evaluates an expression
Token expression();

// reads and evaluates a term
Token term();

// reads and evaluates a factorial
Token factorial();

// reads and evaluates a primary
Token primary();

// checks if the user wants to exit the program
bool is_exit();

// checks if a variable has been declared
bool is_declared(const string&);

// evaluates an expression
void calculate();