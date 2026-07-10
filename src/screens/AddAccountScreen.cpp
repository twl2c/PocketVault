#include "AddAccountScreen.h"


const char* AddAccountScreen::CHARSET[] = {
    " ",
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
    "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
    "u", "v", "w", "x", "y", "z",
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
    "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
    "U", "V", "W", "X", "Y", "Z",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    ".", "-", "_", "@",
    "OK"
};

const int AddAccountScreen::CHARSET_SIZE =
    sizeof(CHARSET) / sizeof(CHARSET[0]);


void AddAccountScreen::init(
    Display* display,
    Vault* vault,
    Navigation* navigation,
    Storage* storage
)
{
    this->display = display;

    this->vault = vault;

    this->navigation = navigation;

    this->storage = storage;

    reset();
}


void AddAccountScreen::reset()
{
    currentField = Field::NAME;

    name = "";

    login = "";

    password = "";

    charIndex = 0;
}


String AddAccountScreen::currentValue()
{
    if(currentField == Field::NAME)
    {
        return name;
    }

    if(currentField == Field::LOGIN)
    {
        return login;
    }

    return password;
}


void AddAccountScreen::appendChar(const String& symbol)
{
    if(currentField == Field::NAME)
    {
        name += symbol;
    }
    else if(currentField == Field::LOGIN)
    {
        login += symbol;
    }
    else
    {
        password += symbol;
    }

    charIndex = 0;
}


void AddAccountScreen::backspace()
{
    if(currentField == Field::NAME && name.length() > 0)
    {
        name.remove(name.length() - 1);
    }
    else if(currentField == Field::LOGIN && login.length() > 0)
    {
        login.remove(login.length() - 1);
    }
    else if(currentField == Field::PASSWORD && password.length() > 0)
    {
        password.remove(password.length() - 1);
    }
}


void AddAccountScreen::nextField()
{
    if(currentField == Field::NAME)
    {
        currentField = Field::LOGIN;

        charIndex = 0;

        return;
    }

    if(currentField == Field::LOGIN)
    {
        currentField = Field::PASSWORD;

        charIndex = 0;

        return;
    }

    // Поле PASSWORD было последним — сохраняем аккаунт

    save();
}


void AddAccountScreen::save()
{
    // Не сохраняем полностью пустой аккаунт (пустое имя)

    if(name.length() == 0)
    {
        return;
    }

    int id = vault->getCount() + 1;

    while(vault->exists(id))
    {
        id++;
    }

    Account account(
        id,
        name,
        login,
        password
    );

    vault->add(account);

    storage->save(*vault);

    reset();

    navigation->back();
}


void AddAccountScreen::draw()
{
    String fields[3] = { name, login, password };

    int fieldIndex = static_cast<int>(currentField);

    display->drawAddAccount(
        fields,
        fieldIndex,
        CHARSET[charIndex]
    );
}


void AddAccountScreen::update(ButtonEvent event)
{
    if(event == ButtonEvent::NEXT)
    {
        charIndex = (charIndex + 1) % CHARSET_SIZE;

        draw();

        return;
    }

    if(event == ButtonEvent::PREV)
    {
        charIndex = (charIndex - 1 + CHARSET_SIZE) % CHARSET_SIZE;

        draw();

        return;
    }

    if(event == ButtonEvent::SELECT)
    {
        String symbol = CHARSET[charIndex];

        if(symbol == "OK")
        {
            nextField();
        }
        else
        {
            appendChar(symbol);
        }

        draw();

        return;
    }

    if(event == ButtonEvent::BACK)
    {
        if(currentValue().length() > 0)
        {
            backspace();

            draw();

            return;
        }

        reset();

        navigation->back();

        return;
    }
}