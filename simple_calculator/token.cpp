#include "token.h"
#include "ofuse.h"

#include<iomanip>
using std::setprecision;

#include<limits>
using std::numeric_limits;

#include<iostream>
using std::cin;
using std::ios;
using std::move;
using std::streamsize;

#include<cmath>
using std::fmod;

// default constructor
Token::Token() noexcept
	: tkind(Token::Token_kind::invalid)
	, tname("INVALID")
	, tvalue(0) {}

// constructor taking value as argument
// makes a number Token from a double value
Token::Token(double value) noexcept
	: tkind(Token::Token_kind::numbers)
	, tname(to_string(value))
	, tvalue(value) {}

// constructor taking character as argument
// makes an operator/parenthesis Token from a char value
Token::Token(char c) noexcept
	: tkind(Token::Token_kind::invalid)
	, tname("")
	, tvalue(0)
{
	switch (c) {
	case '/': case '*': case '+': case '-': case '!': case '%': case '=':
		tkind = Token::Token_kind::operators;
		tname.push_back(c);

		switch (c) {
		case '+': case '-':
			tvalue = 2; // sets operator precedence
			break;

		case '/': case '*': case '%':
			tvalue = 3; // sets operator precedence
			break;

		case '!':
			tvalue = 4; // sets operator precedence
			break;

		case '=':
			tvalue = 0; // sets operator precedence
			break;
		}
		break;

	case '(': case ')': case '{': case '}':
		tkind = Token::Token_kind::parentheses;
		tname.push_back(c);

		switch (c) {
		case '(':
			tvalue = -1; // sets parenthesis value
			break;

		case ')':
			tvalue = 1; // sets parenthesis value
			break;

		case '{':
			tvalue = -2; // sets parenthesis value
			break;

		case '}':
			tvalue = 2; // sets parenthesis value
			break;
		}
		break;

	case ',':
		tkind = Token::Token_kind::punctuations;
		tname.push_back(c);
		tvalue = 0;
		break;

	default:
		break;
	}
}

// constructor taking string as argument
// makes a symbolic Token from a string value
Token::Token(string name) noexcept
	: tkind(Token::Token_kind::symbolics)
	, tname(name)
	, tvalue(0) {}

// retrives the type of the token
Token::Token_kind Token::Type() const noexcept {
	return tkind;
}

// retrieves the name of the token
string Token::Name() const noexcept {
	return tname;
}

// retrieves the value of the token
double Token::Value() const noexcept {
	return tvalue;
}

// checks if a token is valid
bool Token::is_valid() const noexcept {
	if (tkind == Token::Token_kind::invalid)
		return false;
	return true;
}

// copy compound assignment operator+=
Token& Token::operator+=(const Token& right)
// adds the second operand to the first if both tokens are of type numbers
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		tvalue += right.tvalue;
		tname = to_string(tvalue);
	}
	else
		throw Bad_token("copy operator+=: expected numbers.");
	return *this;
}

// move compound assignment operator+=
Token& Token::operator+=(Token&& right)
// adds the second operand to the first if both tokens are of type numbers
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		tvalue += move(right.tvalue);
		tname = to_string(tvalue);
	}
	else
		throw Bad_token("move operator+=: expected numbers.");
	return *this;
}

// copy compound assignment operator-=
Token& Token::operator-=(const Token& right)
// subtracts the second operand to the first if both tokens are of type numbers
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		tvalue -= right.tvalue;
		tname = to_string(tvalue);
	}
	else
		throw Bad_token("copy operator-=: expected numbers.");
	return *this;
}

// move compound assignment operator-=
Token& Token::operator-=(Token&& right)
// subtracts the second operand to the first if both tokens are of type numbers
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		tvalue -= move(right.tvalue);
		tname = to_string(tvalue);
	}
	else
		throw Bad_token("move operator-=: expected numbers.");
	return *this;
}

// copy compound assignment operator*=
Token& Token::operator*=(const Token& right)
// multiplies the second operand to the first if both tokens are of type numbers
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		tvalue *= right.tvalue;
		tname = to_string(tvalue);
	}
	else
		throw Bad_token("copy operator*=: expected numbers.");
	return *this;
}

// move compound assignment operator*=
Token& Token::operator*=(Token&& right)
// multiplies the second operand to the first if both tokens are of type numbers
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		tvalue *= move(right.tvalue);
		tname = to_string(tvalue);
	}
	else
		throw Bad_token("move operator*=: expected numbers.");
	return *this;
}

// copy compound assignment operator/=
Token& Token::operator/=(const Token& right)
// divides the second operand to the first if both tokens are of type numbers
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		*this = (*this) / right;
	}
	else
		throw Bad_token("copy operator/=: expected numbers.");
	return *this;
}

// move compound assignment operator/=
Token& Token::operator/=(Token&& right)
// divides the second operand to the first if both tokens are of type numbers
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		*this = (*this) / move(right);
	}
	else
		throw Bad_token("move operator/=: expected numbers.");
	return *this;
}

// copy compound assignment operator%=
Token& Token::operator%=(const Token& right)
// calculates the remainder and assigns it to the first operand
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		*this = (*this) % right;
	}
	else
		throw Bad_token("copy operator%=: expected numbers.");
	return *this;
}

// move compound assignment operator%=
Token& Token::operator%=(Token&& right)
// calculates the remainder and assigns it to the first operand
{
	if (this->tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		*this = (*this) % move(right);
	}
	else
		throw Bad_token("move operator%=: expected numbers.");
	return *this;
}

// overloading opeartor<<
ostream& operator<<(ostream& os, const Token& token)
// insertion operator
{
	if (token.is_valid())
		os << token.tname;
	//os << token.tname << ", " << setprecision(numeric_limits<double>::digits10) << token.tvalue;
	else
		os << "INVALID TOKEN";
	return os;
}

// overloading operator>>
istream& operator>>(istream& is, Token& token)
// extraction operator
{
	char c{ '?' }; // first character
	is >> c;

	switch (c) {
	case '.': case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		is.putback(c); // puts digit back into the input stream
		double d{ 0.0 };
		is >> d;

		if (is)
			token = Token(d);
	}
	break;

	case '+': case '-': case '*': case '/': case '!': case '%': case '=':
	case '(': case ')': case '{': case '}':
	case ',':
		if (is)
			token = Token(c);
		break;

	default:
		// handles symbolics
		if (isalpha(c)) {
			string sstream { "" };
			sstream.push_back(c);

			while (is.get(c) && (isalpha(c) || isdigit(c)))
				sstream.push_back(c);
			is.putback(c);

			if (is)
				token = Token(sstream);
		}
		else {
			is.putback(c);
			is.setstate(ios::failbit);
		}
		break;
	}

	return is;
}

// overloading copy operator+
Token operator+(const Token& left, const Token& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers)
		return Token(left.tvalue + right.tvalue);
	else
		throw Bad_token("copy operator+: expected numbers.");
}

// overloading move operator+
Token operator+(Token&& left, Token&& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers)
		return Token(move(left.tvalue) + move(right.tvalue));
	else
		throw Bad_token("move operator+: expected numbers.");
}

// overloading copy operator-
Token operator-(const Token& left, const Token& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers)
		return Token(left.tvalue - right.tvalue);
	else
		throw Bad_token("copy operator-: expected numbers.");
}

// overloading move operator-
Token operator-(Token&& left, Token&& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers)
		return Token(move(left.tvalue) - move(right.tvalue));
	else
		throw Bad_token("move operator-: expected numbers.");
}

// overloading copy operator*
Token operator*(const Token& left, const Token& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers)
		return Token(left.tvalue * right.tvalue);
	else
		throw Bad_token("copy operator*: expected numbers.");
}

// overloading move operator*
Token operator*(Token&& left, Token&& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers)
		return Token(move(left.tvalue) * move(right.tvalue));
	else
		throw Bad_token("move operator*: expected numbers.");
}

// overloading copy operator/
Token operator/(const Token& left, const Token& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		if (right.tvalue == 0.0)
			throw Bad_token("division by 0.");
		return Token(left.tvalue / right.tvalue);
	}
	else
		throw Bad_token("copy operator/: expected numbers.");
}

// overloading move operator/
Token operator/(Token&& left, Token&& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		if (right.tvalue == 0.0)
			throw Bad_token("division by 0.");
		return Token(move(left.tvalue) / move(right.tvalue));
	}
	else
		throw Bad_token("move operator/: expected numbers.");
}

// overloading copy operator%
Token operator%(const Token& left, const Token& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		if (right.tvalue == 0.0)
			throw Bad_token("division by 0.");
		return Token(fmod(left.tvalue, right.tvalue));
	}
	else
		throw Bad_token("copy operator%: expected numbers.");
}

// overloading move operator%
Token operator%(Token&& left, Token&& right) {
	if (left.tkind == right.tkind && right.tkind == Token::Token_kind::numbers) {
		if (right.tvalue == 0.0)
			throw Bad_token("division by 0.");
		return Token(fmod(move(left.tvalue), move(right.tvalue)));
	}
	else
		throw Bad_token("move operator%: expected numbers.");
}

// default constructor
Token_stream::Token_stream() noexcept
	: is_full(false)
	, buffer(Token()) {}

// peeks next token
Token Token_stream::peek()
// returns the next token in the input sequence, without extracting it: 
// the token is left as the next token to be extracted from the stream.
{
	Token token = get();

	if (cin && token.is_valid())
		putback(token);

	return token;
}

// retrieves buffer 
Token Token_stream::get()
// returns the buffer if its full
// otherwise returns the next token in the input stream
{
	if (is_full) {
		is_full = false;
		return buffer;
	}

	Token token;

	if (cin.peek() != '\n')
		cin >> token;

	return token;
}

// retrieves buffer state
bool Token_stream::full() {
	return is_full;
}

// puts token back
void Token_stream::putback(const Token& token)
// stores token into the Token buffer
{
	if (is_full)
		throw runtime_error("unable to put back token: buffer full.");
	if (token.is_valid()) {
		buffer = token; // copies token to buffer
		is_full = true; // sets the buffer state to full
	}
	else
		throw Bad_token("putback: invalid token.");
}

// clears the stream state
void Token_stream::clear() {
	is_full = false;
	buffer = Token();
}