#include "simple_calculator.h"

#include<iostream>
using std::cin;
using std::streamsize;

#include<sstream>
using std::stringstream;

#include<stdexcept>
using std::runtime_error;
using std::out_of_range;

#include<algorithm>
using std::remove_if;

#include<limits>
using std::numeric_limits;

#include<iomanip>
using std::setprecision;

// checks if a char is a valid operator
bool is_an_operator(const char& c) noexcept
// checks if the character argument is the representation of a valid operator +, -, *, / or ^
// returns true if it is the case
{
	switch (c)
	{
	case '+': case '-': case '*': case '/': case '^':
		return true;

	default:
		return false;
	}
}

// checks if a token is a valid operator
bool is_an_operator(const Token& token) noexcept 
// checks if the token argument is of type operators
// returns true if it is the case
{
	if (token.type() == Token::Token_type::operators)
		return true;

	return false;
}

// checks if a char is a parenthesis
bool is_a_parenthesis(const char& c) noexcept
// checks if the character argument is a parenthesis ( or )
// returns true if it is the case
{
	switch (c)
	{
	case '(': case ')':
		return true;

	default:
		return false;
	}
}

// checks if a token is a parenthesis
bool is_a_parenthesis(const Token& token) noexcept
// checks if the token argument is of type parentheses
// returns true if it is the case
{
	if (token.type() == Token::Token_type::parentheses)
		return true;

	return false;
}

// checks if a token is a number
bool is_a_number(const Token& token) noexcept
// checks if the token argument is of type numbers
// returns true if it is the case
{
	if (token.type() == Token::Token_type::numbers)
		return true;

	return false;
}

// checks if a token is valid
bool is_valid(const Token& token) noexcept 
// checks if the token argument is valid
// returns true if it is the case
{
	if (token.type() == Token::Token_type::invalid)
		return false;

	return true;
}

// checks if a token is a valid unary operator + or -
bool is_unary_plus_or_minus(const Token& token) noexcept 
// checks if the token argument is a valid unary operator + or -
// returns true if it is the case
{
	if (is_an_operator(token) && token.value() == 2)
		return true;

	return false;
}

// tokenizes string expression
vector<Token> tokenize(const string& expression) 
// tokenizes a string expression passed as argument
// returns a vector of Token if the stringstream object is in a good state
// throws an exception otherwise
{
	string str = expression + '\n';
	stringstream ss(str);

	vector<Token> tokens;

	// ignores whitespaces
	while (isspace(ss.peek()) && ss.peek() != '\n') {
		ss.ignore(1, ' ');
	}

	for (Token t; ss && ss.peek() != '\n';) {
		ss >> t;
		if (ss && is_valid(t))
			tokens.push_back(t);

		// ignores whitespaces
		while (isspace(ss.peek()) && ss.peek() != '\n') {
			ss.ignore(1, ' ');
		}
	}

	if (!ss) {
		ss.clear();
		throw Bad_token("unable to parse expression.");
	}

	return tokens;
}

// checks if there are operators in a vector of tokens
bool contains_operator(const vector<Token>& vec) noexcept 
// checks if there is at least one operator in a vector of tokens
// returns true if it is the case
{
	for (Token token : vec) {
		if (is_an_operator(token))
			return true;
	}

	return false;
}

// checks if there are parentheses in a vector of tokens
bool contains_parenthesis(const vector<Token>& vec) noexcept
// checks if there is at least one parenthesis in a vector of tokens
// returns true if it is the case
{
	for (Token token : vec) {
		if (is_a_parenthesis(token))
			return true;
	}

	return false;
}

// checks assertion c >=-1 && c <=255
int passes_assertion(int c)
// checks if the assertion c >=-1 && c <=255 is true for a specified character
// returns 1 (true) if it is the case
// returns 0 (false) otherwise
{
	if (c >= -1 && c <= 255)
		return 1;
	else
		return 0;
}

// checks assertion c >=-1 && c <=255 for each character of a string expression
int passes_assertion(const string& expression)
// checks if the assertion c >=-1 && c <=255 is true for each character of a string expression
// returns 1 (true) if it is the case
// returns 0 (false) otherwise
{
	for (char c : expression)
		if (!passes_assertion(c))
			return 0;

	return 1;
}

// clears string expression
void clear_expression(string& expression) noexcept
// clears a string expression passed as argument by :
// - removing whitespaces
// - changing 'x' to '*' and ':' unto '/'
{
	// remove whitespaces from expression
	// checks assertion c >=-1 && c <=255 before using isspace
	if (passes_assertion(expression))
		expression.erase(remove_if(expression.begin(), expression.end(), isspace), expression.end());
	else
		expression = "";

	// replace ':', 'x' by '/' and '*'
	for (size_t i = 0; i < expression.size(); ++i) {
		switch (expression[i]) {
		case 'x':
			expression[i] = '*';
			break;

		case ':':
			expression[i] = '/';
			break;

		default:
			break;
		}
	}
}

// clears expression
void clear_expression(vector<Token>& tokens) noexcept 
// clears a vector of token expression passed as argument by
// - removing unnecessary unary operators
// - signing numbers
// e.g. {(, -, 1,)} becomes {(, -1, )}
{
	// gets size of the vector
	size_t size = tokens.size();

	for (size_t i = 0; i < size; ++i) {
		// searches for unary operators + or -
		if (is_unary_plus_or_minus(tokens[i]) && (i == 0 
			|| (is_an_operator(tokens[i - 1]) && tokens[i - 1].value() != 2)
			|| (is_a_parenthesis(tokens[i - 1]) && tokens[i - 1].value() == 1))) {

			if (i + 1 < size && is_a_number(tokens[i + 1]))
				switch (tokens[i].name()[0]) {
				case '-':
					// removes the unary operator token from the vector
					tokens.erase(tokens.begin() + i);

					// changes the sign of the token
					tokens[i].negative();

					break;

				default:
					// removes the unary operator token from the vector
					tokens.erase(tokens.begin() + i);

					break;
				}
		}

		// refreshes the value of size
		size = tokens.size();
	}
}
  
// checks parentheses
bool check_parentheses(const vector<Token>& tokens) noexcept
// checks parentheses in a vector of tokens
// returns true if nothing is wrong with the parentheses
// i.e odd number of parentheses, unclosed parentheses, etc
{
	// validation variable
	// it must never be less than 0
	int validation { 0 };
	for (Token t: tokens) {
		if (is_a_parenthesis(t) && t.value() == 1)
			++validation;
		else if (is_a_parenthesis(t) && t.value() == -1)
			--validation;
		else {}

		// validation
		if (validation < 0)
			return false;
	}

	// validation
	if (validation != 0)
		return false;

	return true;
}

// checks if an expression is valid
bool is_valid(const vector<Token>& tokens) noexcept 
// checks if an expression (represented by a vector of Token) is valid (i.e. can be computed) by using a set of rules
// returns true if it is the case
{
	// rule #0.1: the expression can not be empty
	if (tokens.empty())
		return false;

	// rule #0.2: the expression must contain valid tokens
	for (Token t : tokens) {
		if (!is_valid(t))
			return false;
	}

	// gets size of the vector tokens
	size_t size = tokens.size();

	// rule #1: the first token must be a number, an unary operator (+, -) or the parenthesis (
	if (!is_a_number(tokens[0]) &&
		(!is_an_operator(tokens[0]) || tokens[0].value() != 2) &&
		(!is_a_parenthesis(tokens[0]) || tokens[0].value() != 1))
		return false;

	// rule #2: the last token must be a number or the parenthesis )
	if (!is_a_number(tokens[size - 1]) &&
		(!is_a_parenthesis(tokens[size - 1]) || tokens[size - 1].value() != -1))
		return false;

	// rule #3: must pass the parentheses check
	if (!check_parentheses(tokens))
		return false;

	// rule #4: must pass the valid arithmetic expression check
	for (size_t i = 0; i < size; ++i) {
		switch (tokens[i].type()) {
		case Token::Token_type::numbers:
			if (i + 1 < size)
				switch (tokens[i + 1].type()) {
				case Token::Token_type::numbers:
					return false;

				case Token::Token_type::parentheses:
					if (tokens[i + 1].value() == 1)
						return false;
					break;

				default:
					break;
				}
			break;

		case Token::Token_type::operators:
			if (i + 1 < size)
				switch (tokens[i + 1].type()) {
				case Token::Token_type::operators: 
					if(tokens[i].value() == 2 || tokens[i + 1].value() != 2)
						return false; // except *+, *-, /+, /-, ^+ and ^-
					break;

				case Token::Token_type::parentheses:
					if (tokens[i + 1].value() == -1)
						return false; // when +), -), *), /) and ^)
					break;
					
				default:
					break;
				}
			break;

		case Token::Token_type::parentheses:
			if (tokens[i].value() == 1) {
				if (i + 1 < size)
					switch (tokens[i + 1].type()) {
					case Token::Token_type::operators:
						if(tokens[i + 1].value() != 2)
							return false; // when (*, (/ and (^
						break;

					case Token::Token_type::parentheses:
						if (tokens[i + 1].value() != 1)
							return false; // when ()
						break;

					default:
						break;
					}
			}
			else {
				if (i + 1 < size)
					switch (tokens[i + 1].type()) {
					case Token::Token_type::numbers:
						return false; // e.g. when )0

					case Token::Token_type::parentheses:
						if (tokens[i + 1].value() != -1)
							return false; // when )(
						break;

					default:
						break;
					}
			}
			break;

		default:
			break;

		}
	}

	return true;
}

// converts double value to string
string to_string(const double& val) 
// converts a double value to a string value
// returns a string with the representation of the double val
{
	stringstream ss;
	ss << setprecision(numeric_limits<double>::digits10) << val;
	return ss.str();
}

// finds token in vector of tokens
size_t find_first_of(Token::Token_type token_type, int token_value, vector<Token>& vec, size_t pos)
// searches the vector for the first occurrence of the token specified by its arguments
// returns the index of the first match
// if no matches were found, the function returns -1
// throws an out_of_range exception when pos is out of range
{
	if (pos >= vec.size())
		throw out_of_range("position out of range.");

	for (size_t i = pos; i < vec.size(); ++i)
		if (vec[i].type() == token_type && vec[i].value() == token_value)
			return i;

	return -1;
}

// finds token in vector of tokens
size_t find_last_of(Token::Token_type token_type, int token_value, vector<Token>& vec, size_t pos)
// searches the vector for the last occurrence of the token specified by its arguments
// returns the index of the first match
// if no matches were found, the function returns -1
// throws an out_of_range exception when pos is out of the range
{
	if (pos >= vec.size())
		throw out_of_range("position out of range.");

	for (size_t i = pos; i < vec.size(); --i)
		if (vec[i].type() == token_type && vec[i].value() == token_value)
			return i;

	return -1;
}

// calculates an expression and returns the result
Token calculate(const Token& left, const Token& right, const Token& op) 
// calculates an expression and returns the result
// supports only the operators +, -, /, * and ^
// left and right must be tokens of type numbers
// op must be of type operators
// throws a division by zero exception when detected
{
	// checks arguments
	if (!is_a_number(left) || !is_a_number(right) || !is_an_operator(op))
		throw Bad_token("unable to calculate expression.");

	// switches on op
	switch (op.name()[0]) {
	case '+':
		return left + right;

	case '-':
		return left - right;

	case '*':
		return left * right;

	case '/':
		if (right.value() == 0)
			throw Bad_token("division by zero.");
		return left / right;

	case '^':
		if ((left.value() < 0 && (right.value() != int(right.value())))
			|| (left.value() == 0 && right.value() == 0)
			|| (left.value() == 0 && right.value() < 0))
			throw Bad_token("domain error.");
		return left^right;

	default:
		throw Bad_token("unsupported operator.");
	}
}

// parses expression
vector<Token> parse_expression(const vector<Token>& expression, vector<size_t>& parentheses_indexes)
// parses the expression (represented as a vector of Token)
// returns the part of the expression that must be computed first
{
	// checks expression
	if (expression.empty() || !is_valid(expression))
		throw Bad_token("unable to parse expression.");

	// keeps track of the parentheses position
	parentheses_indexes = vector<size_t>(2);

	// expression result
	vector<Token> result;

	for (size_t i = 0; i < expression.size(); ++i) {
		switch (expression[i].type()) {
		case Token::Token_type::parentheses:
			if (expression[i].value() == 1) {
				// gets index of the left parenthesis
				parentheses_indexes[0] = i;

				// empties expression result
				result = vector<Token>();
			}
			else if (expression[i].value() == -1) {
				// gets index of the right parenthesis
				parentheses_indexes[1] = i;

				// returns the expression result
				return result;
			}

			break;

		default:
			// pushes the token into the expression result
			result.push_back(expression[i]);

			break;
		}
	}

	// returns expression
	return expression;
}

// computes expression
Token compute_expression(vector<Token>& expression) 
// parses and calculates expression the expression (represented as a vector of Token)
// returns the result as a Token number
{
	// clears expression
	clear_expression(expression);

	// checks if the expression is valid
	if (expression.empty() || !is_valid(expression))
		throw Bad_token("unable to compute expression.");

	// gets size of the vector
	size_t size = expression.size();

	if (contains_operator(expression)) {
		// sets operator precedence
		size_t precedence = 4;

		while (size > 1 && precedence >= 2) {
			// gets the index of the operator of precedence precedence
			// note: right-associativity is used for operator ^
			int index;
			if (precedence == 4)
				index = find_last_of(Token::Token_type::operators, precedence, expression, size - 1);
			else
				index = find_first_of(Token::Token_type::operators, precedence, expression);

			if (index != -1) {
				// calculates a part of the expression, removes operands and pushes the result into the expression
				expression[index - 1] = calculate(expression[index - 1], expression[index + 1], expression[index]);
				expression.erase(expression.begin() + index, expression.begin() + index + 2);

				// refreshes expression size
				size = expression.size();
			}
			else
				--precedence;
		}
	}

	// returns the only token in the expression
	if (size == 1 && is_a_number(expression[0]))
		return expression[0];
	else
		throw Bad_token("unable to compute expression.");

}