#ifndef GMRPC_H_INCLUDED
#define GMRPC_H_INCLUDED
#include <string>

/**
*  @brief Struct that stores the values of the initialized User.
*/
struct GMRPC_USER{
    std::string userId;
    std::string username;
    std::string discriminator;
    std::string avatar;
};

#endif // GMRPC_H_INCLUDED
