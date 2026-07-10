#pragma once

#include "../ui/Display.h"
#include "../ui/Menu.h"
#include "../input/Buttons.h"
#include "../vault/Vault.h"
#include "../screens/MainMenuScreen.h"
#include "../core/Navigation.h"
#include "../screens/VaultScreen.h"
#include "../screens/AccountScreen.h"
#include "../screens/AddAccountScreen.h"
#include "../screens/EditAccountScreen.h"
#include "../screens/SettingsScreen.h"
#include "../screens/AboutScreen.h"
#include "../screens/MasterPasswordScreen.h"
#include "../storage/Storage.h"
#include "../communication/SerialManager.h"

class App
{

private:

    Display display;
    Buttons buttons;
    MainMenuScreen mainMenuScreen;
    VaultScreen vaultScreen;
    Vault vault;
    Navigation navigation;
    AccountScreen accountScreen;
    AddAccountScreen addAccountScreen;
    EditAccountScreen editAccountScreen;
    SettingsScreen settingsScreen;
    AboutScreen aboutScreen;
    MasterPasswordScreen masterPasswordScreen;
    Storage storage;
    SerialManager serialManager;

public:

    void init();
    void update();

};