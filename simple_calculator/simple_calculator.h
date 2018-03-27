#pragma once

#include "token.h"

#include<map>
using std::map;

// defines a token stream which provides get() and putback()
extern Token_stream ts;

// defines a container for user-defined variables
extern map<string, Token> variables;

// defines available functions
enum Function {
	invalid, squareroot, power
};

// defines a container for user-defined functions
extern map<string, Function> functions;

// reads and evaluates a statement
Token statement();

// reads and evaluates a declaration
Token declaration();

// initializes variables
void initialize_variables();

// initializes available functions
void initialize_functions();

// reads and evaluates a function
Token function();

// reads and evaluates a squareroot operation
Token squareroot_function();

// reads and evaluates a power operation
Token power_function();

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

// checks if the user wants help
bool is_help();

// displays help
void display_help();

// checks if a variable has been declared
bool is_declared(const string&);

// checks if a variable is a constant
bool is_constant(const string&);

// checks if a function is available
bool is_function(const string&);

// evaluates an expression
void calculate();