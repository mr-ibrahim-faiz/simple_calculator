#include "token.h"
#include "simple_calculator.h"

// default constructor
Token::Token() noexcept
	: ttype(Token::Token_type::invalid)
	, tname("")
	, tvalue(0) {}

// numbers constructor
Token::Token(double value)
	: ttype(Token::Token_type::numbers)
	, tvalue(value)
	, tname(to_string(value)) {}

// parentheses and operators constructor
Token::Token(char c) 
	: ttype(Token::Token_type::invalid)
	, tname("")
	, tvalue(0)
{
	switch (c) {
	// deals with operators +, -, /, * and ^
	case '+': case '-': case '*': case '/': case '^':
		ttype = Token::Token_type::operators;
		tname = c;

		// sets operator precedence
		switch (c) {
		case '+': case '-':
			tvalue = 2;
			break;

		case '/': case '*':
			tvalue = 3;
			break;

		default:
			tvalue = 4;
			break;
		}

		break;

	// deals with parentheses
	case '(': case ')':
		ttype = Token::Token_type::parentheses;
		tname = c;

		// sets parenthesis value
		if (c == '(')
			tvalue = 1;
		else
			tvalue = -1;

		break;
	}
}

// copy constructor
Token::Token(const Token& other) noexcept {
	*this = other;
}

// copy assignment operator
Token& Token::operator=(const Token& right) noexcept {
	if (this != &right) {
		ttype = right.ttype;
		tname = right.tname;
		tvalue = right.tvalue;
	}
	return *this;
}

// move constructor
Token::Token(Token&& other) noexcept 
	: ttype(Token::Token_type::invalid)
	, tname("")
	, tvalue(0)
{
	*this = move(other);
}

// move assignment operator
Token& Token::operator=(Token&& right) noexcept {
	if (this != &right) {
		ttype = move(right.ttype);
		tname = move(right.tname);
		tvalue = move(right.tvalue);

		right.ttype = Token::Token_type::invalid;
		right.tname = "";
		right.tvalue = 0;
	}
	return *this;
}

// retrieves the type of the token
Token::Token_type Token::type() const noexcept {
	return ttype;
}

// retrieves the name of the token
string Token::name() const noexcept {
	return tname;
}

// retrieves the value of the token
double Token::value() const noexcept {
	return tvalue;
}

// changes the sign of a token
void Token::negative() noexcept 
// changes the sign of a token
// only affects tokens of type numbers
{
	if (ttype == Token::Token_type::numbers) {
		if (tvalue > 0)
			tname.insert(tname.begin(), '-');
		else if (tvalue < 0)
			tname = tname.substr(1);
		tvalue *= -1;
	}
}

// overloading operator>>
istream& operator>>(istream& is, Token& token) {
	// searches for a valid operator +, -, *, / or ^
	char first { '?' };
	is >> first;

	// checks if the stream is in a good state before moving on
	if (!is)
		return is;

	// deals with operators (+, -, /, * and ^) and parentheses ( and )
	if (is_an_operator(first) || is_a_parenthesis(first))
		// creates a token of type operators or parentheses
		token = Token(first);
	// deals with operators (+, -, /, * and ^) and parentheses ( and )
	else {
		// puts character back into the stream
		is.putback(first); // similar to is.unget()

		// checks if the stream is in a good state before moving on
		if (!is)
			return is;

		// gets token value
		is >> token.tvalue;

		// checks if the stream is in a good state before moving on
		if (!is)
			return is;

		// creates a token of type numbers
		token = Token(token.tvalue);
	}

	return is;
}

// overloading operator<<
ostream& operator<<(ostream& os, const Token& token) {
	os << token.tname;
	return os;
}

// overloading operator+
Token operator+(const Token& left, const Token& right) {
	if (is_a_number(left) && is_a_number(right)) {
		return Token(left.tvalue + right.tvalue);
	}
	return Token();
}

// overloading operator-
Token operator-(const Token& left, const Token& right) {
	if (is_a_number(left) && is_a_number(right)) {
		return Token(left.tvalue - right.tvalue);
	}
	return Token();
}

// overloading operator*
Token operator*(const Token& left, const Token& right) {
	if (is_a_number(left) && is_a_number(right)) {
		return Token(left.tvalue * right.tvalue);
	}
	return Token();
}

// overloading operator/
Token operator/(const Token& left, const Token& right) {
	if (is_a_number(left) && is_a_number(right)) {
		if (right.tvalue == 0)
			throw Bad_token("division by zero.");
		return Token(left.tvalue / right.tvalue);
	}
	return Token();
}

// overloading operator^
Token operator^(const Token& left, const Token& right) {
	if (is_a_number(left) && is_a_number(right)) {
		if((left.tvalue < 0 && (right.tvalue != int(right.tvalue)))
			|| (left.tvalue == 0 && right.tvalue == 0)
			|| (left.tvalue == 0 && right.tvalue < 0))
			throw Bad_token("domain error.");
		return Token(pow(left.tvalue, right.tvalue));
	}
	return Token();
}