#include "databaselogic.hpp"
#include <iostream>
#include <dpp/dpp.h>
#include <mysql.h>
#include "config.hpp"
#include <thread>
#include <functional>

using namespace std;
	
using cGuild = utl::cGuild;
using fracNum = fNum::fracNum;

int strToInt (char * inStr) {
	if (inStr != 0) {
		try { int tInt = stoi(inStr); return tInt; } catch (...) { return 1; }
	} else {
		return 0;
	}
}
uint64_t strToUInt (char * inStr) {
	if (inStr != 0) {
		try { uint64_t tInt = stoull(inStr); return tInt; } catch (...) { return 1; }
	} else {
		return 0;
	}
}

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
	//std::cout << mysql_stat(this->dataCon);
	if (mysql_stat(this->dataCon) == NULL) { 
		std::cout << "connection failed\n";
		throw 0; 
	} else {
		std::cout << "Final checks succeded\n";
	}
	
	//this->dataCon = NULL;
 
}

int dataHandle::getUser(uint64_t userId) {
	std::string curQ = "";
	try {
		curQ = ("SELECT id FROM userIds WHERE userId = " + to_string(userId) + ";"); 		
		//std::cout << curQ << " at: " << __LINE__ << "\n";
		mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());

		MYSQL_RES * result = mysql_store_result(this->dataCon);
		
		if (mysql_num_rows(result) > 0) {	
			MYSQL_ROW resRow = mysql_fetch_row(result);
			int tInt = stoi(resRow[0]);
			mysql_free_result(result);
			return tInt;
		} else {		
			curQ = ("INSERT INTO userIds(userId) VALUES (" +to_string(userId) + ");");
			mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());
			return (mysql_insert_id(this->dataCon));	
		}	
	} catch (...) {
		std::cout << "An error has occured (data) \n";
	}
	return 0;



}


int dataHandle::getCount(fracNum rCount, fracNum rStart, int rLives) {
	std::string curQ = "";
	try {
		curQ = ("SELECT id FROM countIds WHERE currentJump = \"" + rCount.toStr() + "\" AND currentStart = \"" + rStart.toStr() + "\" AND numLives = " + to_string(rLives) + ";"); 		
		//std::cout << curQ << " at: " << __LINE__ << "\n";
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
		std::cout << "An error has occured (data) \n";
	}
	return 0;



}

utl::cGuild * dataHandle::getGuild(snowflake guildId) {
	std::string curQ = "";
	cGuild * curG = new cGuild(guildId,this->bot);
	curG->onUpdate = [this,curG] { this->updateGuild(*curG); }; 
	try {
		curQ = ("SELECT * FROM guildIds LEFT JOIN countIds ON guildIds.curCount = countIds.id LEFT JOIN userIds ON guildIds.curUser = userIds.id WHERE guildId = "  + std::to_string(guildId) + ";"); 		
		//std::cout << curQ << " at: " << __LINE__ << "\n";
		mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());

		MYSQL_RES * result = mysql_store_result(this->dataCon);
		//std::cout << mysql_num_rows(result) << std::endl;
		if (result == 0) { return curG; }
		if (mysql_num_rows(result) > 0) {
			
			MYSQL_ROW resRow = mysql_fetch_row(result);		
			//std::cout << "num rows: " << mysql_num_rows(result) << std::endl;		
			//std::cout << "num fields: " << mysql_num_fields(result) << std::endl;			
			curG->setCount(fracNum(resRow[8]));			
			curG->setStart(fracNum(resRow[9]));			
			curG->setLives(stoi(resRow[3]));			
			curG->setPrefChan(strToUInt(resRow[6]));
			curG->startLives = strToInt(resRow[10]);			
			curG->curUser = (strToUInt(resRow[5]));
			curG->currentValue = (fracNum(resRow[2]));			
			mysql_free_result(result);
		} else {
			
			curQ = ("INSERT INTO guildIds (guildId,curVal,curLives,curCount,curUser,defChan) VALUES (" + to_string(guildId) + ",\"1\",1,1,NULL,NULL);");
			//std::cout << curQ << " at: " << __LINE__ << "\n";
			mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());
			
		}
			
	
	} catch (...) {
		std::cout << "An error has occured (data) 1 \n";

	}
	//curG->forceChange();
	return curG;

}

void dataHandle::deleteGuild(snowflake guildId) {
	std::string curQ = "";
	
	try {
		curQ = ("SELECT id FROM guildIds WHERE guildId = "  + std::to_string(guildId) + ";");
		//std::cout << curQ << " at: " << __LINE__ << "\n"; 		
		mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());

		MYSQL_RES * result = mysql_store_result(this->dataCon);
		
		if (mysql_num_rows(result) > 0) {
			curQ = ("DELETE FROM guildIds WHERE guildId = "  + std::to_string(guildId) + ";");
			mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());

			mysql_free_result(result);
		} 

			
	
	} catch (...) {
		std::cout << "An error has occured (data) 2 \n";
	}


}

void dataHandle::updateGuild(cGuild gState) {
	std::string curQ = "";

	try {
		 		
		curQ = ("UPDATE guildIds SET curVal = \"" + gState.currentValue.toStr() + "\", curLives = " + to_string(gState.curLives) + ", curCount = " + to_string(this->getCount(gState.curStep,gState.curStart,gState.startLives)) + ", curUser = " + to_string(this->getUser(gState.curUser)) + ", defChan = " + to_string(gState.prefChan) + " WHERE guildId = " + to_string(gState.curGuild) + ";");
		//std::cout << curQ << " at: " << __LINE__ << "\n";
		mysql_real_query(this->dataCon,curQ.c_str(),curQ.length());


	} catch (...) {
		cout << "A error has occured (data) 3 \n";
	}
}


}



