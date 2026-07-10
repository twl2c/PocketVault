#pragma once
#include "../vault/Account.h"

class Display
{

public:

    void init();

    void drawMenu(
        const char* title,
        const char* items[],
        int count,
        int selected
    );

    void showTitle(const char* title);

    void drawAccount(
        const Account& account,
        bool showPassword
    );

    void drawAddAccount(
        const String fields[3],
        int currentField,
        const char* candidate
    );

    void drawPasswordPrompt(
        const String& title,
        int enteredLength,
        const char* candidate,
        const String& message
    );

};