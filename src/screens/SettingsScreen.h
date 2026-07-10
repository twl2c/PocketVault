#pragma once

#include "Screen.h"
#include "../ui/Display.h"
#include "../core/Navigation.h"

class SettingsScreen : public Screen
{

private:

    Display* display;

    Navigation* navigation;

public:

    void init(
        Display* display,
        Navigation* navigation
    );

    void draw() override;

    void update(ButtonEvent event) override;

};