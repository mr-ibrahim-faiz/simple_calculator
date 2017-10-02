#include "simple_calculator.h"
#include "token.h"

#include<vector>
using std::vector;

#include<iostream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;

#include<stdexcept>
using std::exception;
using std::runtime_error;

int main()
try
{
	string expression { "" };

	while (true)
	{
		// gets expression from input
		cout << "> ";
		getline(cin, expression);

		// checks if the user wants to quit the program
		// exits if the user enters "exit"
		if (expression == "exit")
			break;

		// clears expression
		clear_expression(expression);

		try {
			// tokenizes expression
			vector<Token> tokens = tokenize(expression);

			// parses the expression and computes it
			while (contains_parenthesis(tokens)) {
				// indexes of parentheses
				vector<size_t> parentheses_index(2);

				// gets the part of the expression that should be computed first
				vector<Token> computation_unit = parse_expression(tokens, parentheses_index);

				// computes the computation unit, pushes the result into the initial expression
				// and removes the computation unit tokens from the initial expression
				tokens[parentheses_index[0]] = compute_expression(computation_unit);
				tokens.erase(tokens.begin() + parentheses_index[0] + 1, tokens.begin() + parentheses_index[1] + 1);
			}

			// displays final result
			cout << compute_expression(tokens).name() << endl;
			cout << endl;
		}
		catch (Bad_token& e) {
			cerr << "Error: " << e.what() << endl;
			cerr << endl;
		}
	}

	cout << "\nGoodbye !" << endl;
	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Error: unknown exception caught." << endl;
	return 2;
}