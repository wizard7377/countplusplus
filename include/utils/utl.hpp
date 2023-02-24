#pragma once

#include <dpp/dpp.h>
#include <vector>
#include <string>
#include <gmpxx.h>
#include "fracnum.hpp"

using namespace dpp;

using bigInt = mpz_class;

namespace utl {

//form is base * (10 ^ power)
/*
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
*/


class cGuild {
	public:
		cGuild(snowflake gId,cluster * botPar,snowflake goodChan = 0);
		fNum::fracNum currentValue = 1;
		fNum::fracNum highValue = 1;
		fNum::fracNum curStep = 1;
		fNum::fracNum curStart = 1;
		int curLives = 1;
		int startLives = 1;
		snowflake prefChan = 0;
		snowflake curUser;
		void onMsg(message inMsg);
		void setStart(fNum::fracNum inD);
		void setCount(fNum::fracNum inD);
		void setLives(int inInt);
		void setPrefChan(snowflake inSnow);
		void forceReset();
		void forceChange();
		snowflake curGuild;
		std::function<void()> onUpdate;

	private:
		cluster * bot;
		bool isCorrect(std::string inStr);
		
		
		
		


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
