#pragma once


enum class ButtonEvent
{
    NONE,
    SELECT,
    NEXT,
    BACK
};


class Buttons
{
public:

    void init();

    void update();

    ButtonEvent getEvent();
};