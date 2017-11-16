#include "token.h"
#include "ofuse.h"
#include "simple_calculator.h"

#include<stdexcept>
using std::runtime_error;

#include<iostream>
using std::ios;

// default constructor
Token::Token() noexcept
	: ttype(token_type::invalid)
	, tname("")
	, tvalue(0) {}

// constructor creating a token of type number
Token::Token(double value) noexcept
	: ttype(token_type::numbers)
	, tname(to_string(value))
	, tvalue(value) {}

// constructor creating a token of type parentheses or operators
Token::Token(char c) noexcept
	: ttype(token_type::invalid)
	, tname("")
	, tvalue(0)
{
	ttype = get_type(c);
	switch (ttype) {
	case token_type::numbers:
		tname = string(1, c);
		tvalue = to_int(c);
		break;

	case token_type::operators:
		tname = string(1, c);
		tvalue = get_precedence(c);
		break;

	case token_type::parentheses:
		tname = string(1, c);
		tvalue = get_parenthesis_value(c);
		break;

	default:
		break;
	}
}

// retrives type of the token
Token::token_type Token::Type() const noexcept {
	return ttype;
}

// retrieves name of a token
string Token::Name() const noexcept {
	return tname;
}

// retrives value of a token
double Token::Value() const noexcept {
	return tvalue;
}

// gets type of a character
Token::token_type Token::get_type(const char& c) noexcept 
// analyzes a char c and returns its type
// returns a value of type Token::token_type
{
	if (is_a_digit(c) || c == '.')
		return token_type::numbers;
	else if (is_an_operator(c))
		return token_type::operators;
	else if (is_a_parenthesis(c))
		return token_type::parentheses;
	else
		return token_type::invalid;
}

// gets operator precedence
unsigned int Token::get_precedence(const char& c) 
// returns the precedence of an operator c
// throws an exception if the char c is not the representation of an operator
{
	switch (c) {
	case '+': case '-':
		return 2;
	case '*': case '/':
		return 3;
	default:
		throw runtime_error("invalid operator.");
	}
}

// gets parethensis value
int Token::get_parenthesis_value(const char& c) 
// returns the value of a parenthesis
// i.e. -1 for ( and +1 for )
// throws an exception if the char c is not the representation of a parenthesis
{
	switch (c) {
	case '(':
		return -1;
	case ')':
		return 1;
	default:
		throw runtime_error("not a parenthesis.");
	}
}

// overloading operator<<
ostream& operator<<(ostream& os, const Token& token) {
	//os << token.tname << '\n' << setprecision(numeric_limits<double>::digits10) << token.tvalue; // debug
	os << token.tname;
	return os;
}

// overloading operator>>
istream& operator>>(istream& is, Token& token) {
	char first{ '?' }; // first character
	is >> first;
	if (!is)
		return is;

	Token::token_type type = Token::get_type(first);

	switch (type) {
	case Token::token_type::operators: case Token::token_type::parentheses:
		token = Token(first);
		break;

	case Token::token_type::numbers:
	{
		is.unget();
		double value{ 0.0 };
		is >> value;
		if (!is)
			return is;
		token = Token(value);
	}
	break;

	default:
		token = Token();
		is.setstate(ios::failbit);
		break;
	}

	return is;
}