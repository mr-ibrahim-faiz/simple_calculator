#include "simple_calculator.h"

#include<iostream>
using std::cin;

#include<stdexcept>
using std::runtime_error;

// checks if a char is a digit
bool is_a_digit(const char& c) noexcept
// checks if a char c can be represented as a digit
// returns true if it is the case
{
	switch (c) {
	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9':
		return true;
	default:
		return false;
	}
}

// checks if a char is a parenthesis
bool is_a_parenthesis(const char& c) noexcept 
// checks if a char c is a parenthesis
// returns true if it is the case
{
	switch (c) {
	case '(': case ')':
		return true;
	default:
		return false;
	}
}

// checks if a char is an operator
bool is_an_operator(const char& c) noexcept 
// checks if a char c is an operator
// returns true if it is the case
{
	switch (c) {
	case '+': case '-': case '*': case '/':
		return true;
	default:
		return false;
	}
}

// checks if a token is valid
bool is_valid(const Token& token) noexcept 
// checks if a token is valid
// returns true if it is the case
{
	if (token.Type() != Token::token_type::invalid)
		return true;
	return false;
}

// checks if the user wants to exit the program
bool is_exit()
// checks the user's input
// returns true if the user enters "exit"
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
		return false;
	}
}

// tokenizes an expression
vector<Token> tokenize() 
// tokenizes an expression from input
// returns a vector of tokens
{
	vector<Token> result;

	for (Token token; cin.peek() != '\n'; ) {

		if (isspace(cin.peek())) {
			cin >> token;
			if (cin && is_valid(token))
				result.push_back(token);
			else
				throw runtime_error("unable to tokenize input.");
		}

		while (isspace(cin.peek()) && cin.peek() != '\n')
			cin.ignore(1);
	}

	getchar();
	return result;
}

// puts token back in the stream
void putback_token(const Token& token) 
// puts the token passed as argument into the stream
{
	if (is_valid(token))
		for (int i = token.Name().size() - 1; i >= 0; --i)
			cin.putback(token.Name()[i]);
}

// peeks next token
bool peek_token(Token::token_type token_type) 
// peeks the next token into the stream
// checks if its type equals the type passed as argument
// returns true if it is the case
{
	Token token;

	if (cin.peek() != '\n') {
		cin >> token;
		if (cin)
			putback_token(token);
		if (token.Type() == token_type)
			return true;
	}

	if (!cin)
		throw runtime_error("something went wrong.");

	return false;
}

// computes primary
Token primary() {
	Token token;

	while (isspace(cin.peek()) && cin.peek() != '\n')
		cin.ignore(1);

	if (cin.peek() != '\n') {
		cin >> token;
		switch (token.Type()) {
		case Token::token_type::operators:
			if (token.Name() == "-" || token.Name() == "+") {
				putback_token(token);
				return Token(0.0);
			}
			break;

		case Token::token_type::numbers:
			break;

		case Token::token_type::parentheses:
			if (token.Value() == -1) {
				token = expression();
				Token parenthesis;
				if (cin.peek() != '\n') {
					cin >> parenthesis;
					if (!(parenthesis.Type() == Token::token_type::parentheses && parenthesis.Value() == 1))
						throw runtime_error("expected right parenthesis.");
				}
				else
					throw runtime_error("expected right parenthesis.");
			}
			else
				throw runtime_error("expected left parenthesis.");

			break;

		default:
			break;
		}
	}

	while (isspace(cin.peek()) && cin.peek() != '\n')
		cin.ignore(1);

	if (!cin || token.Type() != Token::token_type::numbers)
		throw runtime_error("invalid operand.");

	return token;
}

// computes term
Token term() {
	Token left = primary();

	while (peek_token(Token::token_type::operators)) {
		Token op;
		cin >> op;

		switch (op.Name()[0]) {
		case '*':
			left = Token(left.Value() * primary().Value());
			break;

		case '/':
		{
			Token divisor = primary();
			if(divisor.Value() == 0.0)
				throw runtime_error("division by zero.");
			left = Token(left.Value() / divisor.Value());
		}			
			break;

		default:
			putback_token(op);
			return left;
		}
	}

	return left;
}

// computes expression
Token expression() {
	Token left = term();

	while (peek_token(Token::token_type::operators)) {
		Token op;
		cin >> op;

		switch (op.Name()[0]) {
		case '+':
			left = Token(left.Value() + term().Value());
			break;

		case '-':
			left = Token(left.Value() - term().Value());
			break;

		default:
			break;
		}
	}

	return left;
}