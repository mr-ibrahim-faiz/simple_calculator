#pragma once

#include<iostream>
using std::istream;
using std::ostream;

#include<string>
using std::string;

// defined-type Token
class Token {
public:
	// defines different kinds of token
	enum class token_type {
		invalid, numbers, operators, parentheses
	};

	// default constructor
	explicit Token() noexcept;

	// constructor creating a token of type number
	explicit Token(double) noexcept;

	// constructor creating a token of type parentheses or operators
	explicit Token(char) noexcept;

	// retrives type of the token
	Token::token_type Type() const noexcept;

	// retrieves name of a token
	string Name() const noexcept;

	// retrives value of a token
	double Value() const noexcept;

private:
	token_type ttype; // type of the token
	string tname; // name of the token
	double tvalue; // value of the token

	// gets type of a character
	static token_type get_type(const char&) noexcept;

	// gets operator precedence
	unsigned int get_precedence(const char&);

	// gets parethensis value
	int get_parenthesis_value(const char&);

	// overloading operator<<
	friend ostream& operator<<(ostream&, const Token&);

	// overloading operator>>
	friend istream& operator>>(istream&, Token&);
};