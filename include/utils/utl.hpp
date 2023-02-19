#pragma once

#include <dpp/dpp.h>
#include <vector>
#include <string>

using namespace dpp;



namespace utl {

class cGuild {
	public:
		cGuild(snowflake gId,cluster * botPar,snowflake goodChan = 0);
		long double currentValue = 1;
		long double highValue = 1;
		long double curStep = 1;
		long double curStart = 1;
		int curLives = 1;
		int startLives = 1;
		snowflake curUser;
		void onMsg(message inMsg);
		void setStart(long double inD);
		void setCount(long double inD);
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
