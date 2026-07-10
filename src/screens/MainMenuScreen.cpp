#include "MainMenuScreen.h"
#include "VaultScreen.h"
#include "SettingsScreen.h"
#include "AboutScreen.h"


void MainMenuScreen::init(
    Display* display,
    Navigation* navigation,
    VaultScreen* vaultScreen,
    SettingsScreen* settingsScreen,
    AboutScreen* aboutScreen
)
{
    this->display = display;

    this->navigation = navigation;

    this->vaultScreen = vaultScreen;

    this->settingsScreen = settingsScreen;

    this->aboutScreen = aboutScreen;

    menu.init();
}


void MainMenuScreen::draw()
{
    display->drawMenu(
        "PocketVault",
        menu.getItems(),
        menu.getCount(),
        menu.getSelected()
    );
}


void MainMenuScreen::update(ButtonEvent event)
{
    if(event == ButtonEvent::SELECT)
    {
        switch(menu.getSelected())
        {
            case 0:
                navigation->setScreen(vaultScreen);
                return;

            case 1:
                navigation->setScreen(settingsScreen);
                return;

            case 2:
                navigation->setScreen(aboutScreen);
                return;
        }

        return;
    }

    if(event == ButtonEvent::BACK)
    {
        navigation->back();

        return;
    }

    if(event != ButtonEvent::NONE)
    {
        menu.handle(event);

        draw();
    }
}


int MainMenuScreen::getSelected()
{
    return menu.getSelected();
}