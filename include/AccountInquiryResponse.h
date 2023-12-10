#ifndef ACCOUNTINQUIRYRESPONSE_H
#define ACCOUNTINQUIRYRESPONSE_H
#include <string>
#include "Account.h"

/**
AccountInquiryResponse object for user
**/
class AccountInquiryResponse
{
    public:
        AccountInquiryResponse();
        virtual ~AccountInquiryResponse();
        void setAccount(Account* accPtr);
        void setResponseMsg(std::string responseMsg);
        void setStatus(std::string status);
        std::string getStatus();
        Account* getAccount();
        std::string getResponseMsg();

    protected:

    private:
        Account* accountPtr;
        std::string responseMsg;
        std::string status;

};

#endif // ACCOUNTINQUIRYRESPONSE_H
