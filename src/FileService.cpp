#include "FileService.h"
#include <string>
#include <sstream>
#include <vector>

// functions definitions


FileService::FileService()
{
    //ctor
}

FileService::~FileService()
{
    //dtor
}


const std::string FileService::fileName{"accounts.txt"};

std::string FileService::getFileName(){

return FileService::fileName;

}

void FileService::deleteRecord(Account* accDelPtr)
{


    std::ifstream inAccountsFile;

    Account* accptr = new Account;


    inAccountsFile.open(FileService::getFileName()); //for read
    if(!inAccountsFile)
    {

        std::cout <<"Cannot open "<< FileService::getFileName() << " file " <<std::endl;

        throw std::runtime_error("file exception.");


        return; // null account;

    }

    std::string record;

    int rowId;
    std::string customer_name;
    std::string customer_address;
    double balance;
    std::string customer_account_number;
    char status;


    rowId = accDelPtr->getId();
    customer_name = accDelPtr->getCustomerName();
    customer_address = accDelPtr->getCustomerAddress();
    balance = accDelPtr->getBalance();
    customer_account_number = accDelPtr->getAccountNumber();
    status = accDelPtr->getAccountStatus();

    //prepare the record for write
    record = "";

    std::vector<std::string> backedUpRecord;

    std::string line;
    int modifiedRowNumber;



    while(getline(inAccountsFile, line))
    {

        // save the records
        backedUpRecord.push_back(line);


    }

    inAccountsFile.close();

    std::vector<std::string> modifiedRecord; //
    // update the backup record with the new line.
    for(int i =0 ; i < backedUpRecord.size(); i++)
    {


        std::istringstream lineProcessor(backedUpRecord[i]);
        lineProcessor >> modifiedRowNumber;

        if(modifiedRowNumber == rowId )
        {
            modifiedRecord.push_back(record);
        }
        else
        {

            modifiedRecord.push_back(backedUpRecord[i]);
        }




    }


    std::ofstream outAccountsFile;

    outAccountsFile.open(FileService::fileName, std::ofstream::out); //for write
    if(!outAccountsFile)
    {

        std::cout <<"Cannot open "<< FileService::getFileName() << " file " <<std::endl;

        return; // null account;

    }


    // then write fresh records
    for(int i =0 ; i < modifiedRecord.size(); i++)
    {

        // write content to file
        if(modifiedRecord[i]== "")
        {
            outAccountsFile <<"\n";

        }
        else
        {
            outAccountsFile << modifiedRecord[i]<<"\n";


        }

    }

    // close file
    outAccountsFile.close();






}



bool FileService::saveToFile(Account customerAccount)
{

    std::ofstream accountsFile;



// open file
    accountsFile.open(FileService::getFileName(), std::ofstream::app); //for extension

    if(!accountsFile)
    {

        std::cout <<"Cannot open "<< FileService::getFileName() << " file " <<std::endl;

        throw std::runtime_error("file exception.");


        return false;
    }


// write content to file
    accountsFile << customerAccount.getId() <<","<<customerAccount.getCustomerName()<<","<<customerAccount.getAccountNumber()
                 <<","<<customerAccount.getCustomerAddress()<<","<<customerAccount.getBalance()
                 <<","<<customerAccount.getAccountStatus()<<","<<customerAccount.getPassword()<<"\n";

// close file
    accountsFile.close();

// say done.
    return true;


}


Account* FileService::findAccount(std::string account_number)
{

// open file.
    std::ifstream accountsFile;

    Account* accptr = new Account;



    accountsFile.open(FileService::getFileName()); //for read
    if(!accountsFile)
    {

        std::cout <<"Cannot open "<< FileService::getFileName() << " file " <<std::endl;

        throw std::runtime_error("file exception.");


        return accptr; // null account;

    }

    std::string record;
    // Read all data
    //: read a record from the file
    //: assemble an object of the record.
    //: inspect the record account_number against the passed account number

    int rowId;
    std::string customer_name; //
    std::string customer_address;
    double balance;
    std::string customer_account_number;
    char status;
    std::string password;

    while(getline(accountsFile, record))
    {


        for(int i = 0; i < record.size(); i++)
        {

            if(record[i] == ',')
            {
                record[i] = ' ';
            }

        }



        std::istringstream data(record);


        data >> rowId;
        data >> customer_name;
        data >> customer_account_number;
        data >> customer_address;
        data >> balance;
        data >> status;
        data >> password;



        if(account_number == customer_account_number)
        {



            accptr->setId(rowId);
            accptr->setAccountNumber(customer_account_number);
            accptr->setAccountStatus(status);
            accptr->setBalance(balance);
            accptr->setCustomerAddress(customer_address);
            accptr->setCustomerName(customer_name);
            accptr->setPassword(password);

            return accptr;

        }
        else
        {


            accptr->setAccountNumber(" ");

        }

    }






// match found say true.

    return accptr; // null account;
}



std::vector<Account*> FileService::findAllAccounts()
{



    std::ifstream accountsFile;
    std::vector<Account*> accounts;

    // open file.
    accountsFile.open(FileService::getFileName()); //for write
    if(!accountsFile)
    {

        std::cout <<"Cannot open "<< FileService::getFileName() << " file " <<std::endl;
        throw std::runtime_error("file exception.");


        return accounts; // null account;

    }

    std::string record;
    // Read all data
    // read a record from the file
    // assemble an object of the record.
    // return accounts

    while(getline(accountsFile, record))
    {

        for(int i = 0; i < record.size(); i++)
        {

            if(record[i] == ',')
            {
                record[i] = ' ';
            }

        }



        std::istringstream data(record);

        int rowId;
        std::string customer_name; //
        std::string customer_address;
        double balance = 0.0;
        std::string customer_account_number;
        char status = ' ';
        std::string password;


        data >> rowId;
        data >> customer_name;
        data >> customer_account_number;
        data >> customer_address;
        data >> balance;
        data >> status;
        data >> password;



        Account* accsPtr = new Account;


        accsPtr->setAccountNumber(customer_account_number);
        accsPtr->setAccountStatus(status);
        accsPtr->setBalance(balance);
        accsPtr->setCustomerAddress(customer_address);
        accsPtr->setCustomerName(customer_name);
        accsPtr->setPassword(password);


        if(customer_name == "" || customer_account_number == "" || customer_address == "" || status == ' ' || balance == 0.0 || password == "")

        {
            ;
        }
        else
        {

            accounts.push_back(accsPtr);

        }




    }






    return accounts;




};

bool FileService::updateToFile(Account* accMdfPtr)
{

// // read the record.
// // assemble an object.
// // Read all data
//    //: read a record from the file
//    //: assemble an object of the record.
//    //: make the modification.
//    //: write to the file.

    std::ifstream inAccountsFile;

    Account* accptr = new Account;


    inAccountsFile.open(FileService::getFileName()); //for read
    if(!inAccountsFile)
    {

        std::cout <<"Cannot open "<< FileService::getFileName() << " file " <<std::endl;

        throw std::runtime_error("file exception.");

        return false; // null account;

    }

    std::string record;

    int rowId;
    std::string customer_name;
    std::string customer_address;
    double balance;
    std::string customer_account_number;
    char status;
    std::string password;


    rowId = accMdfPtr->getId();
    customer_name = accMdfPtr->getCustomerName();
    customer_address = accMdfPtr->getCustomerAddress();
    balance = accMdfPtr->getBalance();
    customer_account_number = accMdfPtr->getAccountNumber();
    status = accMdfPtr->getAccountStatus();
    password = accMdfPtr->getPassword(); //

    //prepare the record for write
    record = std::to_string(rowId) + "," + customer_name +   "," +  customer_account_number + "," + customer_address + "," + std::to_string(balance) + ","
             +  status + "," + password ;


    std::vector<std::string> backedUpRecord;

    std::string line;
    int modifiedRowNumber;



    while(getline(inAccountsFile, line))
    {

        // save the records
        backedUpRecord.push_back(line);


    }

    inAccountsFile.close();

    std::vector<std::string> modifiedRecord; //
    // update the backup record with the new line.
    for(int i =0 ; i < backedUpRecord.size(); i++)
    {


        std::istringstream lineProcessor(backedUpRecord[i]);
        lineProcessor >> modifiedRowNumber;

        if(modifiedRowNumber == rowId )
        {
            modifiedRecord.push_back(record);
        }
        else
        {

            modifiedRecord.push_back(backedUpRecord[i]);
        }




    }


    std::ofstream outAccountsFile;

    outAccountsFile.open(FileService::getFileName(), std::ofstream::out); //for read
    if(!outAccountsFile)
    {

        std::cout <<"Cannot open "<< FileService::getFileName() << " file " <<std::endl;

        throw std::runtime_error("file exception.");


        return false; // null account;

    }


    // then write fresh records
    for(int i =0 ; i < modifiedRecord.size(); i++)
    {

        // write content to file
        outAccountsFile << modifiedRecord[i]<<"\n";
    }

    // close file
    outAccountsFile.close();



    return true;


};







