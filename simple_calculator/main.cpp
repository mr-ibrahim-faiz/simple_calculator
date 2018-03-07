#include "token.h"
#include "ofuse.h"
#include "simple_calculator.h"

#include<iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::streamsize;

#include<limits>
using std::numeric_limits;

#include<stdexcept>
using std::exception;

// defines a token stream which provides get() and putback()
Token_stream ts;

int main()
try
{
	const string prompt { "> " };
	while (true) {
		cout << prompt; // prompts the user to enter expression

		// checks if the user wants to exit the program
		if (is_exit())
			break;

		try {
			calculate();
		}
		catch (Bad_token& e) {
			cerr << "Error: " << e.what() << endl;

			if (!cin)
				cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// clears the token_stream state
			if (ts.full())
				ts.clear();
		}

		cout << endl;

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