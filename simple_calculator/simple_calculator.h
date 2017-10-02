#pragma once

#include "token.h"

#include<vector>
using std::vector;

#include<string>
using std::string;

// checks if a char is a valid operator
bool is_an_operator(const char&) noexcept;

// checks if a token is a valid operator
bool is_an_operator(const Token&) noexcept;

// checks if a char is a parenthesis
bool is_a_parenthesis(const char&) noexcept;

// checks if a token is a parenthesis
bool is_a_parenthesis(const Token&) noexcept;

// checks if a token is a number
bool is_a_number(const Token&) noexcept;

// checks if a token is valid
bool is_valid(const Token&) noexcept;

// checks if a token is a valid unary operator + or -
bool is_unary_plus_or_minus(const Token&) noexcept;

// tokenizes string expression
vector<Token> tokenize(const string&);

// checks if there are operators in a vector of tokens
bool contains_operator(const vector<Token>&) noexcept;

// checks if there are operators in a vector of tokens
bool contains_parenthesis(const vector<Token>&) noexcept;

// checks assertion c >=-1 && c <=255
int passes_assertion(int);

// checks assertion c >=-1 && c <=255 for each character of a string expression
int passes_assertion(const string&);

// clears string expression
void clear_expression(string&) noexcept;

// clears expression
void clear_expression(vector<Token>&) noexcept;

// checks parentheses
bool check_parentheses(const vector<Token>&) noexcept;

// checks if an expression is valid
bool is_valid(const vector<Token>&) noexcept;

// converts double value to string
string to_string(const double&);

// finds token in vector of tokens
size_t find_first_of(Token::Token_type, int, vector<Token>&, size_t pos = 0);

// finds token in vector of tokens
size_t find_last_of(Token::Token_type, int, vector<Token>&, size_t pos = 0);

// calculates an expression and returns the result
Token calculate(const Token&, const Token&, const Token&);

// parses expression
vector<Token> parse_expression(const vector<Token>&, vector<size_t>&);

// computes expression
Token compute_expression(vector<Token>&);