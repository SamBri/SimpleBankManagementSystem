#include "SecurityService.h"
#include <iostream>
#include "FileService.h"
#include "AccountInquiryResponse.h"
#include "BankingService.h"
#include "SecurityServiceResponse.h"

//  functions definitions

SecurityService::SecurityService()
{
    //ctor
}

SecurityService::~SecurityService()
{
    //dtor
}


char SecurityService::getKey()
{

    return SecurityService::key;
}

std::string SecurityService::doPasswordEncryption(std::string password)
{


     //switch the characters of the password up by the security key:: aes encryption style.
    for(int i = 0;  i <  password.size(); i++)
    {

       //AEUOI:: b+5 a+5 k+5 e+5 r+5 y+5.
        password[i] = password[i] + SecurityService::getKey();

    }

    return password;


}

SecurityServiceResponse SecurityService::doPasswordDecryption(std::string accountNumber)
{


   // find the account with accountInquiry service
    AccountInquiryResponse response  = BankingService::doAccountInquiry(accountNumber);


    SecurityServiceResponse securityServiceResponse;
    std::string message{""};

    // where not found, send to the end user.
    if(response.getStatus()=="failed")
    {

        message = response.getResponseMsg();
        securityServiceResponse.setResponseMsg(message);
        securityServiceResponse.setStatus(response.getStatus());

        return securityServiceResponse;
    }


    std::string savedPassword = response.getAccount()->getPassword();

    // decrypt with key -- switch down.
    for(int i = 0;  i <  savedPassword.size(); i++)
    {


        savedPassword[i]  = savedPassword[i] - SecurityService::getKey();

    }


    message =  response.getResponseMsg();
    securityServiceResponse.setResponseMsg(message);
    securityServiceResponse.setStatus(response.getStatus());
    securityServiceResponse.setContent(savedPassword);

    return securityServiceResponse;


}
