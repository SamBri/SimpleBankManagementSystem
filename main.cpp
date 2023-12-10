/**
Project Title : Simple Bank Management System
Date :
Author :
Summary:
This application create new bank accounts,
deposit and withdraw money, check balances, and view account details.
Security implementation made for operations or services such as close account and withdraw from account.
**/
#include <iostream>
#include <string>
#include <stdlib.h>
#include "BankingService.h"
#include <vector>
#include "SecurityService.h"
#include "SecurityServiceResponse.h"
#include "FileService.h"
#include <sstream>


using namespace std;


// function declaration.
void showTitleMessage();
void showBankingService();
void performBankingService(int service);
void init();


int main()
{


    init(); // create fileDb
    while(true)
    {


        try
        {

            //1. show title
            showTitleMessage();

            //2. display application functions
            showBankingService();

            //3. choose function
            int userInput{0};
            cin >> userInput;

            if(userInput == 0)
            {

                throw runtime_error("input exception :: invalid input entered");
            }

            performBankingService(userInput);



        }
        catch(runtime_error err)
        {


            cout << err.what() << endl;

            return -1; // break while loop when exception occurs

        }

    }





    std::getchar(); //waits for character.
    return 0;
}


/**
 function definition

 **/

 // do background filedb setup
void init(){

    std::ofstream fileDb;

    fileDb.open(FileService::getFileName(), ios::app); //for write
    if(!fileDb)
    {

        std::cout <<"File DB init failed!"<<std::endl;

        throw std::runtime_error("init exception.");

        return;

    }



    fileDb.close();

}

void showTitleMessage()
{



    cout <<"********************************************************************"<<endl;
    cout <<"*********** THIS IS THE CORTEX SIMPLE BANK MANAGEMENT SYSTEM *******"<<endl;
    cout <<"********************************************************************"<<endl;


}

void showBankingService()
{



    cout <<"Cortex Banking Service :"<<endl;
    cout <<"1. Create Account"<<endl;
    cout <<"2. Deposit Money"<<endl;
    cout <<"3. Withdraw Money"<<endl;
    cout <<"4. Perform Account Inquiry"<<endl;
    cout <<"5. Show All Accounts"<<endl;
    cout <<"6. Close Account"<<endl;

    cout <<"Enter ( 1 - 6 ) to select :"<<endl;

}

void performBankingService(int s)
{



    string account_number, customer_name, customer_address, password;
    double amount;



    switch (s)
    {

    case 1:
    {

        double initial_amount;
        cout <<"1. Create Account Service"<<endl;

        cout <<"Enter name:"<<endl;
        cin >> customer_name;



        cout <<"Enter address:"<<endl;
        cin >> customer_address;



        cout <<"Initial deposit amount : GHC";
        cin >> initial_amount;



        cout <<"Create Password:"<<endl;
        cin >> password;


        if(initial_amount == 0.0 || customer_name == "" || customer_address == ""|| password == "")
        {

            throw runtime_error("input exception :: invalid entry");
        }



        // call createAccount Operation.
        BankingService::createAccount(customer_name, customer_address, initial_amount, password);

    }
    break;
    case 2:


        cout <<"2. Deposit Money"<<endl;
        cout <<"Enter account Number:"<<endl;
        cin >> account_number;
        cout <<"Amount (GHS): "<<endl;
        cin >> amount;


        if(amount==0.0 || account_number == "")
        {

            throw runtime_error("input exception :: invalid entry.");
        }
        BankingService::depositMoney(amount, account_number);

        break;
    case 3:

    {


        cout <<"3. Withdraw Money"<<endl;
        cout <<"Enter account Number:"<<endl;
        cin >> account_number;

        cout <<"Enter password:"<<endl;
        cin >> password;
        std::string decrypt_password;


        if(account_number  == "" || password == "")
        {

            throw runtime_error("input exception :: invalid entry");
        }

        SecurityServiceResponse serviceResponse;

        serviceResponse  = SecurityService::doPasswordDecryption(account_number);


        if(serviceResponse.getStatus() != "success")
        {


            cout <<"Cash Withdrawal request could not be fulfilled"<<endl;
            cout <<serviceResponse.getResponseMsg()<<endl;



        }
        else
        {

            decrypt_password = serviceResponse.getContent();

            if(password != decrypt_password)
            {

                cout <<"invalid password!"<<endl;

                cout <<"Cash Withdrawal request could not be fulfilled"<<endl;

            }
            else
            {
                cout <<"Amount (GHS): "<<endl;
                cin >> amount;
                if(amount==0.0)
                {

                    throw runtime_error("input exception :: invalid amount entered");
                }
                BankingService::doWithdrawal(account_number, amount);
            }

        }


    }

    break;
    case 4:
    {

        cout <<endl;
        cout <<"4. Account inquiry"<<endl;
        cout <<"Enter account Number:"<<endl;
        cin >> account_number;

        if(account_number  == "")
        {

            throw runtime_error("input exception :: invalid entry");
        }

        AccountInquiryResponse response = BankingService::doAccountInquiry(account_number);

        if(response.getStatus()=="failed")
        {


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

            std::cout << std::endl;



        }


        cout <<endl;

    }

    break;

    case 5:
    {


        cout <<"5. List All Accounts"<<endl;
        std::vector<Account*> accounts =   BankingService::getAllAccounts();

        for(int i =0 ; i < accounts.size(); i++)
        {


            std::cout<<"Name:"<<accounts[i]->getCustomerName()<<std::endl;
            std::cout <<"Account Number:"<<accounts[i]->getAccountNumber()<<std::endl;
            std::cout <<"Address:"<<accounts[i]->getCustomerAddress()<<std::endl;
            std::cout  <<"Account Balance (GHS):"<<accounts[i]->getBalance()<<std::endl;
            std::cout <<"Account Status:";
            if(accounts[i]->getAccountStatus() == 'O')
            {
                std::cout <<"ACTIVE";
            }
            if(accounts[i]->getAccountStatus()  == 'C')
            {
                std::cout <<"CLOSED";
            }

            std::cout << std::endl;
            std::cout << std::endl;


        }


        std::cout << std::endl;




    }


    break;
    case 6 :
    {


        cout <<"6. Close Account"<<endl;
        cout <<"Enter account Number:"<<endl;
        cin >> account_number;
        cout <<"Enter password:"<<endl;
        cin >> password;

        if(account_number  == "" || password == "")
        {

            throw runtime_error("input exception :: invalid entry");
        }


        std::string decrypt_password;
        SecurityServiceResponse serviceResponse;
        serviceResponse  = SecurityService::doPasswordDecryption(account_number);

        if(serviceResponse.getStatus() != "success")
        {

            cout <<"Account closure request could not be fulfilled"<<endl;
            cout <<serviceResponse.getResponseMsg()<<endl;

        }
        else
        {

            decrypt_password = serviceResponse.getContent();

            if(password != decrypt_password)
            {

                cout <<"invalid password!"<<endl;
                cout <<"Account Closure request could not be fulfilled"<<endl;

            }
            else
            {

                BankingService::closeAccount(account_number);

            }

        }





    }


    break;

    default:

        cout <<"No Service Available for the input entered"<<endl;

    }




}
