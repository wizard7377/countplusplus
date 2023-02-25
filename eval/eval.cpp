
#include "eval.hpp"
#include <string>
#include "fracnum.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>

#include <iostream>

extern int evalF(const char * string);

//std::regex numReg("((?:(?<=(?:[(|]))-)?(?:\\d+(?:\\.\\d*)?))");
//std::regex numReg("((?:(?<=(?:[\\(\\|]))-)?(?:\\d+(?:\\.\\d*)?))");
//std::regex numReg(".*");

long double pErr(long double mIn, long double aIn) {
	return ((mIn-aIn)/aIn);
}

bool evalString(std::string inStr,fNum::fracNum inNum) {
	long double curNum = std::stold(inNum.toStr());
	long double gVal = evalF(inStr.c_str());
	return (pErr(gVal,curNum) < 0.01);
}

