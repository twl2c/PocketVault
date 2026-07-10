#pragma once

#include "../input/Buttons.h"

class Menu
{

private:

    const char* items[3];

    int selected;

public:

    void init();

    void handle(ButtonEvent event);

    const char** getItems();

    int getCount();

    int getSelected();

};