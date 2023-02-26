

#include "driver.hh"
#include "parser.hpp"
#include <string>
#include <vector>

std::vector<std::string> vecStr(std::string inStr) {
	std::vector<std::string> tVec = {};
	std::string curStr = "";
	for (char a: inStr) {
		if (a != ';') {
			curStr = curStr + a;
		} else {
			tVec.push_back(curStr);
			curStr = "";
		}
	}
	return tVec;
}

driver::driver ()
  : trace_parsing (false), trace_scanning (false)
{
  variables["one"] = 1;
  variables["two"] = 2;
}

int driver::parse (const std::string &f)
{
	/*
	std::string fullStr = f;
	std::vector<std::string> pLines = vecStr(fullStr);
	for (auto a: pLines) {
		file = a;
		location.initialize (&file);
		scan_begin ();
		yy::parser parse (*this);
		parse.set_debug_level (trace_parsing);
		int res = parse ();
		scan_end ();
		if (res != 0) { return res; }
	}
	*/
	std::cout << f << std::endl;
	file = f;
	location.initialize (&file);
	scan_begin ();
	yy::parser parse (*this);
	parse.set_debug_level (trace_parsing);
	int res = parse ();
	scan_end ();
	
	return res;
}

double returnVal(std::string expr) {
	driver drv;
	std::cout << expr << "\n\n";
   	/*for (char a: expr) {
		if (!(drv.parse (std::string(1,a)) == 0)) { throw 1; } 
	}*/
	if (!(drv.parse (expr) == 0)) { throw 1; }  
    return drv.resVal;
}
