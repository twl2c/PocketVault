#pragma once

#include "../vault/Vault.h"
#include "../input/Buttons.h"


class VaultMenu
{

private:

    Vault* vault;

    int selected;


public:

    void init(Vault* vault);


    void handle(ButtonEvent event);


    int getSelected();


    const char* getCurrentName();


};