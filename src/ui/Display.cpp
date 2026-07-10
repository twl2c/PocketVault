#include "Display.h"
#include <M5Unified.h>


void Display::init()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);
}



void Display::drawMenu(
    const char* title,
    const char* items[],
    int count,
    int selected
)
{
    M5.Display.clear();


    M5.Display.setTextSize(1);


    int screenWidth = M5.Display.width();

    int textWidth = M5.Display.textWidth(title);


    int x = (screenWidth - textWidth) / 2;


    M5.Display.setCursor(x, 5);

    M5.Display.println(title);



    M5.Display.setTextSize(2);


    int y = 35;


    for(int i = 0; i < count; i++)
    {
        M5.Display.setCursor(5, y);


        if(i == selected)
        {
            M5.Display.print("> ");
        }
        else
        {
            M5.Display.print("  ");
        }


        M5.Display.println(items[i]);


        y += 25;
    }
}



void Display::showTitle(const char* title)
{
    M5.Display.clear();


    M5.Display.setTextSize(2);


    M5.Display.setCursor(10, 30);


    M5.Display.println(title);
}

void Display::drawAccount(
    const Account& account,
    bool showPassword
)
{
    M5.Display.clear();

    M5.Display.setTextSize(2);

    int x = (M5.Display.width() - M5.Display.textWidth(account.name)) / 2;

    M5.Display.setCursor(x, 5);
    M5.Display.println(account.name);

    M5.Display.setTextSize(1);

    M5.Display.setCursor(5, 40);
    M5.Display.println("Login:");

    M5.Display.setCursor(5, 55);
    M5.Display.println(account.login);

    M5.Display.setCursor(5, 80);
    M5.Display.println("Password:");

    M5.Display.setCursor(5, 95);

    if(showPassword)
    {
        M5.Display.println(account.password);
    }
    else
    {
        M5.Display.println("********");
    }

    M5.Display.setCursor(5, 120);

    if(showPassword)
    {
        M5.Display.println("A Hide   B Back");
    }
    else
    {
        M5.Display.println("A Show   B Back");
    }
}

void Display::drawAddAccount(
    const String fields[3],
    int currentField,
    const char* candidate
)
{
    static const char* labels[3] = { "Name:", "Login:", "Password:" };

    M5.Display.clear();

    M5.Display.setTextSize(2);

    int x = (M5.Display.width() - M5.Display.textWidth("Add Account")) / 2;

    M5.Display.setCursor(x, 5);
    M5.Display.println("Add Account");

    M5.Display.setTextSize(1);

    int y = 40;

    for(int i = 0; i < 3; i++)
    {
        M5.Display.setCursor(5, y);

        if(i == currentField)
        {
            M5.Display.print("> ");
        }
        else
        {
            M5.Display.print("  ");
        }

        M5.Display.print(labels[i]);

        M5.Display.print(" ");

        M5.Display.print(fields[i]);

        if(i == currentField)
        {
            M5.Display.print("_");
        }

        M5.Display.println();

        y += 20;
    }

    M5.Display.setCursor(5, y + 10);
    M5.Display.print("Char: ");
    M5.Display.println(candidate);

    M5.Display.setCursor(5, y + 30);
    M5.Display.println("B Del/Back  A/B Next  Sel OK");
}


void Display::drawPasswordPrompt(
    const String& title,
    int enteredLength,
    const char* candidate,
    const String& message
)
{
    M5.Display.clear();

    M5.Display.setTextSize(2);

    int x = (M5.Display.width() - M5.Display.textWidth(title)) / 2;

    M5.Display.setCursor(x, 5);
    M5.Display.println(title);

    M5.Display.setTextSize(1);

    M5.Display.setCursor(5, 40);
    M5.Display.print("Password: ");

    for(int i = 0; i < enteredLength; i++)
    {
        M5.Display.print("*");
    }

    M5.Display.println();

    M5.Display.setCursor(5, 60);
    M5.Display.print("Char: ");
    M5.Display.println(candidate);

    if(message.length() > 0)
    {
        M5.Display.setCursor(5, 85);
        M5.Display.println(message);
    }

    M5.Display.setCursor(5, 110);
    M5.Display.println("B Del/Back  A/B Next  Sel OK");
}