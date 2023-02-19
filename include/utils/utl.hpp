#pragma once

#include <dpp/dpp.h>
#include <vector>
#include <string>
#include <gmpxx.h>

using namespace dpp;

using bigInt = mpz_class;

namespace utl {

//form is base * (10 ^ power)
class fracNum {
	public:
		fracNum(std::string inStr);
		fracNum(long double inD);
		fracNum operator + (const fracNum& obj);
		fracNum operator - (const fracNum& obj);
		bool operator == (const fracNum& obj);
		std::string toStr();
		long double toDouble();
	private:
		bigInt baseVal;
		int64_t power;
		void conStr(std::string conStr);
};


class cGuild {
	public:
		cGuild(snowflake gId,cluster * botPar,snowflake goodChan = 0);
		utl::fracNum currentValue = 1;
		utl::fracNum highValue = 1;
		utl::fracNum curStep = 1;
		utl::fracNum curStart = 1;
		int curLives = 1;
		int startLives = 1;
		snowflake curUser;
		void onMsg(message inMsg);
		void setStart(utl::fracNum inD);
		void setCount(utl::fracNum inD);
		void setLives(int inInt);
		void setPrefChan(snowflake inSnow);
		void forceReset();

	private:
		cluster * bot;
		bool isCorrect(std::string inStr);
		
		snowflake prefChan = 0;
		


};

class point {
	public:
		point(int inX,int inY,int inSize = 64);
		point(int inIndex,int inSize, bool xIsOne);
		std::string tString();
		int getVal(bool xIsOne = false);
		int x, y, size;
};

class bigSelect {

	public:
		bigSelect(std::vector<std::string> startVals);
		std::vector<component*> selectMenus;
		int curPage = 0;
		int numPage = 0;
		component pageUp();
		component pageDown();
		component pageStay();
		bool canPage[2] = {true,true};
	private:
		void changePage();
};

}
