#pragma once

#include "Screen.h"
#include "../ui/Display.h"
#include "../vault/Vault.h"
#include "../core/Navigation.h"
#include "../storage/Storage.h"

class AddAccountScreen : public Screen
{

private:

    enum class Field
    {
        NAME,
        LOGIN,
        PASSWORD
    };

    Display* display;

    Vault* vault;

    Navigation* navigation;

    Storage* storage;

    Field currentField;

    String name;

    String login;

    String password;

    int charIndex;

    static const char* CHARSET[];

    static const int CHARSET_SIZE;

    String currentValue();

    void appendChar(const String& symbol);

    void backspace();

    void nextField();

    void save();

    void reset();

public:

    void init(
        Display* display,
        Vault* vault,
        Navigation* navigation,
        Storage* storage
    );

    void draw() override;

    void update(ButtonEvent event) override;

};