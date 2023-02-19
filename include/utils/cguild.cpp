

#include "utl.hpp"
#include <string>
#include <type_traits>
#include <vector>

using namespace dpp;

utl::fracNum evalStr(std::string inStr) {
    return (utl::fracNum(inStr));
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
    this->curGuild = gId;
    
}
void cGuild::forceChange() { this->currentValue = this->curStart - this->curStep; }



void cGuild::onMsg(message inMsg) {
    std::cout << inMsg.content << std::endl;
    std::cout << "Looking for: " << (this->currentValue + this->curStep).toStr() << std::endl;
	if (inMsg.author.id != this->curUser) {
		bool isCor;

		try {
			isCor = this->isCorrect(inMsg.content);
			if (this->prefChan == uint64_t(0)) { this->prefChan = inMsg.channel_id; }
		} catch (...) { return; }

		if (isCor) {
			this->bot->message_add_reaction(inMsg,"✅");
			//this->currentValue += this->curStep;
            this->currentValue = this->currentValue + this->curStep;

		} else {

			this->bot->message_add_reaction(inMsg,"❌");
			this->curLives -= 1;

			if (this->curLives <= 0) {
				this->currentValue = this->curStart-this->curStep;
				this->curLives = 1;
				this->bot->message_create(message(inMsg.channel_id,(inMsg.author.get_mention() + " got the count wrong, you have no more lives left, starting count at " + (this->curStart).toStr())));
			} else {
				this->bot->message_create(message(inMsg.channel_id,(inMsg.author.get_mention() + " got the count wrong, you have " + std::to_string(this->curLives) + " left, last count was " + this->currentValue.toStr())));
			}


		}
        this->curUser = inMsg.author.id;
        this->onUpdate();
	} else {
		this->bot->message_add_reaction(inMsg,"⚠️");
	}
    std::cout << "Looking for: " << (this->currentValue + this->curStep).toStr() << std::endl;

}

bool cGuild::isCorrect(std::string inStr) {

	return (evalStr(inStr) == (this->currentValue + this->curStep));
	
}

void cGuild::forceReset() {
	this->currentValue = this->curStart - this->curStep;
	this->curLives = this->startLives;
	this->curUser = 0;
	this->highValue = this->curStart;
	this->bot->message_create(message(this->prefChan,("Current count has been reset to " + this->curStart.toStr() + " incrementing by " + this->curStep.toStr() + " you have " + std::to_string(this->curLives) + " lives, good luck!")));
    this->onUpdate();
}


void cGuild::setStart(utl::fracNum inD) {
    this->curStart = inD;
    //std::cout << this->curStart << " is start \n";
}
void cGuild::setCount(utl::fracNum inD) {
    this->curStep = inD;
    //std::cout << this->curStep << " is count \n";
}
void cGuild::setLives(int inInt) {
    this->startLives = inInt;
}

void cGuild::setPrefChan(snowflake inSnow) {
    this->prefChan = inSnow;
}


}
