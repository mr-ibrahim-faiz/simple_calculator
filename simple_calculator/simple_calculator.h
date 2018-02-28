#pragma once

#include "token.h"

// defines a token stream which provides get() and putback()
extern Token_stream ts;

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

// evaluates an expression
void calculate();