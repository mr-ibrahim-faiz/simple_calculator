#pragma once

#include<string>
using std::string;

#include<iostream>
using std::ostream;
using std::istream;

#include<stdexcept>
using std::runtime_error;

// user-defined type Bad_token
class Bad_token : public runtime_error {
	using runtime_error::runtime_error;
};

// user-defined type Token
class Token {
public:
	// type of a token
	enum class Token_kind {
		invalid, numbers, operators, parentheses, symbolics, punctuations
	};

	// default constructor
	Token() noexcept;

	// constructor taking value as argument
	// makes a Token from a double value
	explicit Token(double) noexcept;

	// constructor taking character as argument
	// makes a Token from a char value
	explicit Token(char) noexcept;

	// constructor taking string as argument
	// makes a Token from a string value
	explicit Token(string) noexcept;

	// retrives the type of the token
	Token::Token_kind Type() const noexcept;

	// retrieves the name of the token
	string Name() const noexcept;

	// retrieves the value of the token
	double Value() const noexcept;

	// checks if a token is valid
	bool is_valid() const noexcept;

	// copy compound assignment operator+=
	Token& operator+=(const Token&);

	// move compound assignment operator+=
	Token& operator+=(Token&&);

	// copy compound assignment operator-=
	Token& operator-=(const Token&);

	// move compound assignment operator-=
	Token& operator-=(Token&&);

	// copy compound assignment operator*=
	Token& operator*=(const Token&);

	// move compound assignment operator*=
	Token& operator*=(Token&&);

	// copy compound assignment operator/=
	Token& operator/=(const Token&);

	// move compound assignment operator/=
	Token& operator/=(Token&&);

	// copy compound assignment operator%=
	Token& operator%=(const Token&);

	// move compound assignment operator%=
	Token& operator%=(Token&&);

private:
	Token_kind tkind; // type of a token
	string tname; // name of a token
	double tvalue; // value of a token;

				   // overloading opeartor<<
	friend ostream& operator<<(ostream&, const Token&);

	// overloading operator>>
	friend istream& operator>>(istream&, Token&);

	// overloading copy operator+
	friend Token operator+(const Token&, const Token&);

	// overloading move operator+
	friend Token operator+(Token&&, Token&&);

	// overloading copy operator-
	friend Token operator-(const Token&, const Token&);

	// overloading move operator-
	friend Token operator-(Token&&, Token&&);

	// overloading copy operator*
	friend Token operator*(const Token&, const Token&);

	// overloading move operator*
	friend Token operator*(Token&&, Token&&);

	// overloading copy operator/
	friend Token operator/(const Token&, const Token&);

	// overloading move operator/
	friend Token operator/(Token&&, Token&&);

	// overloading copy operator%
	friend Token operator%(const Token&, const Token&);

	// overloading move operator%
	friend Token operator%(Token&&, Token&&);
};

// user-defined type Token_stream
class Token_stream {
public:
	// default constructor
	explicit Token_stream() noexcept;

	// peeks next token
	Token peek();

	// retrieves buffer 
	Token get();

	// retrieves buffer state
	bool full();

	// puts token back
	void putback(const Token&);

	// clear the stream state
	void clear();

private:
	bool is_full; // buffer state
	Token buffer; // token buffer
};