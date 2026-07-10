#include "VaultScreen.h"
#include "AccountScreen.h"
#include "AddAccountScreen.h"
#include <Arduino.h>


void VaultScreen::init(
    Display* display,
    Vault* vault,
    Navigation* navigation,
    AccountScreen* accountScreen,
    AddAccountScreen* addAccountScreen
)
{
    this->display = display;

    this->vault = vault;

    this->navigation = navigation;

    this->accountScreen = accountScreen;

    this->addAccountScreen = addAccountScreen;

    menu.init(vault);

    scrollOffset = 0;
}


void VaultScreen::updateScroll(int total)
{
    int selected = menu.getSelected();


    if(selected < scrollOffset)
    {
        scrollOffset = selected;
    }

    if(selected >= scrollOffset + VISIBLE_ROWS)
    {
        scrollOffset = selected - VISIBLE_ROWS + 1;
    }

    int maxOffset = total - VISIBLE_ROWS;

    if(maxOffset < 0)
    {
        maxOffset = 0;
    }

    if(scrollOffset > maxOffset)
    {
        scrollOffset = maxOffset;
    }

    if(scrollOffset < 0)
    {
        scrollOffset = 0;
    }
}


void VaultScreen::draw()
{
    int count = vault->getCount();

    int total = count + 1;


    // Реальные данные из Vault

    for(int i = 0; i < count; i++)
    {
        itemNames[i] = vault->get(i).name;

        items[i] = itemNames[i].c_str();
    }

    itemNames[count] = "+ Add Account";

    items[count] = itemNames[count].c_str();


    updateScroll(total);


    int visibleCount = total - scrollOffset;

    if(visibleCount > VISIBLE_ROWS)
    {
        visibleCount = VISIBLE_ROWS;
    }


    for(int i = 0; i < visibleCount; i++)
    {
        windowItems[i] = items[scrollOffset + i];
    }


    int relativeSelected = menu.getSelected() - scrollOffset;


    display->drawMenu(
        "Vault",
        windowItems,
        visibleCount,
        relativeSelected
    );
}


void VaultScreen::update(ButtonEvent event)
{
    if(event == ButtonEvent::BACK)
    {
        navigation->back();

        return;
    }

    if(event == ButtonEvent::SELECT)
    {
        if(menu.isAddAccountSelected())
        {
            navigation->setScreen(
                addAccountScreen
            );

            return;
        }

        int selected = menu.getSelected();

        accountScreen->openAccount(
            selected
        );

        navigation->setScreen(
            accountScreen
        );

        return;
    }

    if(event == ButtonEvent::NEXT || event == ButtonEvent::PREV)
    {
        menu.handle(event);

        draw();

        return;
    }
}