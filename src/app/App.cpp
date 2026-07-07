#include "App.h"
#include <M5Unified.h>


void App::init()
{
    auto cfg = M5.config();

    M5.begin(cfg);


    display.init();

    buttons.init();

    menu.init();

    vault.init();

    vaultMenu.init(&vault);


    state = AppState::MAIN_MENU;
}


void App::update()
{
    buttons.update();

    ButtonEvent event = buttons.getEvent();


    switch(state)
    {

        case AppState::MAIN_MENU:
        {
            menu.handle(event);


            if(event == ButtonEvent::SELECT)
            {

                if(menu.getSelected() == 0)
                {
                    state = AppState::ACCOUNT_LIST;


                    vaultMenu.init(&vault);


                    display.showTitle("Vault");
                }

            }


            if(event == ButtonEvent::NEXT)
            {
                display.drawMenu(
                    "PocketVault",
                    menu.getItems(),
                    menu.getCount(),
                    menu.getSelected()
                );
            }

            break;
        }



        case AppState::ACCOUNT_LIST:
        {

            vaultMenu.handle(event);


            if(event == ButtonEvent::NEXT)
            {
                display.showTitle(
                    vaultMenu.getCurrentName()
                );
            }



            if(event == ButtonEvent::BACK)
            {
                state = AppState::MAIN_MENU;


                display.drawMenu(
                    "PocketVault",
                    menu.getItems(),
                    menu.getCount(),
                    menu.getSelected()
                );
            }


            break;
        }



        case AppState::ACCOUNT_VIEW:
        {
            break;
        }



        case AppState::SETTINGS:
        {
            break;
        }

    }
}