#pragma once

#include "Screen.h"
#include "../ui/Display.h"
#include "../vault/Vault.h"
#include "../core/Navigation.h"
#include "../ui/VaultMenu.h"

class AccountScreen;
class AddAccountScreen;

class VaultScreen : public Screen
{

private:

    static const int VISIBLE_ROWS = 4;

    Display* display;

    Vault* vault;

    Navigation* navigation;

    VaultMenu menu;

    AccountScreen* accountScreen;

    AddAccountScreen* addAccountScreen;

    String itemNames[11];

    const char* items[11];

    const char* windowItems[VISIBLE_ROWS];

    int scrollOffset = 0;

    void updateScroll(int total);

public:

    void init(
        Display* display,
        Vault* vault,
        Navigation* navigation,
        AccountScreen* accountScreen,
        AddAccountScreen* addAccountScreen
    );

    void draw() override;

    void update(ButtonEvent event) override;

};