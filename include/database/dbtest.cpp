#include "databaselogic.hpp"
#include <iostream>
#include <dpp/dpp.h>
#include <mysql.h>
#include "config.hpp"
#include <thread>
#include <functional>

using namespace std;
	
using cGuild = utl::cGuild;
using fracNum = utl::fracNum;

namespace mData {

dataHandle::dataHandle(cluster * botPar) {
	this->bot = botPar;
	this->dataCon = NULL;
	try {
		mysql_library_init(0,NULL,NULL);
		this->dataCon = mysql_init(this->dataCon);
	} catch (...) {
		std::cout << "error occured in database init \n";
		exit(0);
	}
	std::cout << "Database init succeded" << std::endl;
	try {
		mysql_real_connect(this->dataCon,MYOP_HOST,MYOP_USER,MYOP_PASS,MYOP_DATA,MYOP_PORT,MYOP_SOCK,MYOP_FLAG);
	} catch (...) {
		std::cout << "Error conn \n";
	}
	
	//this->dataCon = NULL;
 
}

int dataHandle::getCount(fracNum rCount, fracNum rStart, int rLives) {
	std::string curQ = "";
	try {
		curQ = ("SELECT id FROM countIds WHERE currentJump = \"" + rCount.toStr() + "\" AND currentStart = \"" + rStart.toStr() + "\" AND numLives = " + to_string(rLives) + ";"); 		
		std::cout << curQ << " at: " << __LINE__ << "\n";
		mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());

		MYSQL_RES * result = mysql_store_result(this->dataCon);
		
		if (mysql_num_rows(result) > 0) {	
			MYSQL_ROW resRow = mysql_fetch_row(result);
			int tInt = stoi(resRow[0]);
			mysql_free_result(result);
			return tInt;
		} else {		
			curQ = ("INSERT INTO countIds(currentJump,currentStart,numLives) VALUES (\"" +  rCount.toStr() + "\",\"" + rStart.toStr() + "\"," + to_string(rLives) + ");");
			mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());
			return (mysql_insert_id(this->dataCon));	
		}	
	} catch (...) {
		std::cout << "An error has occured \n";
	}
	return 0;



}

utl::cGuild * dataHandle::getGuild(snowflake guildId) {
	std::string curQ = "";
	cGuild * curG = new cGuild(guildId,this->bot);
	curG->onUpdate = [this,curG] { this->updateGuild(*curG); }; 
	try {
		curQ = ("SELECT * FROM guildIds WHERE guildId = "  + std::to_string(guildId) + " LEFT JOIN countIds ON guildIds.curCount = countIds.id;"); 		
		std::cout << curQ << " at: " << __LINE__ << "\n";
		mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());

		MYSQL_RES * result = mysql_store_result(this->dataCon);
		if (result == 0) { return curG; }
		if (mysql_num_rows(result) > 0) {
			
			MYSQL_ROW resRow = mysql_fetch_row(result);
			std::cout << mysql_num_rows(result) << std::endl;
			std::cout << mysql_num_fields(result) << std::endl;
			curG->setCount(fracNum(resRow[2]));
			curG->setStart(fracNum(resRow[9]));
			curG->setLives(stoi(resRow[3]));
			curG->setPrefChan(stoull(resRow[6]));
			curG->startLives = stoi(resRow[1]);
			curG->curUser = (stoull(resRow[6]));
			mysql_free_result(result);
		} else {
			curQ = ("INSERT INTO guildIds (guildId,curVal,curLives,curCount,curUser,defChan) VALUES (" + to_string(guildId) + "\"1\",1,1,NULL,NULL);");
			mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());
			
		}
			
	
	} catch (...) {
		std::cout << "An error has occured \n";
	}
	return curG;

}

void dataHandle::deleteGuild(snowflake guildId) {
	std::string curQ = "";
	
	try {
		curQ = ("SELECT id FROM guildIds WHERE guildId = "  + std::to_string(guildId) + ";");
		std::cout << curQ << " at: " << __LINE__ << "\n"; 		
		mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());

		MYSQL_RES * result = mysql_store_result(this->dataCon);
		
		if (mysql_num_rows(result) > 0) {
			curQ = ("DELETE FROM guildIds WHERE guildId = "  + std::to_string(guildId) + ";");
			mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());

			mysql_free_result(result);
		} 

			
	
	} catch (...) {
		std::cout << "An error has occured \n";
	}


}

void dataHandle::updateGuild(cGuild gState) {
	std::string curQ = "";

	try {
		curQ = ("UPDATE guildIds SET curVal = \"" + gState.currentValue.toStr() + "\", curLives = " + to_string(gState.curLives) + ", curCount = " + to_string(this->getCount(gState.curStep,gState.curStart,gState.startLives)) + ", curUser = " + to_string(gState.curUser) + ", defChan = " + to_string(gState.prefChan) + " WHERE guildId = " + to_string(gState.curGuild) + ";");

		mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());


	} catch (...) {
		cout << "A error has occured\n";
	}
}


}



