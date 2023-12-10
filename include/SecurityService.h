#ifndef SECURITYSERVICE_H
#define SECURITYSERVICE_H
#include <string>
#include "SecurityServiceResponse.h"

/**
SecurityService object to facilitate security operations of sensitive user information.
**/

class SecurityService
{
    public:
        SecurityService();
        virtual ~SecurityService();

        static std::string doPasswordEncryption(std::string password);

       static SecurityServiceResponse doPasswordDecryption(std::string password);


        static char getKey();

    protected:

    private:
     static const int key = 5;



};

#endif // SECURITYSERVICE_H
