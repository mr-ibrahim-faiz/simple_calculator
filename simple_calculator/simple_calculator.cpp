#include "simple_calculator.h"

#include<iostream>
using std::cin;
using std::streamsize; // test

#include<limits>
using std::numeric_limits;

#include "ofuse.h"

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
			left /= factorial(); // evaluates primary and divides
			break;

		case '*':
			left *= factorial(); // evaluates primary and multiplies
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
	while (isspace(cin.peek()) && cin.peek() != '\n')
		cin.ignore(1);

	Token left = ts.get();

	switch (left.Type()) {
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
	while (isspace(cin.peek()) && cin.peek() != '\n')
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
	if (sstream == "exit")
		return true;
	else {
		cin.putback('\n');
		for (int i = sstream.size() - 1; i >= 0; --i)
			cin.putback(sstream[i]);
	}
	return false;
}