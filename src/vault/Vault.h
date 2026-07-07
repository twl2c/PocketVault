#pragma once

#include "Account.h"


class Vault
{

private:

    Account accounts[5];

    int count;


public:

    void init();


    int getCount();


    Account get(int index);

};