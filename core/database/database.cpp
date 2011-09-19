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

#include "database.h"
#include <sstream>

Database::Database() {
    db = NULL;
    stmt = NULL;
}

int Database::Connect() {
    if (SQLITE_OK == sqlite3_open("database.db",&db))
        return 0;
    Logger::Error("Database:Connect()");
    Close();
    return -1;
}

int Database::PrepareStmt(std::string query) {
    if (SQLITE_OK == sqlite3_prepare_v2(db, query.c_str(), (int)query.length(), &stmt, NULL))
        return 0;
    Logger::Error("Database:PrepareStmt()");
    Close();
    return -1;
}

int Database::ExecuteStmt() {
    int ret = sqlite3_step(stmt);
    if (ret == SQLITE_ROW)
        return DATABASE_ROW;
    else if (ret == SQLITE_DONE)
        return DATABASE_END;
    else if (ret == SQLITE_BUSY)
        Logger::Error("Database:ExecuteStmt() SQLITE_BUSY");
    else if (ret == SQLITE_MISUSE)
        Logger::Error("Database:ExecuteStmt() SQLITE_MISUSE");
    else
        Logger::Error("Database:ExecuteStmt() UNKNOWN ERROR=%i", ret);
    return DATABASE_END;
}

int Database::FinalizeStmt() {
    if (stmt != NULL)
        sqlite3_finalize(stmt);
    stmt = NULL;
    return 0;
}

void Database::Close() {
    FinalizeStmt();
    int test = sqlite3_get_autocommit(db);
    Logger::Trace("AutoCommit mode = %i", test);
    if (db != NULL)
        sqlite3_close(db);
    db = NULL;
}

uint64 Database::GetInsertId() {
    return sqlite3_last_insert_rowid(db);
}

int Database::ResetStmt() {
    sqlite3_reset(stmt);
    return 0;
}

int Database::BindString(int pos, std::string param) {
    sqlite3_bind_text(stmt, pos, param.c_str(), (int)param.length(), NULL);
    return 0;
}
int Database::BindInt64(int pos, uint64 param) {
    sqlite3_bind_int64(stmt, pos, param);
    return 0;
}

int Database::GetInt(int pos) {
    return sqlite3_column_int(stmt, pos);
}
uint64 Database::GetInt64(int pos) {
    return sqlite3_column_int64(stmt, pos);
}
std::string Database::GetString(int pos) {
    std::stringstream ss;
    ss << sqlite3_column_text(stmt, pos);
    return ss.str();
}