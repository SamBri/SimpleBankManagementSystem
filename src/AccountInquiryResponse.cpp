#include "AccountInquiryResponse.h"

// functions definitions


AccountInquiryResponse::AccountInquiryResponse()
{
    //ctor
}

AccountInquiryResponse::~AccountInquiryResponse()
{
    //dtor
}

void AccountInquiryResponse::setAccount(Account* accPtr){

   this->accountPtr  = accPtr;

}

void AccountInquiryResponse::setResponseMsg(std::string msg){

responseMsg = msg;
}



void AccountInquiryResponse::setStatus(std::string status){
this->status = status;
}


Account* AccountInquiryResponse::getAccount(){

return this->accountPtr;
}


std::string AccountInquiryResponse::getResponseMsg(){

return this->responseMsg;
}


std::string AccountInquiryResponse::getStatus(){

return this->status;
}
