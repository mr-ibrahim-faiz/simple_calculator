#pragma once

#include<iostream>
using std::move;
using std::istream;
using std::ostream;

#include<stdexcept>
using std::runtime_error;

#include<string>
using std::string;

// defines the type Bad_token
class Bad_token : public runtime_error {
	using runtime_error::runtime_error;
};

// defines the type Token
class Token {
public:
	// defines the types of token available
	enum class Token_type {
		invalid, operators, numbers, parentheses
	};

	// default constructor
	explicit Token() noexcept;

	// numbers constructor
	explicit Token(double);

	// parentheses and operators constructor
	explicit Token(char);

	// copy constructor
	Token(const Token&) noexcept;

	// copy assignment operator
	Token& operator=(const Token&) noexcept;

	// move constructor
	Token(Token&&) noexcept;

	// move assignment operator
	Token& operator=(Token&&) noexcept;

	// retrieves the type of the token
	Token_type type() const noexcept;

	// retrieves the name of the token
	string name() const noexcept;

	// retrieves the value of the token
	double value() const noexcept;

	// changes the sign of a token
	void negative() noexcept;

private:
	Token_type ttype; // type of the token
	string tname; // name of the token
	double tvalue; // value of the token

	// overloading operator>>
	friend istream& operator>>(istream&, Token&);

	// overloading operator<<
	friend ostream& operator<<(ostream&, const Token&);

	// overloading operator+
	friend Token operator+(const Token&, const Token&);

	// overloading operator-
	friend Token operator-(const Token&, const Token&);

	// overloading operator*
	friend Token operator*(const Token&, const Token&);

	// overloading operator/
	friend Token operator/(const Token&, const Token&);

	// overloading operator^
	friend Token operator^(const Token&, const Token&);
};