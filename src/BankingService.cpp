#include "BankingService.h"
#include "Account.h"
#include "FileService.h"
#include <vector>


// functions definitions


BankingService::BankingService()
{
    //ctor
}

BankingService::~BankingService()
{
    //dtor
}







void BankingService::createAccount(std::string name, std::string address, double amount, std::string password)
{


// declare a new account instance.
// auto generate the account number.
// save to a file.
    Account *acc_ptr = new Account(name, address, amount, password);
    bool done = FileService::saveToFile((*acc_ptr));

    if(!done)
    {
        std::cout <<"Account creation failed!"<<std::endl;
    }

    std::cout <<"Account creation was successful."<<std::endl;

    std::cout <<"The Account Number : "<<(*acc_ptr).getAccountNumber()<<std::endl;

    std::cout<<std::endl;

    delete acc_ptr; //clean memory

}

// amount and account number.
void BankingService::depositMoney(double amount, std::string account_number)
{


    // find account

    AccountInquiryResponse response =  doAccountInquiry(account_number);


    if(response.getStatus()=="failed")
    {

        std::cout <<"Deposit money failed!";
        std::cout <<response.getResponseMsg()<<std::endl;

    }
    else if(response.getStatus()=="success")
    {



        // credit account.

        std::cout <<response.getResponseMsg()<<std::endl;
        std::cout<<"Name:"<<response.getAccount()->getCustomerName()<<std::endl;
        std::cout <<"Account Number:"<<response.getAccount()->getAccountNumber()<<std::endl;
        std::cout <<"Address:"<<response.getAccount()->getCustomerAddress()<<std::endl;
        std::cout  <<"Account Balance (GHS):"<<response.getAccount()->getBalance()<<std::endl;
        std::cout <<"Account Status:";
        if(response.getAccount()->getAccountStatus() == 'O')
        {
            std::cout <<"ACTIVE";
        }
        else if(response.getAccount()->getAccountStatus() == 'C')
        {
            std::cout <<"CLOSED";
        }

        std::cout << std::endl;


        // when closed, do nothing.
        if(response.getAccount()->getAccountStatus() == 'C')
        {
            std::cout <<"Account is Closed. Cannot fulfill Deposit request." << std::endl;
            return ;
        }

        std::cout << std::endl;

        double newBalance = amount + response.getAccount()->getBalance();

        //update file.
        Account* recordPtr = response.getAccount();

        response.getAccount()->setBalance(newBalance);

        bool done = FileService::updateToFile(recordPtr);

        // update status
         if(done)
        {
            std::cout <<"New Account Balance (GHS) :"<< response.getAccount()->getBalance() << std::endl;
        std::cout <<"Deposit Money was successfull :"<<std::endl;
            std::cout <<"Record updated."<<std::endl;

            delete recordPtr;
        }
        else
        {
            std::cout <<"Deposit Money request failed :"<<std::endl;
            std::cout <<"Record could not be updated."<<std::endl;

            delete recordPtr;

        }




    }







}

AccountInquiryResponse BankingService::doAccountInquiry(std::string account_number)
{

   // get all accounts from file.
   // if query matches data
    // return the account details.
    Account* theCustomerAccountPtr =  FileService::findAccount(account_number);


    AccountInquiryResponse accountInquiryResponse;

    if(theCustomerAccountPtr->getAccountNumber() == " ")
    {


        accountInquiryResponse.setAccount(theCustomerAccountPtr);
        accountInquiryResponse.setResponseMsg("Account number does not exist!");
        accountInquiryResponse.setStatus("failed");


    }
    else if(theCustomerAccountPtr->getAccountNumber() == account_number)
    {

        accountInquiryResponse.setAccount(theCustomerAccountPtr);
        accountInquiryResponse.setResponseMsg("Account Inquiry was successful.");
        accountInquiryResponse.setStatus("success");




    }
    else
    {


        accountInquiryResponse.setAccount(theCustomerAccountPtr);
        accountInquiryResponse.setResponseMsg("Account Inquiry Service Error");
        accountInquiryResponse.setStatus("failed");



    }



    return accountInquiryResponse;


}

void BankingService::doWithdrawal(std::string account_number, double amount)
{

// find account
// debit customer
// update file



    AccountInquiryResponse response =  doAccountInquiry(account_number);


    if(response.getStatus()=="failed")
    {

        std::cout <<"cash withdrawal failed!";
        std::cout <<response.getResponseMsg()<<std::endl;

    }
    else if(response.getStatus()=="success")
    {


        // when closed, do nothing.
        if(response.getAccount()->getAccountStatus() == 'C')
        {
            std::cout <<"Account is Closed.";
            return ;
        }


        std::cout <<response.getResponseMsg()<<std::endl;
        std::cout<<"Name:"<<response.getAccount()->getCustomerName()<<std::endl;
        std::cout <<"Account Number:"<<response.getAccount()->getAccountNumber()<<std::endl;
        std::cout <<"Address:"<<response.getAccount()->getCustomerAddress()<<std::endl;
        std::cout  <<"Account Balance (GHS):"<<response.getAccount()->getBalance()<<std::endl;
        std::cout <<"Account Status:";
        if(response.getAccount()->getAccountStatus() == 'O')
        {
            std::cout <<"ACTIVE";
        }
        else if(response.getAccount()->getAccountStatus() == 'C')
        {
            std::cout <<"CLOSED";
        }

        std::cout << std::endl;

        // when closed, do nothing.
        if(response.getAccount()->getAccountStatus() == 'C')
        {
            std::cout <<"Account is Closed. Cannot fulfill withdrawal request.";

            return ;
        }


        double newBalance =  response.getAccount()->getBalance() - amount;



        //update file.
        Account* recordPtr = response.getAccount();

        response.getAccount()->setBalance(newBalance);
        bool done = FileService::updateToFile(recordPtr);

        if(done)
        {
            std::cout <<"New Account Balance (GHS) :"<< response.getAccount()->getBalance() << std::endl;
            std::cout <<"Cash Withdrawal was successfull :"<<std::endl;
            std::cout <<"Record updated."<<std::endl;

            delete recordPtr;
        }
        else
        {
            std::cout <<"Cash Withdrawal request failed. :"<<std::endl;
            std::cout <<"Record could not be updated."<<std::endl;

            delete recordPtr;

        }



    }




}

std::vector<Account*> BankingService::getAllAccounts()
{
    return FileService::findAllAccounts();
}

void BankingService::closeAccount(std::string account_number)
{


// do account inquiry
// find account
// delete record from file
    AccountInquiryResponse response =  doAccountInquiry(account_number);


    if(response.getStatus()=="failed")
    {

        std::cout <<"Account Closure failed!";
        std::cout <<response.getResponseMsg()<<std::endl;

    }
    else if(response.getStatus()=="success")
    {

        std::cout <<response.getResponseMsg()<<std::endl;
        std::cout<<"Name:"<<response.getAccount()->getCustomerName()<<std::endl;
        std::cout <<"Account Number:"<<response.getAccount()->getAccountNumber()<<std::endl;
        std::cout <<"Address:"<<response.getAccount()->getCustomerAddress()<<std::endl;
        std::cout  <<"Account Balance (GHS):"<<response.getAccount()->getBalance()<<std::endl;
        std::cout <<"Account Status:";
        if(response.getAccount()->getAccountStatus() == 'O')
        {
            std::cout <<"ACTIVE";
        }

        std::cout << std::endl;

        // update status
        response.getAccount()->setAccountStatus('C');


        // update file
        Account* recordPtr = response.getAccount();
       bool done = FileService::updateToFile(recordPtr);


       if(done){

        std::cout <<"Modified Account Status :";
        if(response.getAccount()->getAccountStatus() == 'C')
        {
            std::cout <<"CLOSED";
        }

        std::cout<< std::endl;
        std::cout <<"Account Closure was successful!"<< std::endl;

        FileService::deleteRecord(recordPtr);
        std::cout <<"Account successfully Deleted."<< std::endl;

        delete recordPtr;

       } else{


        std::cout<< std::endl;
        std::cout <<"Account Closure was not successful!"<< std::endl;
        std::cout <<"Account could not be successfully Deleted."<< std::endl;

        delete recordPtr;



       }








    }




}


