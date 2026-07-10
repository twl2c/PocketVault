#include "AboutScreen.h"


void AboutScreen::init(
    Display* display,
    Navigation* navigation
)
{
    this->display = display;

    this->navigation = navigation;
}


void AboutScreen::draw()
{
    display->showTitle("About");
}


void AboutScreen::update(ButtonEvent event)
{
    if(event == ButtonEvent::BACK)
    {
        navigation->back();

        return;
    }
}