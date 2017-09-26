#include "token.h"

// defines type of a token
enum class Token::Token_type {
	operators, numbers, parentheses
};

// retrieves type of the token
Token::Token_type Token::type() const noexcept {
	return ttype;
}

// retrieves string value
string Token::name() const noexcept {
	return svalue;
}

// retrieves double value
double Token::value() const noexcept {
	return dvalue;
}

// overloading operator>>
istream& operator>>(istream& is, Token& token) {
	// searches for a valid operator +, -, *, / or ^
	char first{ '?' };
	is >> first;

	switch (first) {
		// deals with operators +, -, /, * and ^
	case '+': case '-': case '*': case '/': case '^':
		token.ttype = Token::Token_type::operators;
		token.svalue = first;

		// sets precedence
		switch (first) {
		case '+': case '-':
			token.dvalue = 2;
			break;
		case '/': case '*':
			token.dvalue = 3;
			break;
		default:
			token.dvalue = 4;
			break;
		}

		break;

		// deals with parentheses
	case '(': case ')':
		token.ttype = Token::Token_type::parentheses;
		token.svalue = first;

		// sets parentheses values 1 and -1
		if (first == '(')
			token.dvalue = 1;
		else
			token.dvalue = -1;

		break;

		// deals with numbers
	default:
		token.ttype = Token::Token_type::numbers;

		// gets input stream
		is.putback(first);
		is >> token.svalue;

		// checks if each character in token is allowed
		// throws a Bad_token exception if it's not the case
		for (char c : token.svalue)
			if (!is_allowed_in_expression(c))
				throw Bad_token("character '" + string(1, c) + "' not allowed in token.");

		// gets token value
		for (int i = token.svalue.size() - 1; i >= 0; --i)
			is.putback(token.svalue[i]);
		is >> token.dvalue;

		// gets token name
		if (!isspace(is.peek())) {
			string left{ "" };
			is >> left;

			for (int i = left.size() - 1; i >= 0; --i)
				is.putback(left[i]);

			size_t pos = token.svalue.find_last_of(left);
			if (pos != string::npos)
				token.svalue.erase(pos - left.size() + 1);
		}

		break;
	}

	return is;
}

// overloading operator<<
ostream& operator<<(ostream& os, const Token& token) {
	os << token.svalue << ", " << token.dvalue;
	return os;
}