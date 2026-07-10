#include "Screen.h"
#include "../ui/Display.h"
#include "../vault/Vault.h"
#include "../core/Navigation.h"

class EditAccountScreen;

class AccountScreen : public Screen
{

private:

    Display* display;

    Vault* vault;

    Navigation* navigation;

    EditAccountScreen* editAccountScreen;

    int accountIndex;

    bool showPassword;

public:

    void init(
        Display* display,
        Vault* vault,
        Navigation* navigation,
        EditAccountScreen* editAccountScreen
    );

    void openAccount(
        int index
    );

    void draw() override;

    void update(ButtonEvent event) override;

};