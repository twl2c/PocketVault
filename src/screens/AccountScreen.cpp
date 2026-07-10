#include "AccountScreen.h"
#include "EditAccountScreen.h"


void AccountScreen::init(
    Display* display,
    Vault* vault,
    Navigation* navigation,
    EditAccountScreen* editAccountScreen
)
{
    this->display = display;

    this->vault = vault;

    this->navigation = navigation;

    this->editAccountScreen = editAccountScreen;

    accountIndex = 0;

    showPassword = false;
}


void AccountScreen::openAccount(
    int index
)
{
    if(!vault->isValidIndex(index))
    {
        return;
    }

    accountIndex = index;

    showPassword = false;

    draw();
}


void AccountScreen::draw()
{
    if(!vault->isValidIndex(accountIndex))
    {
        navigation->back();

        return;
    }

    display->drawAccount(
        vault->get(accountIndex),
        showPassword
    );
}


void AccountScreen::update(ButtonEvent event)
{
    if(event == ButtonEvent::SELECT)
    {
        showPassword = !showPassword;

        draw();

        return;
    }

    if(event == ButtonEvent::PREV)
    {
        editAccountScreen->openAccount(accountIndex);

        navigation->setScreen(editAccountScreen);

        return;
    }

    if(event == ButtonEvent::BACK)
    {
        showPassword = false;

        navigation->back();

        return;
    }
}