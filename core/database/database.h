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

#ifndef D3Serve_database_h
#define D3Serve_database_h

typedef unsigned char byte;
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;

#include <string>
#include "../../utils/logger.h"
#include "../../utils/sqlite3.h"

class Database {
public:
    static const int DATABASE_END=0;
    static const int DATABASE_ROW=1;
    
    Database();
    int Connect();
    int PrepareStmt(std::string query);
    int ExecuteStmt();
    int FinalizeStmt();
    void Close();
    
    uint64 GetInsertId();
    
    int ResetStmt();
    int BindString(int pos, std::string param);
    int BindInt64(int pos, uint64 param);
    
    int GetInt(int pos);
    uint64 GetInt64(int pos);
    std::string GetString(int pos);
private:
    sqlite3 *db;
    sqlite3_stmt *stmt;
};

#endif
