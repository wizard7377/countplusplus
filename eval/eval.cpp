
#include "eval.hpp"
#include <string>
#include "fracnum.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>

#include <iostream>

extern double returnVal(std::string expr);

//std::regex numReg("((?:(?<=(?:[(|]))-)?(?:\\d+(?:\\.\\d*)?))");
//std::regex numReg("((?:(?<=(?:[\\(\\|]))-)?(?:\\d+(?:\\.\\d*)?))");
//std::regex numReg(".*");

long double pErr(long double mIn, long double aIn) {
	return (std::abs((mIn-aIn)/aIn));
}

bool evalString(std::string inStr,fNum::fracNum inNum) {
	//long double curNum = std::stold(inNum.toStr());
	double gVal = returnVal("(" + inStr + ")");
	std::cout << "\n\ngVal is: " + std::to_string(gVal) << ".\n\n";
	//std::cout << std::endl << gVal << std::endl << std::endl;
	//std::cout << pErr(gVal,curNum) << std::endl;
	//return (pErr(gVal,curNum) < 0.01);
	return false;
}

