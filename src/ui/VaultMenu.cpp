#include "VaultMenu.h"


void VaultMenu::init(Vault* vault)
{
    this->vault = vault;

    selected = 0;
}



void VaultMenu::handle(ButtonEvent event)
{

    if(event == ButtonEvent::NEXT)
    {

        selected++;


        if(selected >= vault->getCount())
        {
            selected = 0;
        }

    }

}



int VaultMenu::getSelected()
{
    return selected;
}



const char* VaultMenu::getCurrentName()
{
    return vault->get(selected).name;
}