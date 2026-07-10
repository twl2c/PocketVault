#pragma once

#include "Screen.h"
#include "../ui/Display.h"
#include "../core/Navigation.h"
#include "../storage/Storage.h"
#include "../vault/Vault.h"

class MasterPasswordScreen : public Screen
{

private:

    enum class Mode
    {
        UNLOCK,
        SETUP_ENTER,
        SETUP_CONFIRM
    };

    Display* display;

    Navigation* navigation;

    Storage* storage;

    Vault* vault;

    Screen* mainMenuScreen;

    Mode mode;

    String password;

    String firstPassword;

    int charIndex;

    String message;

    static const char* CHARSET[];

    static const int CHARSET_SIZE;

    void appendChar(const String& symbol);

    void backspace();

    void confirm();

    void resetInput();

public:

    void init(
        Display* display,
        Navigation* navigation,
        Storage* storage,
        Vault* vault,
        Screen* mainMenuScreen
    );

    void draw() override;

    void update(ButtonEvent event) override;

};