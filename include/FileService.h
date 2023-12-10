#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <iostream>
#include <fstream>
#include "Account.h"
#include<string>
#include<vector>

/**
FileService object to facilitate CRUD operations of user account.
**/


class FileService
{
public:
    FileService();
    virtual ~FileService();
    bool static saveToFile(Account customerAccountPtr);
    Account static  findRecord(std::string account_number);
    static Account* findAccount(std::string account_number);
    static std::vector<Account*> findAllAccounts();
    bool static updateToFile(Account* accPtr);
    void static deleteRecord(Account* accPtr);

    std::string static getFileName();

protected:

private:

  const static std::string  fileName; // the file name.



};

#endif // FILESERVICE_H
