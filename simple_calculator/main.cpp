/*
	Simple Calculator

	This program calculates the expression provided by the user.

	The grammar for the input is the following:

	Calculation:
		Statement
		Quit

	Quit:
		"exit"

	Statement:
		Declaration
		Expression
	
	Assignment:
		Name '=' Expression

	Declaration:
		Name '=' Expression

	Expression:
		Term
		Expression '+' Term
		Expression '-' Term
	
	Term:
		Factorial
		Term '/' Factorial
		Term '*' Factorial
		Term '%' Factorial

	Factorial:
		Primary
		Primary '!'

	Function:
		pow '(' Expression  ',' Expression ')'
		sqrt '(' Expression ')'

	Primary:
		Number
		Symbolics
		Assignment
		'(' Expression ')'
		'-' Primary
		'+' Primary
		Function
	
	Number:
		floating-point-literal
*/

#include "token.h"
#include "ofuse.h"
#include "simple_calculator.h"

#include<iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::streamsize;

#include<limits>
using std::numeric_limits;

#include<stdexcept>
using std::exception;

// defines a token stream which provides get() and putback()
Token_stream ts;

// defines a container for user-defined variables
map<string, Token> variables;

// defines a container for user-defined functions
map<string, Function> functions;

int main()
try
{
	const string prompt { "> " };
	initialize_variables();
	initialize_functions();

	while (true) {
		cout << prompt; // prompts the user to enter expression

		// checks if the user wants to exit the program
		if (is_exit())
			break;

		try {
			calculate();
		}
		catch (Bad_token& e) {
			cerr << "Error: " << e.what() << endl;

			if (!cin)
				cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// clears the token_stream state
			if (ts.full())
				ts.clear();
		}
		cout << endl;
	}

	cout << "\nGoodbye !" << endl;

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Error: unknown exception caught." << endl;
	return 2;
}