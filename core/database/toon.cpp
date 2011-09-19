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

#include "toon.h"

Toon::Toon(uint64 Id, std::string Name, ToonClass Class, ToonGender Gender, int Level, uint64 AccountId) {
    this->Id = Id;
    this->Name = Name;
    this->Class = Class;
    this->Gender = Gender;
    this->Level = Level;
    this->AccountId = AccountId;
}

std::vector<Toon> ToonsManager::GetToonsForAccount(Account account) {
    std::vector<Toon> toons;
    
    Database db;
    db.Connect();
    db.PrepareStmt("SELECT * FROM toons WHERE accountId=?");
    db.BindInt64(1, account.getId());
    while (db.ExecuteStmt() == db.DATABASE_ROW) {
        uint64 toon_id = db.GetInt64(0);
        std::string toon_name = db.GetString(1);
        Toon::ToonClass toon_class = (Toon::ToonClass)db.GetInt(2);
        Toon::ToonGender toon_gender = (Toon::ToonGender)db.GetInt(3);
        int toon_level = db.GetInt(4);
        uint64 account_id = db.GetInt64(5);
        toons.push_back(Toon(toon_id, toon_name, toon_class, toon_gender, toon_level, account_id));
    }
    db.Close();
    return toons;
}