#pragma once

#include "Account.h"


class Vault
{

private:

    static const int MAX_ACCOUNTS = 10;

    Account accounts[MAX_ACCOUNTS];

    int count = 0;

    Account invalidAccount;


public:

    void init();


    int getCount();


    bool isValidIndex(int index);


    Account& get(int index);


    bool add(const Account& account);


    bool remove(int index);


    bool update(
        int index,
        const Account& account
    );


    void clear();


    bool exists(int id);

};