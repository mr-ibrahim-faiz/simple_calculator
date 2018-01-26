#include "simple_calculator.h"
#include "token.h"

#include<iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::streamsize;

#include<stdexcept>
using std::runtime_error;

#include<limits>
using std::numeric_limits;

int main() {

	while (true) {
		cout << "> ";
		Token result;

		try {
			// checks if the user wants to exit the program
			if (is_exit())
				break;

			// gets and computes expression
			result = expression();

			// displays result
			if (is_valid(result) && (cin.peek() == '\n'))
				cout << result << endl;
			else
				throw runtime_error("invalid expression.");

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		catch (runtime_error& e) {
			cerr << "Error: " << e.what() << endl;
			if (!cin)
				cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		cout << endl;
	}

	cout << "\nGoodbye !" << endl;

	return 0;
}