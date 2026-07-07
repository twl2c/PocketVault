#pragma once

#include "../ui/Display.h"
#include "../ui/Menu.h"
#include "../input/Buttons.h"
#include "AppState.h"
#include "../vault/Vault.h"
#include "../ui/VaultMenu.h"

class App
{

private:

    Display display;

    Buttons buttons;

    Menu menu;

    Vault vault;

    VaultMenu vaultMenu;

    AppState state;


public:

    void init();

    void update();

};