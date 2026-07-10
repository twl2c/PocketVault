#pragma once

enum class ButtonEvent
{
    NONE,
    SELECT,
    NEXT,
    PREV,
    BACK
};

class Buttons
{

private:

    struct State
    {
        bool pressed = false;

        unsigned long pressStart = 0;

        bool holdFired = false;
    };

    static const unsigned long HOLD_THRESHOLD_MS = 800;

    State stateA;

    State stateB;

    ButtonEvent pendingEvent = ButtonEvent::NONE;

    ButtonEvent checkButton(
        bool isPressedNow,
        State& state,
        ButtonEvent clickEvent,
        ButtonEvent holdEvent
    );

public:

    void init();

    void update();

    ButtonEvent getEvent();

};