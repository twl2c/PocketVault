#include "Menu.h"



void Menu::init()
{
    items[0] = "Vault";
    items[1] = "Settings";
    items[2] = "Lock";
    items[3] = "";

    selected = 0;
}



void Menu::handle(ButtonEvent event)
{

    if(event == ButtonEvent::NEXT)
    {
        selected++;


        if(selected >= 4)
        {
            selected = 0;
        }
    }

}



const char** Menu::getItems()
{
    return items;
}



int Menu::getCount()
{
    return 4;
}



int Menu::getSelected()
{
    return selected;
}