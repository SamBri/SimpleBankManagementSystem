#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <cstdlib>

/**
 Account object for the Create, Read, Update and Delete of user
**/
class Account
{
public:
    Account();
    virtual ~Account();
    Account(std::string name, std::string address, double amount, std::string password);
    std::string getCustomerName();
    std::string getCustomerAddress();

    std::string getAccountNumber();
    char getAccountStatus();

    double getBalance();

    void setCustomerName(std::string name);
    void  setCustomerAddress(std::string address);

    void setBalance(double balance);


    void setAccountStatus(char status);

    void setAccountNumber(std::string account_number);



    int getId();

    void setId(int id);

    void setPassword(std::string password);

    std::string getPassword();


protected:

private:
    static int rowId;
    std::string customer_name;
    std::string customer_address;
    double balance;
    char status;
    std::string account_number;
    std::string password;
};

#endif // ACCOUNT_H




