#include "utl.hpp"
#include <string>
#include <vector>

using namespace dpp;

long double evalStr(std::string inStr) {
    return (std::stold(inStr));
}

std::string dToStr(long double inDouble) {
	std::string tStr = std::to_string(inDouble);

	while (tStr.back() != '.') {
		if (tStr.back() == '0') { tStr.pop_back(); }
		else { return tStr; }
	}
	tStr.pop_back();
	return tStr;
}



namespace utl {


cGuild::cGuild(snowflake gId,cluster * botPar,snowflake goodChan) {
    this->prefChan = goodChan;
    this->bot = botPar;
    this->currentValue = this->curStart - this->curStep;
	this->curLives = this->startLives;
	this->curUser = 0;
	this->highValue = this->curStart;
}



void cGuild::onMsg(message inMsg) {
	if (inMsg.author.id != this->curUser) {
		bool isCor;

		try {
			isCor = this->isCorrect(inMsg.content);
			if (this->prefChan == uint64_t(0)) { this->prefChan = inMsg.channel_id; }
		} catch (...) { return; }

		if (isCor) {
			this->bot->message_add_reaction(inMsg,"✅");
			this->currentValue += this->curStep;

		} else {

			this->bot->message_add_reaction(inMsg,"❌");
			this->curLives -= 1;

			if (this->curLives <= 0) {
				this->currentValue = this->curStart-this->curStep;
				this->curLives = 1;
				this->bot->message_create(message(inMsg.channel_id,(inMsg.author.get_mention() + " got the count wrong, you have no more lives left, starting count at " + dToStr(this->curStart))));
			} else {
				this->bot->message_create(message(inMsg.channel_id,(inMsg.author.get_mention() + " got the count wrong, you have " + std::to_string(this->curLives) + " left, last count was " + dToStr(this->currentValue))));
			}


		}
        this->curUser = inMsg.author.id;
	} else {
		this->bot->message_add_reaction(inMsg,"⚠️");
	}

}

bool cGuild::isCorrect(std::string inStr) {
    std::cout << inStr << " as opposed to " << (this->currentValue + this->curStep) << " is correct \n\n";
	return (evalStr(inStr) == (this->currentValue + this->curStep));
	
}

void cGuild::forceReset() {
	this->currentValue = this->curStart - this->curStep;
	this->curLives = this->startLives;
	this->curUser = 0;
	this->highValue = this->curStart;
	this->bot->message_create(message(this->prefChan,("Current count has been reset to " + dToStr(this->curStart) + " incrementing by " + dToStr(this->curStep) + " you have " + std::to_string(this->curLives) + " lives, good luck!")));
}


void cGuild::setStart(long double inD) {
    this->curStart = inD;
    std::cout << this->curStart << " is start \n";
}
void cGuild::setCount(long double inD) {
    this->curStep = inD;
    std::cout << this->curStep << " is count \n";
}
void cGuild::setLives(int inInt) {
    this->startLives = inInt;
}

void cGuild::setPrefChan(snowflake inSnow) {
    this->prefChan = inSnow;
}


}
