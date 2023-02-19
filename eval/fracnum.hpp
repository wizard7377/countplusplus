#pragma once

#include <vector>
#include <string>
#include <gmpxx.h>



using bigInt = mpz_class;

namespace fNum {

//form is base * (10 ^ power)
class fracNum {
	public:
		fracNum(std::string inStr);
		fracNum(long double inD);
		fracNum operator + (const fracNum& obj);
		fracNum operator - (const fracNum& obj);
		fracNum operator * (const fracNum& obj);
		bool operator == (const fracNum& obj);
		std::string toStr();
		long double toDouble();
		void simplify();
	private:
		bigInt baseVal;
		int64_t power;
		void conStr(std::string conStr);
		void getRep();
};




}
