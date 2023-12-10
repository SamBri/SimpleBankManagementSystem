#ifndef SECURITYSERVICERESPONSE_H
#define SECURITYSERVICERESPONSE_H

#include <string>

/**
SecurityServiceResponse object for data handling.
**/


class SecurityServiceResponse
{
    public:
        SecurityServiceResponse();
        virtual ~SecurityServiceResponse();
        void setResponseMsg(std::string responseMsg);
        std::string getResponseMsg();
        void setStatus(std::string status);
        std::string getStatus();
        void setContent(std::string data);
        std::string getContent();

    protected:

    private:
        std::string responseMsg;
        std::string status;
        std::string data;
};

#endif // SECURITYSERVICERESPONSE_H
