#include "accounts.h"

Account::Account(){}
Account::Account(uint64 Id, std::string Email) {
    this->Id = Id;
    this->Email = Email;
    BnetAccountID.set_high(0x100000000000000);
    BnetAccountID.set_low(this->Id);
    BnetGameAccountID.set_high(0x200006200004433);
    BnetGameAccountID.set_low(this->Id);
}

const bnet::protocol::EntityId Account::getBnetAccountID() {
    return BnetAccountID;
}
const bnet::protocol::EntityId Account::getBnetGameAccountID() {
    return BnetGameAccountID;
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
        Logger::Trace("AccountsManager:GetAccount() Loaded from database(id=%i)", account_id);
        std::string account_email = db.GetString(1);
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
    Logger::Trace("AccountsManager:AddAccount() Created new account(id=%i)", account_id);
    std::string account_email = email;
    db.FinalizeStmt();
    db.Close();
    return Account(account_id, account_email);
}