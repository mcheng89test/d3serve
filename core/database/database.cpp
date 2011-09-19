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

uint64 Database::GetInt64(int pos) {
    return sqlite3_column_int64(stmt, pos);
}
std::string Database::GetString(int pos) {
    std::stringstream ss;
    ss << sqlite3_column_text(stmt, pos);
    return ss.str();
}