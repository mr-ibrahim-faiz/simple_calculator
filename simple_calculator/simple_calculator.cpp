#include "simple_calculator.h"
#include "ofuse.h"

#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::streamsize; // test

#include<limits>
using std::numeric_limits;

#include<utility>
using std::pair;

#include<vector>
using std::vector;

#include<cmath>
using std::pow;
using std::sqrt;
using std::isfinite;

const string quit { "exit" };
const string assignment_operator { "=" };
const char end_statement { '\n' };

// reads and evaluates a statement
Token statement() 
// reads input for statements and evaluates it
// returns a token which is the avaluated statement
{
	// removes whitespaces at the beginning of statement
	while (isspace(cin.peek()) && cin.peek() != end_statement)
		cin.ignore(1);

	Token token = ts.peek();
	switch (token.Type()) {
		case Token::Token_kind::symbolics:
			if (is_declared(token.Name()) || is_function(token.Name()))
				return expression();
			else
				return declaration();

		default:
			return expression();
	}
}

// reads and evaluates a declaration
Token declaration() 
// reads input for declaration and evaluates it
// declaration syntax : name '=' expression
// returns a token which is the avaluated declaration
{
	Token name = ts.get();
	if (name.Type() != Token::Token_kind::symbolics)
		throw Bad_token("symbolic name expected.");

	if (is_constant(name.Name()))
		throw Bad_token(name.Name() + " is a constant and can't be redefined.");

	// removes whitespaces
	while (isspace(cin.peek()) && cin.peek() != end_statement)
		cin.ignore(1);

	Token token = ts.get();
	if (!(token.Type() == Token::Token_kind::operators && token.Name() == assignment_operator))
		throw Bad_token("assignment operator= expected.");

	token = expression();

	// saves the user-defined variable into memory
	variables[name.Name()] = token;

	return token;
}

// initializes variables
void initialize_variables() 
// predefines variables
{
	variables["pi"] = Token(3.14159265359);
}

// evaluates an assignment
Token assignment(const string& name) 
// gives a new value to the variable named name
// name is a declared variable
{
	if (!is_declared(name))
		throw Bad_token(name + " is not declared.");
	else if (is_constant(name))
		throw Bad_token(name + " is a constant and can't be redefined.");

	Token token = expression();
	variables[name] = token;

	if (!(token.is_valid() && cin.peek() == end_statement && !ts.full()))
		throw Bad_token("invalid assignment.");

	return token;
}

// initializes available functions
void initialize_functions() 
// predefines function names
{
	functions["sqrt"] = squareroot;
	functions["pow"] = power;
}

// reads and evaluates a function
Token function()
// reads input for function and evaluates it
// returns a token which is the evaluated expression
{
	Token left = ts.get();
	Function efunction = functions[left.Name()];
	if (efunction == invalid)
		throw Bad_token("(function) invalid function.");

	Token token = ts.get();
	switch (token.Type()) {
	case Token::Token_kind::parentheses:
	{
		if (!(token.Value() == -1))
			throw Bad_token("(function) left parenthesis '(' expected.");

		switch (efunction) {
		case squareroot:
			left = squareroot_function(); 
			break;

		case power:
			left = power_function();
			break;

		default:
			throw Bad_token("(function) unknown function.");
		}

		Token right = ts.get();
		if (!(right.Value() == 1))
			throw Bad_token("(function) left parenthesis ')' expected.");
	}
	break;

	default:
		throw Bad_token("(function) left parenthesis '(' expected.");
	}

	return left;
}

// reads and evaluates a squareroot operation
Token squareroot_function()
// reads input for an expression
// returns a token which is the squareroot of the expression
{
	// reads expression
	Token left = expression();
	if (left.Value() < 0)
		throw Bad_token("(squareroot function) nonnegative real number expected.");

	left = Token(sqrt(left.Value()));

	return left;
}

// reads and evaluates a power operation
Token power_function()
// syntax a ',' b
// reads input for two expressions a and b
// returns a token which is a multiplication of a by itself b times
{
	// reads expression
	Token left = expression();

	Token comma = ts.get();
	if (!(comma.Type() == Token::Token_kind::punctuations && comma.Name() == ","))
		throw Bad_token("(power function) comma expected.");

	Token right = expression();
	if (right.Type() != Token::Token_kind::numbers)
		throw Bad_token("(power function) power expected.");

	double base { left.Value() };
	double exponent { right.Value() };
	if (isfinite(base) && base < 0.0 && isfinite(exponent) && !is_integer(exponent))
		throw Bad_token("(power function) domain error. negative base and noninteger exponent.");

	left = Token(pow(base, exponent));

	return left;
}

// reads and evaluates an expression
Token expression()
// reads input for expression and evaluates it
// returns a token which is the evaluated expression
{
	Token left = term();

	// peeks at the next token and evaluates it if it's an operator token
	while (ts.peek().Type() == Token::Token_kind::operators && ts.peek().Value() == 2) {
		Token op;

		op = ts.get();

		// refuses a++b, a--b, a+-b, a-+b
		if (ts.peek().Type() == Token::Token_kind::operators && ts.peek().Value() == 2)
			throw Bad_token("invalid expression.");

		switch (op.Name()[0]) {
		case '+':
			left += term(); // evaluates term and adds
			break;

		case '-':
			left -= term(); // evaluates term and subtracts
			break;

		default:
			break;
		}
	}

	if (left.Type() != Token::Token_kind::numbers)
		throw Bad_token("expression expected.");

	return left;
}

// reads and evaluates a term
Token term()
// reads input for term and evaluates it
// returns a token which is the evaluated term
{
	Token left = factorial();

	// peeks at the next token and evaluates it if it's an operator token
	while (ts.peek().Type() == Token::Token_kind::operators && ts.peek().Value() == 3) {
		Token op;
		op = ts.get();

		switch (op.Name()[0]) {
		case '/':
			left /= factorial(); // evaluates factorial and divides
			break;

		case '*':
			left *= factorial(); // evaluates factorial and multiplies
			break;

		case '%':
			left %= factorial(); // evaluates factorial and calculates the remainder
			break;

		default:
			break;
		}
	}

	if (left.Type() != Token::Token_kind::numbers)
		throw Bad_token("term expected.");

	return left;
}

// reads and evaluates a term
Token factorial()
// reads input for a factorial and evaluates it
// returns a token which is the evaluated factorial
{
	Token left = primary();

	// peeks at the next token and evaluates it if it's an operator token
	if (ts.peek().Type() == Token::Token_kind::operators && ts.peek().Value() == 4) {
		Token op;
		op = ts.get();

		if (!is_positive_integer(left.Value()))
			throw Bad_token("expected non - negative integer argument.");
		left = Token(factorial(left.Value())); // evaluates factorial
	}

	if (left.Type() != Token::Token_kind::numbers)
		throw Bad_token("factorial expected.");

	return left;
}


// reads and evaluates a primary
Token primary()
// reads input for primary and evaluates it
// returns a token which is the evaluated primary
{
	// removes whitespaces at the beginning of the primary
	while (isspace(cin.peek()) && cin.peek() != end_statement)
		cin.ignore(1);

	Token left = ts.get();

	switch (left.Type()) {
	case Token::Token_kind::symbolics:
		if (is_function(left.Name())) {
			ts.putback(left);
			left = function(); // handles functions
		}
		else if (ts.peek().Type() == Token::Token_kind::operators && ts.peek().Name() == assignment_operator) {
			ts.get(); // removes the assignment operator= from the stream
			left = assignment(left.Name()); // handles assignments
		}
		else
			left = variables[left.Name()]; // handles defined names
		
		break;

	case Token::Token_kind::parentheses: // handles '(' expression ')'
	{
		if (!(left.Type() == Token::Token_kind::parentheses && (left.Value() == -1 || left.Value() == -2)))
			throw Bad_token{ string("left parenthesis ") + ((left.Value() == 1) ? "(" : "{") + string(" expected.") };

		// defines a variable to keep track of a parenthesis value
		int parenthese_value = (int)left.Value();

		// reads expression
		left = expression();

		if (left.Type() != Token::Token_kind::numbers)
			throw Bad_token("expression expected.");

		Token right = ts.get();

		if (!(right.Type() == Token::Token_kind::parentheses && right.Value() == -parenthese_value))
			throw Bad_token{ string("right parenthesis ") + ((parenthese_value == -1) ? ")" : "}") + string(" expected.") };

	}
	break;

	case Token::Token_kind::operators:
		if (left.Value() == 2) {
			// refuses ++b, --b, +-b, -+b
			if (ts.peek().Type() == Token::Token_kind::operators && ts.peek().Value() == 2)
				throw Bad_token("invalid expression.");

			switch (left.Name()[0]) {
			case '+':
				left = primary();
				break;

			case '-':
				left = Token(-1.0) * primary();
				break;
			}
		}
		else
			throw Bad_token("unary operator + or - expected.");
		break;

	case Token::Token_kind::numbers:
		break;

	default:
		throw Bad_token("invalid expression.");
	}

	// removes whitespaces at the end of the primary
	while (isspace(cin.peek()) && cin.peek() != end_statement)
		cin.ignore(1);

	if (left.Type() != Token::Token_kind::numbers)
		throw Bad_token("primary expected.");

	return left;
}

// checks if the user wants to exit the program
bool is_exit()
// checks the input
// returns true if the user wants to exit
// returns false otherwise
{
	string sstream{ "" };
	getline(cin, sstream);
	if (sstream == quit)
		return true;
	else {
		cin.putback(end_statement);

		if(!sstream.empty())
			for (long long int i = sstream.size() - 1; i >= 0; --i)
				cin.putback(sstream[(const unsigned int)i]);
	}
	return false;
}

// checks if a variable has been declared
bool is_declared(const string& name) 
// checks if a variable with the name name has been declared
// returns true if it is the case
// returns false otherwise
{
	Token token = variables[name];
	if (token.is_valid())
		return true;
	return false;
}

// checks if a variable is a constant
bool is_constant(const string& name)
// checks if a variable with the name name is a constant
// returns true if it is the case
// returns false otherwise
{
	vector<string> constants = { "pi" };
	for (string constant : constants)
		if (constant == name)
			return true;
	return false;
}

// checks if a function is available
bool is_function(const string& name) 
// checks if there is a function named name
// returns true if it is the case
// returns false other wise
{
	vector<string> functions = { "sqrt", "pow" };
	for (string function : functions)
		if (function == name)
			return true;
	return false;
}

// evaluates an expression
void calculate() 
// main function
// evaluates an expression
{
	Token token = statement(); // gets and computes expression

	// verifies that the expression was fully computed
	// and that the result is valid before displaying it 
	if (token.is_valid() && cin.peek() == end_statement && !ts.full())
		cout << token << endl;
	else
		throw Bad_token("invalid expression.");

	if (cin.peek() == end_statement)
		getchar(); // deals with the newline left in the input stream
}