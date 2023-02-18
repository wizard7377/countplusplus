#include "utl.hpp"
#include <string>
#include <vector>

using namespace dpp;

long double evalStr(std::string inStr) {
    return (std::stold(inStr));
}


namespace utl {

cGuild::cGuild(snowflake gId,cluster * botPar) {
	this->bot = botPar;
}

void cGuild::onMsg(message inMsg) {
	bool isCor;

	try {
		isCor = this->isCorrect(inMsg.content);
	} catch (...) { return; }

	if (isCor) {
		this->bot->message_add_reaction(inMsg,"✅");
	} else {
		this->bot->message_add_reaction(inMsg,"❌");
	}
}

bool cGuild::isCorrect(std::string inStr) {
	if (evalStr(inStr) == (this->currentValue + this->curStep)) {
		this->currentValue += this->curStep;
		return true;
	} else {
		this->curLives -= 1;
		if (this->curLives <= 0) {
			this->currentValue = 1;
			this->curLives = 1;
		}
		return false;
	}
}



}