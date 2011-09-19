/*
 Diablo 3 Server Emulator
 Copyright (C) 2011 D3Sharp (https://github.com/raistlinthewiz/d3sharp)
 
 Ported to C++ by mcheng89
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef D3Serve_accountsmanager_h
#define D3Serve_accountsmanager_h

#include <string>
#include "database.h"
#include "toon.h"
#include "../../proto/service/authentication/authentication.pb.h"

class Toon;

class Account {
public:
    Account();
    Account(uint64 Id, std::string Email);
    uint64 getId();
    const bnet::protocol::EntityId getBnetAccountID();
    const bnet::protocol::EntityId getBnetGameAccountID();
    
    bool isInitialized();
    
    std::vector<Toon> Toons;
private:
    uint64 Id;
    std::string Email;
    bnet::protocol::EntityId BnetAccountID;
    bnet::protocol::EntityId BnetGameAccountID;
    
    bool initialized;
};

class AccountsManager {
public:
    static Account GetAccount(std::string email);
    static Account AddAccount(std::string email);
};

#endif
