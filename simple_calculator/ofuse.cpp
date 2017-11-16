#include "ofuse.h"

#include<sstream>
using std::stringstream;

#include<iomanip>
using std::setprecision;

#include<limits>
using std::numeric_limits;

#include<stdexcept>
using std::runtime_error;

// converts a double into a string value
string to_string(const double& val) 
// converts a double val into a string value
{
	stringstream ss;
	ss << setprecision(numeric_limits<double>::digits10) << val;
	return ss.str();
}

// converts a char into an int
int to_int(const char& c) 
// converts a char c into an int value
// throws an exception if the conversion failed
{
	stringstream ss;
	ss << c;
	int result { 0 };
	ss >> result;
	if (!ss)
		throw runtime_error("unable to convert char to int.");
	return result;
}

// converts a string into a double
double to_double(const string& s) 
// converts a string s into a double.
// throws an exception if the conversion failed
{
	stringstream ss;
	ss << s;
	double result{ 0.0 };
	ss >> result;
	if (!ss)
		throw runtime_error("unable to convert char to double.");
	return result;
}