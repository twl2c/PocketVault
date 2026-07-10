#include "Navigation.h"


void Navigation::init(Screen* initialScreen)
{
    previousScreen = nullptr;

    currentScreen = initialScreen;

    if(currentScreen)
    {
        currentScreen->draw();
    }
}


void Navigation::setScreen(Screen* screen)
{
    previousScreen = currentScreen;

    currentScreen = screen;

    if(currentScreen)
    {
        currentScreen->draw();
    }
}


void Navigation::update(ButtonEvent event)
{
    if(currentScreen)
    {
        currentScreen->update(event);
    }
}


void Navigation::draw()
{
    if(currentScreen)
    {
        currentScreen->draw();
    }
}


void Navigation::back()
{
    if(previousScreen)
    {
        currentScreen = previousScreen;

        currentScreen->draw();
    }
}