#include <thread>
#include <string>
#include <dpp/dpp.h>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include "gamenums.hpp"
#include "utl.hpp"
//#include "cguild.cpp"
//#include "fracnum.cpp"
#include "eventhandle.hpp"



//extern void handleChallengeSubmit(user userId, snowflake challengeId, std::string gameName, std::string guildName, cluster& bot,const form_submit_t& event);

using namespace dpp;

namespace evt {
	
eventhandle::eventhandle(cluster * bot) {
	this->testCon = new mData::dataHandle();
	std::unordered_map<snowflake,utl::cGuild*> * gMap = new std::unordered_map<snowflake,utl::cGuild*>; 
	for (auto a: bot->current_user_get_guilds_sync()) {
		utl::cGuild * nGuild = new utl::cGuild(a.first,bot);
		gMap->emplace(a.first,nGuild);
		this->addMessageCmd(std::to_string(a.first),([this,nGuild](const message_create_t& event) { nGuild->onMsg(event.msg); } ));
	}
	bot->on_select_click([this](const auto& event) {
		try {
			std::thread([this,event] { try { this->selectCmds.at(event.custom_id)(event); } catch (...) {} } ).detach();
		} catch (...) {
			std::cout << "An error has occured" << std::endl;
		}
	});
	bot->on_button_click([this](const auto& event) {
		try {
			std::thread([this,event] { (this->buttonCmds.at(event.custom_id))(event); }).detach();
		} catch (...) {
			std::cout << "An error has occured" << std::endl;
		}
	});
	bot->on_form_submit([this](const auto& event) {
		try {
			std::thread([this,event] { this->formCmds.at(event.custom_id)(event); }).detach();
		} catch (...) {
			std::cout << "An error has occured" << std::endl;
		}
	});
	bot->on_message_create([this](const auto& event) {
		
	
		std::thread([this,event] { 
			try {
				this->messageCmds.at(std::to_string(event.msg.guild_id))(event);
		 	} catch(...) {
				std::cout << "An error has occured\n";
			}
			}).detach();
	});
	bot->on_slashcommand([this,bot](const auto& event) {
		try {
			//uint64_t retId = std::get<uint64_t>(this->testCon->getUser((uint64_t)(event.command.get_issuing_user().id))[0]);
			//uint64_t retIdT = std::get<uint64_t>(this->testCon->getUser(((uint64_t)(event.command.get_issuing_user().id)),((uint64_t)(event.command.get_guild().id)))[0]);
			//std::cout << std::endl << "Cur user is: " << std::to_string(retId) << " and: " << retIdT << std::endl << std::endl;
			std::thread([this,event,bot] { this->slashCmds.at(event.command.get_command_name())(event); }).detach();
		} catch (...) {
			std::cout << "An error has occured" << std::endl;
		}
	});
	
	

	this->addSlashCmd("info",[bot](const slashcommand_t &event) {
		event.reply("This bot is for playing two player games, and it's source code may be found at https://github.com/wizard7377/countplusplus.git");
	});
	this->addSlashCmd("countrules",[bot,gMap](const slashcommand_t &event) {
		event.reply("Done");
		if (event.get_parameter("start").index() != 0) { (gMap->at(event.command.get_guild().id))->setStart(std::get<double>(event.get_parameter("start"))); }
		if (event.get_parameter("step").index() != 0) { (gMap->at(event.command.get_guild().id))->setCount(std::get<double>(event.get_parameter("step"))); }
		if (event.get_parameter("lives").index() != 0) { (gMap->at(event.command.get_guild().id))->setLives(std::get<int64_t>(event.get_parameter("lives"))); }
		if ((event.get_parameter("start").index() != 0) or (event.get_parameter("step").index() != 0) or (event.get_parameter("lives").index() != 0)) { (gMap->at(event.command.get_guild().id))->forceReset(); }	
	});
	this->addSlashCmd("reset",[bot,gMap](const slashcommand_t &event) {
		event.reply("Count has been reset");
		(gMap->at(event.command.get_guild().id))->forceReset();	
	});
	this->addSlashCmd("channelset",[bot,gMap](const slashcommand_t &event) {
		
		if (event.get_parameter("channel").index() != 0) {
			if (std::any_of(event.command.get_guild().channels.begin(),event.command.get_guild().channels.begin(),[event](snowflake inVal) { return (std::get<snowflake>(event.get_parameter("channel")) == inVal); })) {
				(gMap->at(event.command.get_guild().id))->setPrefChan(std::get<snowflake>(event.get_parameter("channel")));
				event.reply("Set channel");			
			} else {
				event.reply("Channel not in guild");
			}
		} else {
			(gMap->at(event.command.get_guild().id))->setPrefChan(event.command.get_channel().id);
			event.reply("Set channel");			
		}
	});
	
	
		


		



	std::cout << "Event handelers succesfully started" << std::endl;

}
//bool eventhandle::addSelectCmd(std::string compid,std::function<void(const select_click_t&)> newCmd) {
bool eventhandle::addSelectCmd(std::string compid,std::function<void(const select_click_t&)> newCmd) {
	try { this->selectCmds.emplace(compid,newCmd); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::addSlashCmd(std::string compid,std::function<void(const slashcommand_t&)> newCmd) {
	try { this->slashCmds.emplace(compid,newCmd); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::addFormCmd(std::string compid,std::function<void(const form_submit_t&)> newCmd) {
	try { this->formCmds.emplace(compid,newCmd); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::addButtonCmd(std::string compid,std::function<void(const button_click_t&)> newCmd) {
	try { this->buttonCmds.emplace(compid,newCmd); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::addMessageCmd(std::string compid,std::function<void(const message_create_t&)> newCmd) {
	try { this->messageCmds.emplace(compid,newCmd); }
	catch (...) { return false; }
	return true;
}




bool eventhandle::deleteSelectCmd(std::string compid) {
	try { this->selectCmds.erase(compid); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::deleteSlashCmd(std::string compid) {
	try { this->slashCmds.erase(compid); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::deleteFormCmd(std::string compid) {
	try { this->slashCmds.erase(compid); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::deleteButtonCmd(std::string compid) {
	try { this->buttonCmds.erase(compid); }
	catch (...) { return false; }
	return true;
}
bool eventhandle::deleteMessageCmd(std::string compid) {
	try { this->messageCmds.erase(compid); }
	catch (...) { return false; }
	return true;
}


}
