#include "simple_calculator.h"

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

		// checks if the user want to quit the program
		// exits if the user enters "exit"
		if (expression == "exit")
			break;

		// clear expression
		clear_expression(expression);

		try {
			// check if the expression is valid before computing it
			if (is_valid(expression)) {

				// the following block is execute when the expression contains parentheses
				while (count_parentheses(expression) > 0) {

					// parses the expression an retrieves the part of the expression that needs to be computed first
					string computation_unit = parse_expression(expression);

					// retrieves the index where the computation unit was found
					size_t cu_idx = expression.find('(' + computation_unit);
					++cu_idx;

					// gets the length of the computation unit including parentheses
					size_t length = computation_unit.length() + 2;

					// computes the computation unit
					string computed_expression = compute_expression(computation_unit);

					// delete the computation unit from the main expression and replace it by its result
					expression.erase(cu_idx - 1, length);
					expression.insert(cu_idx - 1, computed_expression);
				}

				// displays final result
				cout << atof(compute_expression(expression).c_str()) << endl;
				cout << endl;
			}
			else {
				cout << "Error: invalid expression." << endl;
				cout << endl;
			}
		}
		catch (runtime_error& e) {
			cerr << "Error: " << e.what() << endl;
			cerr << endl;
		}

	}

	cout << "\nGoodbye !" << endl;
	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
}
catch (...) {
	cerr << "Error: unknown exception caught." << endl;
}