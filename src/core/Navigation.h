#pragma once

#include "../screens/Screen.h"

class Navigation
{

private:

    Screen* currentScreen = nullptr;

    Screen* previousScreen = nullptr;

public:

    void init(Screen* initialScreen);

    void setScreen(Screen* screen);

    void update(ButtonEvent event);

    void draw();

    void back();

};