#include <vector>
#include <string>
#include <gmp.h>
#include <gmpxx.h>
#include "utl.hpp"
#include <algorithm>
#include <cmath>

using bigInt = mpz_class;

std::string tNum(std::string inStr) {
	while (inStr.front() == '0') {
		inStr.erase(0,1);
	}
	if (inStr.find(".") != std::string::npos) {
		while (inStr.back() == '0') {
			inStr.pop_back();
		}
	}
	if (inStr.back() == '.') { inStr.pop_back(); }
	return inStr;
}

namespace utl {

/*
class fracNum {
	public:
		fracNum(std::string inStr);
		fracNum(long double inD);
		fracNum operator + (const fracNum& obj);
		fracNum operator - (const fracNum& obj);
		fracNum operator == (const fracNum& obj);
		std::string toStr();
		long double toDouble();
	private:
		bigInt baseVal;
		int64_t power;

};
*/

void fracNum::conStr(std::string conStr) {
    std::string curStr = tNum(conStr);
	int64_t dPos = curStr.find(".");

	std::string rStr = "";
	std::remove_copy(curStr.begin(),curStr.end(),rStr.begin(),'.');
	this->baseVal = bigInt(rStr);

	if (dPos == std::string::npos) { this->power = 0; }
	else if (dPos > 0) { this->power = dPos-curStr.length(); }
	else {
		for (int i = 1; i < rStr.length(); i++) {
			if (rStr[i] != '0') {
				this->power = (-1) * i;
				break;
			}
		}
	}
}

fracNum::fracNum(std::string inStr) {
	this->conStr(inStr);
}

fracNum::fracNum(long double inD) {
	this->conStr(std::to_string(inD));
}

std::string fracNum::toStr() {
	std::string rStr = this->baseVal.get_str();
	if (this->power > 0) {
		for (int i = this->power; i > 0; i--) {
			rStr.push_back('0');
		}
	} else if (this->power < 0) {
		rStr.insert(((rStr.length()-1)+this->power),".");
	}
	return rStr;
}


fracNum fracNum::operator + (const fracNum& obj) {
	
	if (this->power > obj.power) {
		fracNum tempNum = *this;
		tempNum.baseVal = this->baseVal+(obj.baseVal*(std::pow(10,(this->power-obj.power))));
        return tempNum;
	} else if (this->power == obj.power) {
		fracNum tempNum = *this;
		tempNum.baseVal = this->baseVal+obj.baseVal;
        return tempNum;
	} else {
		fracNum tempNum = obj;
		tempNum.baseVal = obj.baseVal+(this->baseVal*(std::pow(10,(obj.power-this->power))));
        return tempNum;
	}
	
}
fracNum fracNum::operator - (const fracNum& obj) {
	
	if (this->power > obj.power) {
		fracNum tempNum = *this;
		tempNum.baseVal = (this->baseVal*(std::pow(10,(this->power-obj.power))))-obj.baseVal;
        return tempNum;
	} else if (this->power == obj.power) {
		fracNum tempNum = *this;
		tempNum.baseVal = this->baseVal-obj.baseVal;
        return tempNum;
	} else {
		fracNum tempNum = obj;
		tempNum.baseVal = this->baseVal-(obj.baseVal*(std::pow(10,(obj.power-this->power))));
        return tempNum;
	}
	
}
bool fracNum::operator == (const fracNum& obj) {
	bool tempB;
	if (this->power > obj.power) {
		tempB = ((this->baseVal*(std::pow(10,(this->power-obj.power))))==obj.baseVal);
	} else if (this->power == obj.power) {
		tempB = (this->baseVal==obj.baseVal);
	} else {
		tempB = (this->baseVal==(obj.baseVal*(std::pow(10,(obj.power-this->power)))));
	}
	return tempB;

}



}



