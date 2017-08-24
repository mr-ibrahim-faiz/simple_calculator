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

// calculates an expression and returns the result
double calculate(const double&, const double&, const char&);

// clears expression
void clear_expression(string&) noexcept;

// returns the part of the expression that must be computed first
string parse_expression(const string&) noexcept;

// computes expression
string compute_expression(string);