#include "simple_calculator.h"

#include<stdexcept>
using std::runtime_error;

#include<algorithm>
using std::remove_if;

#include<vector>
using std::vector;

#include<string>
using std::to_string;

// counts parentheses
size_t count_parentheses(const string& expression) 
// counts the number of parentheses found in an expression
// returns the number of parentheses
{
	size_t result { 0 };
	for (size_t i = 0; i < expression.size(); ++i) {
		if (expression[i] == '(' || expression[i] == ')')
			++result;
		else {}
	}

	return result;
}

// checks parentheses
bool check_parentheses(const string& expression) 
// returns true if nothing is wrong with the parentheses
// i.e odd number of parentheses, unclosed parentheses
{
	int result { 0 };
	for (size_t i = 0; i < expression.size(); ++i) {
		if (expression[i] == '(')
			++result;
		else if (expression[i] == ')')
			--result;
		else {}
	}

	if (result == 0)
		return true;

	return false;
}

// counts operators
size_t count_operators(const string& expression) 
// counts the number of operators found in an expression
// returns the number of operators
{
	size_t result { 0 };
	for (size_t i = 0; i < expression.size(); ++i) {
		switch (expression[i]) {
		case '+': case '-': case '/': case '*':
			++result;
			break;
		default:
			break;
		}
	}
	return result;
}

// checks if a char is a representation of a digit
bool is_a_digit(const char& c) 
// checks if the argument is the representation of a digit [0, 10)
// returns true if the argument is the representation of a digit
{
	switch (c)
	{
	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9':
		return true;
	default:
		return false;
	}
}

// checks if an expression is valid
bool is_valid(const string& expression) 
// checks if an expression is valid by using a set of rules
// i.e. number of parentheses, invalid characters, etc
// returns true if everything is fine according to these rules
{
	// length of the expression
	size_t length = expression.size();

	// returns false if there's something wrong with the parentheses
	if (!check_parentheses(expression))
		return false;

	// returns false if the first character cannot be represented as a digit,
	// exceptions: the first character can be '+', '-', '.' or '('
	switch (expression[0])
	{
	case '+': case '-': case '(': case '.':
		break;
	default:
		if (!is_a_digit(expression[0]))
			return false;
		break;
	}

	// returns false if the last character cannot be represented as a digit
	// exceptions: the last character can be ')' or '.'
	if (!is_a_digit(expression[length - 1])) {
		switch (expression[length - 1]) {
		case ')': case '.':
			break;
		default:
			return false;
		}
	}

	// returns false if two caracters are following each other
	for (size_t i = 0; i < length - 1; ++i) {
		// if the current character can be represented as a digit, it is ignored
		if (is_a_digit(expression[i]))
			continue;

		// if an invalid float (such as .1.2.) is detected, it returns false
		if (expression[i] == '.') {
			size_t j = i + 1;
			while (expression[j++]) {
				// if the current character can be represented as a digit, it is ignored
				if (is_a_digit(expression[j - 1]))
					continue;
				// returns false if a second '.' is found in an operand
				else if (expression[j - 1] == '.')
					return false;
				else
					break;
			}
		}

		// returns false if two caracters which are not allowed to follow each other follow each others
		switch (expression[i]) {
		case '*': case '/': case '+': case '-':
			// accepts *(, /(, +(, -(, *., /., +., -.
			// refuses for example *) or *L
			if (expression[i + 1] == '(');
			else if (expression[i + 1] == '.');
			else
				if (!is_a_digit(expression[i + 1]))
					return false;
		case '(':
			// accepts (+, (-, ((, (.
			// refuses for example (* or (L
			switch (expression[i + 1]) {
			case '+': case '-': case '(': case '.':
				break;
			default:
				if (!is_a_digit(expression[i + 1]))
					return false;
			}
			break;

		case ')': case '.':
			// accepts )+, )-, )*, )/, )), .+, .-, .*, ./, .)
			// refuses for example )( or .L
			switch (expression[i + 1]) {
			case '+': case '-': case '*': case '/': case ')':
				break;
			default:
				if (!is_a_digit(expression[i + 1]))
					return false;
			}
			break;

		default:
			// if the current character is not a valid character, returns false
			return false;
			break;
		}
	}

	return true;
}

// calculates an expression and returns the result
double calculate(const double& first, const double& second, const char& op) 
// calculates an expression and returns the result
// supports only the operators +, -, /, and *
// throws a division by zero exception when detected
{
	switch (op) {
	case '+':
		return first + second;
	case '-':
		return first - second;
	case '*':
		return first * second;
	case '/':
		if (second == 0)
			throw runtime_error("division by zero.");
		return first / second;
	default:
		throw runtime_error("unsupported operator.");
	}
}

// clears expression
void clear_expression(string& expression) 
// clears expression passed as argument by removing whitespaces, changing 'x' to '*' and ':' unto '/'
{
	// remove whitespaces from expression
	expression.erase(remove_if(expression.begin(), expression.end(), isspace), expression.end());

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

// returns the part of the expression that must be computed first
string parse_expression(const string& expression) 
// parse the expression by analyzing the parentheses and returns the part of the
// expression that must be computed first
// if there's no parentheses, the argument expression is returned as is
{
	string parsed_expression{ "" };
	size_t idx = expression.find("(");

	if (idx != string::npos) {
		++idx;
		while (expression[idx] != ')') {
			if (expression[idx] == '(')
				parsed_expression = "";
			else
				parsed_expression.push_back(expression[idx]);
			++idx;
		}
	}

	return parsed_expression;
}

// computes expression
string compute_expression(string expression) 
// computes the expression passed as argument, 
// parses and calcultates expression
// returns the result as a string
{
	// declare a vector containing all operators.
	vector<char> operators = { '/', '*', '-', '+' };

	// for each operator op in operators
	// determines the left and right operands and calculates "left op right"
	for (char op : operators) {
		// retrieves the index where the operator was found
		size_t op_idx = expression.find(op);

		while (op_idx != string::npos) {
			string computation_unit { op };
			string left { "" };
			string right { "" };

			int j = op_idx + 1;
			// here j>=0 is used as a condition here so we can't break the following loop in case '-'
			while (j >= 0 && (is_a_digit(expression[j]) || expression[j] == '.' || expression[j] == '(' || expression[j] == ')' || expression[j] == '-'))
				switch (expression[j]) {
				case '(':
					right.push_back(expression[j++]);
					while (!check_parentheses(right))
						right.push_back(expression[j++]);
					break;
				case '-':
					// check cases such as 2*-8
					if (j == op_idx + 1)
						right.push_back(expression[j++]); // test
					else
						j = -1;
					break;
				default:
					right.push_back(expression[j++]);
					break;
				}

			j = op_idx - 1;
			while (j >= 0 && (is_a_digit(expression[j]) || expression[j] == '.' || expression[j] == '(' || expression[j] == ')' || expression[j] == '-'))
			{
				switch (expression[j]) {
				case ')':
					left.insert(left.begin(), expression[j--]);
					while (!check_parentheses(left))
						if (j >= 0)
							left.insert(left.begin(), expression[j--]);
					break;
				case '-':
					// checks cases such as 3*-2 or -2 
					if (j - 1 >= 0)
						switch (expression[j - 1]) {
						case '/': case '*': case '+': case '-':
							left.insert(left.begin(), expression[j--]);
							break;
						default:
							j = -1;
							break;
						}
					else
						left.insert(left.begin(), expression[j--]);
					break;
				default:
					left.insert(left.begin(), expression[j--]);
					break;
				}
			}

			// converts strings to float and calculate the result
			double dright = atof(right.c_str());
			double dleft = atof(left.c_str());
			double result = calculate(dleft, dright, op);

			computation_unit += right;
			left += computation_unit;
			computation_unit = left;

			// retrieves the index where the computation unit was found
			size_t cu_idx = expression.find(computation_unit);

			// saves the last expression to avoid loops with cases such as -1-2
			string last_expression = expression;

			// delete the computation unit from the main expression and replace it by its result
			expression.erase(cu_idx, computation_unit.length());
			expression.insert(cu_idx, to_string(result));

			// retrieves the index where the operator was found
			// to avoid loop, last_expression is compared to expression
			if (last_expression == expression)
				op_idx = expression.find(op, op_idx + 1);
			else
				op_idx = expression.find(op);

		}
	}

	return expression;
}