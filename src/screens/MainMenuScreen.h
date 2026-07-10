#pragma once

#include "Screen.h"
#include "../ui/Menu.h"
#include "../ui/Display.h"
#include "../core/Navigation.h"

class VaultScreen;
class SettingsScreen;
class AboutScreen;

class MainMenuScreen : public Screen
{

private:

    Display* display;

    Menu menu;

    Navigation* navigation;

    VaultScreen* vaultScreen;

    SettingsScreen* settingsScreen;

    AboutScreen* aboutScreen;

public:

    void init(
        Display* display,
        Navigation* navigation,
        VaultScreen* vaultScreen,
        SettingsScreen* settingsScreen,
        AboutScreen* aboutScreen
    );

    void draw() override;

    void update(ButtonEvent event) override;

    int getSelected();

};