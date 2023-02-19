#include <vector>
#include <string>
#include <gmp.h>
#include <gmpxx.h>
#include "fracnum.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

using bigInt = mpz_class;

bigInt tPower(int power) {
    bigInt tVal = 1;
    if (power > 0) {
        for (int i = 0; i < power; i++) { tVal *= 10; }
    } else if (power < 0) {
        for (int i = 0; i > power; i--) { tVal /= 10; }
    }
    return tVal;
}

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

namespace fNum {

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
    this->getRep();
    std::cout << conStr << std::endl;
    std::string curStr = tNum(conStr);
    std::cout << curStr << std::endl;
	int64_t dPos = curStr.find(".");
    
	std::string rStr = "";
	std::erase(curStr,'.');
    rStr = curStr;
	std::cout << "rStr is: " << rStr << std::endl;
    this->baseVal = bigInt(rStr);
    std::cout << "dpos is: " << dPos << std::endl;
	if (dPos == std::string::npos) { this->power = 0; }
    else if (dPos == 0) { this->power = (-1) * curStr.length(); }
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
    std::cout << "npos is: " << std::string::npos << std::endl;
	this->conStr(inStr);
}

fracNum::fracNum(long double inD) {
    
	this->conStr(std::to_string(inD));
}

std::string fracNum::toStr() {
    this->getRep();
	std::string rStr = this->baseVal.get_str();
	if (this->power > 0) {
		for (int i = this->power; i > 0; i--) {
			rStr.push_back('0');
		}
	} else if (this->power < 0) {
		if (this->power + rStr.length() > 0) { rStr.insert((rStr.length()+this->power),"."); }
        else { rStr.insert(0,"0."); } 
	}
	return rStr;
}

void fracNum::simplify() {
	while ((this->baseVal % 10) == 0) {
		this->baseVal /= 10;
		this->power -= 1;
	}
}


fracNum fracNum::operator + (const fracNum& obj) {
	this->getRep();
	if (this->power > obj.power) {
		fracNum tempNum = *this;
		tempNum.baseVal = this->baseVal+(obj.baseVal*(tPower(this->power-obj.power)));
		return tempNum;
	} else if (this->power == obj.power) {
		fracNum tempNum = *this;
		tempNum.baseVal = this->baseVal+obj.baseVal;
		return tempNum;
	} else {
		fracNum tempNum = obj;
		tempNum.baseVal = obj.baseVal+(this->baseVal*(tPower(obj.power-this->power)));
		return tempNum;
	}	
}

fracNum fracNum::operator * (const fracNum& obj) {
    this->getRep();
	fracNum tempNum = *this;
	tempNum.baseVal *= obj.baseVal;
	tempNum.power += obj.power;
	return tempNum;
}

fracNum fracNum::operator - (const fracNum& obj) {
	this->getRep();
	if (this->power > obj.power) {
		fracNum tempNum = *this;
		tempNum.baseVal = (this->baseVal*(tPower(this->power-obj.power)))-obj.baseVal;
        return tempNum;
	} else if (this->power == obj.power) {
		fracNum tempNum = *this;
		tempNum.baseVal = this->baseVal-obj.baseVal;
        return tempNum;
	} else {
		fracNum tempNum = obj;
		tempNum.baseVal = this->baseVal-(obj.baseVal*(tPower((obj.power-this->power))));
        return tempNum;
	}
	
}
bool fracNum::operator == (const fracNum& obj) {
    this->getRep();
	bool tempB;
	if (this->power > obj.power) {
		tempB = ((this->baseVal*(tPower(this->power-obj.power)))==obj.baseVal);
	} else if (this->power == obj.power) {
		tempB = (this->baseVal==obj.baseVal);
	} else {
		tempB = (this->baseVal==(obj.baseVal*(tPower((obj.power-this->power)))));
	}
	return tempB;

}

void fracNum::getRep() {
    std::cout << this->baseVal.get_str() << "*(10^" << std::to_string(this->power) << ")\n";
}



}



