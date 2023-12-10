#include "Account.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "SecurityService.h"

// functions definitions

Account::Account()
{
    //ctor
}


int Account::rowId = 0;  //static definition

void Account::setPassword(std::string password){
this->password = password;
}

std::string Account::getPassword(){
return this->password;
}



Account::Account(std::string name, std::string address, double amount, std::string password)
{
    // generate account number | random  number generate
    //1661 + timestamp of occurence.
    srand(time(NULL));
    rowId++;
    account_number = "10000" + std::to_string(rand());
    customer_name = name;
    customer_address = address;
    balance = amount;
    status='O';
    // encrypt password to file.
   this->password=SecurityService::doPasswordEncryption(password);

}

Account::~Account()
{
    //dtor

}


std::string Account::getCustomerName()
{

    return customer_name;
}

std::string Account::getCustomerAddress()
{

    return customer_address;
}


std::string Account::getAccountNumber()
{

    return account_number;
}


char Account::getAccountStatus()
{

    return status;
}

double Account::getBalance()
{

    return balance;
}


int Account::getId()
{

    return rowId;
}




void Account::setCustomerName(std::string name)
{

    customer_name = name;
};

void  Account::setCustomerAddress(std::string address)
{

    customer_address = address;

};
void  Account::setBalance(double balance)
{

    this->balance = balance;

};
void  Account::setAccountStatus(char status)
{

    this->status = status;
}
;
void  Account:: setAccountNumber(std::string account_number)
{

    this->account_number = account_number;
};


void Account::setId(int id){

this->rowId = id;
}

