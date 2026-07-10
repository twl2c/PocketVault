#include "App.h"

#include <M5Unified.h>


void App::init()
{
    auto cfg = M5.config();

    M5.begin(cfg);

    display.init();

    buttons.init();

    storage.init();

    serialManager.init(&vault, &storage);

    editAccountScreen.init(
        &display,
        &vault,
        &navigation,
        &storage
    );

    accountScreen.init(
        &display,
        &vault,
        &navigation,
        &editAccountScreen
    );

    addAccountScreen.init(
        &display,
        &vault,
        &navigation,
        &storage
    );

    vaultScreen.init(
        &display,
        &vault,
        &navigation,
        &accountScreen,
        &addAccountScreen
    );

    settingsScreen.init(
        &display,
        &navigation
    );

    aboutScreen.init(
        &display,
        &navigation
    );

    mainMenuScreen.init(
        &display,
        &navigation,
        &vaultScreen,
        &settingsScreen,
        &aboutScreen
    );

    masterPasswordScreen.init(
        &display,
        &navigation,
        &storage,
        &vault,
        &mainMenuScreen
    );

    navigation.init(&masterPasswordScreen);
}


void App::update()
{
    buttons.update();

    ButtonEvent event = buttons.getEvent();

    navigation.update(event);

    serialManager.update();
}