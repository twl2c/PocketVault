#include "VaultMenu.h"


void VaultMenu::init(Vault* vault)
{
    this->vault = vault;

    selected = 0;
}


int VaultMenu::getCount()
{
    return vault->getCount() + 1;
}


void VaultMenu::handle(ButtonEvent event)
{
    int count = getCount();

    if(event == ButtonEvent::NEXT)
    {
        selected++;

        if(selected >= count)
        {
            selected = 0;
        }
    }

    if(event == ButtonEvent::PREV)
    {
        selected--;

        if(selected < 0)
        {
            selected = count - 1;
        }
    }
}


int VaultMenu::getSelected()
{
    return selected;
}


bool VaultMenu::isAddAccountSelected()
{
    return selected == vault->getCount();
}


const char* VaultMenu::getCurrentName()
{
    if(isAddAccountSelected())
    {
        return "+ Add Account";
    }

    return vault->get(selected).name.c_str();
}