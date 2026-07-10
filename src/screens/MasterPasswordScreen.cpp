#include "MasterPasswordScreen.h"
#include "../security/PasswordUtil.h"


const char* MasterPasswordScreen::CHARSET[] = {
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

const int MasterPasswordScreen::CHARSET_SIZE =
    sizeof(CHARSET) / sizeof(CHARSET[0]);


void MasterPasswordScreen::init(
    Display* display,
    Navigation* navigation,
    Storage* storage,
    Vault* vault,
    Screen* mainMenuScreen
)
{
    this->display = display;

    this->navigation = navigation;

    this->storage = storage;

    this->vault = vault;

    this->mainMenuScreen = mainMenuScreen;


    mode = storage->hasMasterPassword() ? Mode::UNLOCK : Mode::SETUP_ENTER;

    resetInput();
}


void MasterPasswordScreen::resetInput()
{
    password = "";

    charIndex = 0;

    message = "";
}


void MasterPasswordScreen::appendChar(const String& symbol)
{
    password += symbol;

    charIndex = 0;
}


void MasterPasswordScreen::backspace()
{
    if(password.length() > 0)
    {
        password.remove(password.length() - 1);
    }
}


void MasterPasswordScreen::confirm()
{
    if(mode == Mode::UNLOCK)
    {
        String storedHash = storage->loadMasterPasswordHash();

        String enteredHash = PasswordUtil::sha256Hex(password);


        if(enteredHash == storedHash)
        {
            uint8_t key[32];

            PasswordUtil::deriveKey(password, key);

            storage->setEncryptionKey(key);


            storage->load(*vault);

            navigation->setScreen(mainMenuScreen);

            return;
        }


        message = "Wrong password";

        password = "";

        charIndex = 0;

        return;
    }


    if(mode == Mode::SETUP_ENTER)
    {
        if(password.length() == 0)
        {
            message = "Password cannot be empty";

            return;
        }


        firstPassword = password;

        password = "";

        charIndex = 0;

        message = "";

        mode = Mode::SETUP_CONFIRM;

        return;
    }


    if(mode == Mode::SETUP_CONFIRM)
    {
        if(password != firstPassword)
        {
            message = "Passwords do not match";

            password = "";

            firstPassword = "";

            charIndex = 0;

            mode = Mode::SETUP_ENTER;

            return;
        }


        String hash = PasswordUtil::sha256Hex(password);

        storage->saveMasterPasswordHash(hash);


        uint8_t key[32];

        PasswordUtil::deriveKey(password, key);

        storage->setEncryptionKey(key);


        vault->init();

        storage->save(*vault);


        navigation->setScreen(mainMenuScreen);

        return;
    }
}


void MasterPasswordScreen::draw()
{
    String title;

    if(mode == Mode::UNLOCK)
    {
        title = "Enter Password";
    }
    else if(mode == Mode::SETUP_ENTER)
    {
        title = "Set Master Password";
    }
    else
    {
        title = "Confirm Password";
    }


    display->drawPasswordPrompt(
        title,
        password.length(),
        CHARSET[charIndex],
        message
    );
}


void MasterPasswordScreen::update(ButtonEvent event)
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
            confirm();
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
        if(password.length() > 0)
        {
            backspace();

            draw();
        }

        return;
    }
}