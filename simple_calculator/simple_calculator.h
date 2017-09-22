#pragma once

#include<string>
using std::string;

// counts parentheses
size_t count_parentheses(const string&) noexcept;

// checks parentheses
bool check_parentheses(const string&) noexcept;

// counts operators
size_t count_operators(const string&) noexcept;

// checks if a char is a representation of a digit
bool is_a_digit(const char&) noexcept;

// checks if an expression is valid
bool is_valid(const string&) noexcept;

// checks if a char is a valid unary operator + or -
bool is_unary_plus_or_minus(const char&) noexcept;

// checks if a character is allowed in an operand
bool is_allowed_in_operand(const char&) noexcept;

// calculates an expression and returns the result
double calculate(const double&, const double&, const char&);

// checks assertion c >=-1 && c <=255
int passes_assertion(int);

// checks assertion c >=-1 && c <=255 for each character of a string expression
int passes_assertion(const string&);

// clears expression
void clear_expression(string&) noexcept;

// returns the part of the expression that must be computed first
string parse_expression(const string&) noexcept;

// computes expression
string compute_expression(string);