#include "Buttons.h"
#include <M5Unified.h>


void Buttons::init()
{

}


void Buttons::update()
{
    M5.update();
}


ButtonEvent Buttons::getEvent()
{

    if(M5.BtnA.wasPressed())
    {
        return ButtonEvent::SELECT;
    }


    if(M5.BtnB.wasPressed())
    {
        return ButtonEvent::NEXT;
    }


    if(M5.BtnB.pressedFor(800))
    {
        return ButtonEvent::BACK;
    }


    return ButtonEvent::NONE;
}