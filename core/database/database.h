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
    
    uint64 GetInt64(int pos);
    std::string GetString(int pos);
private:
    sqlite3 *db;
    sqlite3_stmt *stmt;
};

#endif
