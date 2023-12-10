#ifndef BANKINGSERVICE_H
#define BANKINGSERVICE_H
#include <string>
#include "AccountInquiryResponse.h"
#include <vector>


/**
BankingService Object to facilitate banking operations.
**/
class BankingService
{
    public:
        BankingService();
        virtual ~BankingService();
        static void createAccount(std::string name, std::string address, double amount, std::string password);
        static void depositMoney(double amount, std::string account_number);
        static AccountInquiryResponse doAccountInquiry(std::string account_number);
        static void doWithdrawal(std::string account_number, double amount);;
        static std::vector<Account*> getAllAccounts();
        static void closeAccount(std::string account_number);
        static void deleteAccount(std::string account_number);

    protected:

    private:
};

#endif // BANKINGSERVICE_H
