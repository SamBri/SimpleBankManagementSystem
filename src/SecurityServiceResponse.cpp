#include "SecurityServiceResponse.h"


// functions definitions

SecurityServiceResponse::SecurityServiceResponse()
{
    //ctor
}

SecurityServiceResponse::~SecurityServiceResponse()
{
    //dtor
}



void SecurityServiceResponse::setResponseMsg(std::string msg)
{

    responseMsg = msg;
}



void SecurityServiceResponse::setStatus(std::string status)
{
    this->status = status;
}


std::string SecurityServiceResponse::getResponseMsg()
{

    return this->responseMsg;
}


std::string SecurityServiceResponse::getStatus()
{

    return this->status;
}


void SecurityServiceResponse::setContent(std::string data)
{

    this->data = data;


};
std::string  SecurityServiceResponse::getContent()
{


    return this->data;

};
