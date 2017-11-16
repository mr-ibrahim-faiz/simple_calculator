#pragma once

#include "token.h"

#include<vector>
using std::vector;

// checks if a char is a digit
bool is_a_digit(const char&) noexcept;

// checks if a char is a parenthesis
bool is_a_parenthesis(const char&) noexcept;

// checks if a char is an operator
bool is_an_operator(const char&) noexcept;

// checks if a token is valid
bool is_valid(const Token&) noexcept;

// tokenizes an expression
vector<Token> tokenize();

// puts token back in the stream
void putback_token(const Token&);

// peeks next token
bool peek_token(Token::token_type);

// computes primary
Token primary();

// computes term
Token term();

// computes expression
Token expression();