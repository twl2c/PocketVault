#include "Buttons.h"
#include <M5Unified.h>
#include <Arduino.h>


void Buttons::init()
{
    stateA = State();

    stateB = State();

    pendingEvent = ButtonEvent::NONE;
}


ButtonEvent Buttons::checkButton(
    bool isPressedNow,
    State& state,
    ButtonEvent clickEvent,
    ButtonEvent holdEvent
)
{
    unsigned long now = millis();


    if(isPressedNow && !state.pressed)
    {
        state.pressed = true;

        state.pressStart = now;

        state.holdFired = false;
    }
    else if(isPressedNow && state.pressed)
    {
        if(!state.holdFired && (now - state.pressStart >= HOLD_THRESHOLD_MS))
        {
            state.holdFired = true;

            return holdEvent;
        }
    }
    else if(!isPressedNow && state.pressed)
    {
        state.pressed = false;

        if(!state.holdFired)
        {
            return clickEvent;
        }
    }

    return ButtonEvent::NONE;
}


void Buttons::update()
{
    M5.update();


    ButtonEvent eventA = checkButton(
        M5.BtnA.isPressed(),
        stateA,
        ButtonEvent::SELECT,
        ButtonEvent::PREV
    );

    ButtonEvent eventB = checkButton(
        M5.BtnB.isPressed(),
        stateB,
        ButtonEvent::NEXT,
        ButtonEvent::BACK
    );


    pendingEvent = (eventA != ButtonEvent::NONE) ? eventA : eventB;
}


ButtonEvent Buttons::getEvent()
{
    return pendingEvent;
}