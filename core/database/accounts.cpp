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

#include "accounts.h"

Account::Account() {
    initialized = false;
}
Account::Account(uint64 Id, std::string Email) {
    initialized = true;
    this->Id = Id;
    this->Email = Email;
    BnetAccountID.set_high(0x100000000000000);
    BnetAccountID.set_low(this->Id);
    BnetGameAccountID.set_high(0x200006200004433);
    BnetGameAccountID.set_low(this->Id);
    
    Toons = ToonsManager::GetToonsForAccount(*this);
}

uint64 Account::getId() {return Id;}
const bnet::protocol::EntityId Account::getBnetAccountID() {return BnetAccountID;}
const bnet::protocol::EntityId Account::getBnetGameAccountID() {return BnetGameAccountID;}

bool Account::isInitialized() {
    return initialized;
}

Account AccountsManager::GetAccount(std::string email) {
    std::transform(email.begin(), email.end(), email.begin(), ::tolower);
    
    Database db;
    db.Connect();
    db.PrepareStmt("SELECT * FROM accounts WHERE email=?");
    db.BindString(1, email);
    if (db.ExecuteStmt() == db.DATABASE_ROW) {
        //var id = (ulong)reader.GetInt64(0);
        uint64 account_id = db.GetInt64(0);
        std::string account_email = db.GetString(1);
        Logger::Trace("AccountsManager:GetAccount() Loaded from database(id=%i,email=%s)", account_id, account_email.c_str());
        db.Close();
        return Account(account_id, account_email);
    }
    db.Close();
    return AddAccount(email);
}

Account AccountsManager::AddAccount(std::string email) {
    Database db;
    db.Connect();
    db.PrepareStmt("INSERT INTO accounts VALUES(NULL,?)");
    db.BindString(1, email);
    //if (db.ExecuteStmt() == db.DATABASE_END)
    db.ExecuteStmt();
    uint64 account_id = db.GetInsertId();
    std::string account_email = email;
    Logger::Trace("AccountsManager:AddAccount() Created new account(id=%i,email=%s)", account_id, account_email.c_str());
    db.FinalizeStmt();
    db.Close();
    return Account(account_id, account_email);
}
