#pragma once

#include "../input/Buttons.h"


class Screen
{
public:

    virtual ~Screen() = default;


    virtual void draw() = 0;


    virtual void update(ButtonEvent event) = 0;
};