#pragma once

#include <Arduino.h>


struct Account
{
    int id;

    String name;

    String login;

    String password;


    Account()
        : id(0),
          name(""),
          login(""),
          password("")
    {
    }


    Account(
        int id,
        String name,
        String login,
        String password
    )
        : id(id),
          name(name),
          login(login),
          password(password)
    {
    }
};