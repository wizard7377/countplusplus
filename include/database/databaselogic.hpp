#pragma once

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <dpp/dpp.h>
#include <variant>
/* uncomment for applications that use vectors */
#include <vector>
#include "utl.hpp"

#include "dbtypes.hpp"

#include <mysql.h>

using namespace dpp;


namespace mData {
class dataHandle {
    public:
        dataHandle(cluster * botPar);
        utl::cGuild * getGuild(snowflake guildId);
        void deleteGuild(snowflake guildId);
        void updateGuild(utl::cGuild gState);
        //reSet getUser(uint64_t userId,uint64_t guildId = 0);
        //reSet getRate(int gameId,uint64_t userId,uint64_t guildId = 0);
        //bool editSetting(string setName, string val, int gameId, uint64_t userId, uint64_t guildId = 0, int scopeSet = 0);

    private: 
        MYSQL * dataCon;
        cluster * bot;
        int getCount(utl::fracNum rCount,utl::fracNum rStart,int rLives);
        int getUser(uint64_t userId);
};
}