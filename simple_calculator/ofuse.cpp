#include "ofuse.h"

#include<sstream>
using std::stringstream;

#include<iomanip>
using std::setprecision;

#include<limits>
using std::numeric_limits;

#include<stdexcept>
using std::runtime_error;

// converts a double into a string
string to_string(const double& d) {
	stringstream ss;
	ss << setprecision(numeric_limits<double>::digits10) << d;
	return ss.str();
}

// tests if a number is a positive integer
bool is_positive_integer(const double& d)
// checks if a number d is a non-negative integer
// returns true if it's the case
// returns false otherwise
{
	int i = int(d);
	if (d != double(i) || d < 0)
		return false;

	return true;
}

// computes a factorial
double factorial(const double& n)
// computes the factorial n!
// n is a non-negative integer
// returns the product of all positive integers less than or equal to n
{
	if (!is_positive_integer(n))
		throw runtime_error("expected non-negative integer argument.");

	if (n > 1)
		return n * factorial(n - 1);
	else
		return 1;
}