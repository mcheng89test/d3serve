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

#ifndef D3Serve_toon_h
#define D3Serve_toon_h

#include <vector>
#include "accounts.h"
#include "database.h"

class Account;

class ToonHandleHelper {
    
};

class Toon {
public:
    enum ToonClass { 
        Barbarian   /*0x4FB91EE2*/,
        Monk        /*0x3DAC15*/, 
        DemonHunter /*0xc88b9649*/,
        WitchDoctor /*0x343C22A*/,
        Wizard      /*0x1D4681B1*/
    };
    enum ToonGender { Male /*0x0*/, Female /*0x2000002*/ };
    
    Toon(uint64 Id, std::string Name, ToonClass Class, ToonGender Gender, int Level, uint64 AccountId);
private:
    uint64 Id;
    std::string Name;
    ToonClass Class;
    ToonGender Gender;
    int Level;
    uint64 AccountId;
};

class ToonsManager {
public:
    static std::vector<Toon> GetToonsForAccount(Account account);
};

#endif
