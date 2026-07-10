#include "Vault.h"



void Vault::init()
{
    accounts[0] =
        Account(
            1,
            "GitHub",
            "user@gmail.com",
            "123456"
        );


    accounts[1] =
        Account(
            2,
            "Google",
            "google@gmail.com",
            "qwerty"
        );


    accounts[2] =
        Account(
            3,
            "Steam",
            "steam@mail.com",
            "password"
        );


    count = 3;
}



int Vault::getCount()
{
    return count;
}



bool Vault::isValidIndex(int index)
{
    return index >= 0 && index < count;
}



Account& Vault::get(int index)
{
    if(!isValidIndex(index))
    {
        return invalidAccount;
    }


    return accounts[index];
}



bool Vault::add(const Account& account)
{
    if(count >= MAX_ACCOUNTS)
    {
        return false;
    }


    accounts[count] = account;

    count++;


    return true;
}



bool Vault::remove(int index)
{
    if(!isValidIndex(index))
    {
        return false;
    }


    for(int i = index; i < count - 1; i++)
    {
        accounts[i] = accounts[i + 1];
    }


    count--;


    return true;
}



bool Vault::update(
    int index,
    const Account& account
)
{
    if(!isValidIndex(index))
    {
        return false;
    }


    accounts[index] = account;


    return true;
}



void Vault::clear()
{
    count = 0;
}



bool Vault::exists(int id)
{
    for(int i = 0; i < count; i++)
    {
        if(accounts[i].id == id)
        {
            return true;
        }
    }


    return false;
}