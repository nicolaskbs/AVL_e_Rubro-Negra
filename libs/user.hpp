#pragma once

#include <string>

struct User{

    std::string login;
    int userid;
    int region;
    std::string password;

    User(const std::string& login, 
        int userid, 
        int region, 
        const std::string& password)
        : login(login), 
        userid(userid), 
        region(region), 
        password(password) {};

    // Sobrecarga do operador de igualdade para facilitar a busca
    bool operator==(const User& other) const {
        return userid == other.userid;
    }
};