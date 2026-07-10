#include "SettingsScreen.h"


void SettingsScreen::init(
    Display* display,
    Navigation* navigation
)
{
    this->display = display;

    this->navigation = navigation;
}


void SettingsScreen::draw()
{
    display->showTitle("Settings");
}


void SettingsScreen::update(ButtonEvent event)
{
    if(event == ButtonEvent::BACK)
    {
        navigation->back();

        return;
    }
}