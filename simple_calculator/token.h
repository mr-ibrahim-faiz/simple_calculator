#pragma once

#include<iostream>
using std::istream;
using std::ostream;

#include<stdexcept>
using std::runtime_error;

#include<string>
using std::string;

// defines user-type Bad_token exception
class Bad_token : public runtime_error {
	using runtime_error::runtime_error;
};

// defines the user-type Token
class Token {
public:
	// defines type of a token
	enum class Token_type;

	// retrieves type of the token
	Token_type type() const noexcept;

	// retrieves string value
	string name() const noexcept;

	// retrieves double value
	double value() const noexcept;

private:
	Token_type ttype; // type of the token
	string svalue; // name of the token
	double dvalue; // value of the token

	// overloading operator>>
	friend istream& operator>>(istream&, Token&);

	// overloading operator<<
	friend ostream& operator<<(ostream&, const Token&);

};