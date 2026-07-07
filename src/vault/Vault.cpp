#include "Vault.h"


void Vault::init()
{
    accounts[0] =
    {
        "GitHub",
        "user@gmail.com",
        "123456"
    };


    accounts[1] =
    {
        "Google",
        "google@gmail.com",
        "qwerty"
    };


    accounts[2] =
    {
        "Steam",
        "player",
        "password"
    };


    count = 3;
}



int Vault::getCount()
{
    return count;
}



Account Vault::get(int index)
{
    return accounts[index];
}