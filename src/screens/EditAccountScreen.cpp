#include "EditAccountScreen.h"


const char* EditAccountScreen::CHARSET[] = {
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

const int EditAccountScreen::CHARSET_SIZE =
    sizeof(CHARSET) / sizeof(CHARSET[0]);


void EditAccountScreen::init(
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

    accountIndex = 0;

    currentField = Field::NAME;

    charIndex = 0;
}


void EditAccountScreen::openAccount(
    int index
)
{
    if(!vault->isValidIndex(index))
    {
        return;
    }

    accountIndex = index;

    Account& account = vault->get(index);


    // Предзаполняем поля текущими значениями аккаунта

    name = account.name;

    login = account.login;

    password = account.password;


    currentField = Field::NAME;

    charIndex = 0;

    draw();
}


String EditAccountScreen::currentValue()
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


void EditAccountScreen::appendChar(const String& symbol)
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


void EditAccountScreen::backspace()
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


void EditAccountScreen::nextField()
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

    // PASSWORD было последним полем — сохраняем изменения

    save();
}


void EditAccountScreen::save()
{
    if(name.length() == 0)
    {
        return;
    }

    if(!vault->isValidIndex(accountIndex))
    {
        navigation->back();

        return;
    }

    Account& existing = vault->get(accountIndex);

    Account updated(
        existing.id,
        name,
        login,
        password
    );

    vault->update(
        accountIndex,
        updated
    );

    storage->save(*vault);

    navigation->back();
}


void EditAccountScreen::draw()
{
    String fields[3] = { name, login, password };

    int fieldIndex = static_cast<int>(currentField);

    display->drawAddAccount(
        fields,
        fieldIndex,
        CHARSET[charIndex]
    );
}


void EditAccountScreen::update(ButtonEvent event)
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

        navigation->back();

        return;
    }
}