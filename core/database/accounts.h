#ifndef D3Serve_accountsmanager_h
#define D3Serve_accountsmanager_h

#include <string>
#include "database.h"
#include "../../proto/service/authentication/authentication.pb.h"

class Account {
public:
    Account();
    Account(uint64 Id, std::string Email);
    const bnet::protocol::EntityId getBnetAccountID();
    const bnet::protocol::EntityId getBnetGameAccountID();
private:
    uint64 Id;
    std::string Email;
    bnet::protocol::EntityId BnetAccountID;
    bnet::protocol::EntityId BnetGameAccountID;
};

class AccountsManager {
public:
    static Account GetAccount(std::string email);
    static Account AddAccount(std::string email);
};

#endif
