#pragma once

#include <Arduino.h>
#include "../vault/Vault.h"
#include "../storage/Storage.h"

class SerialManager
{

private:

    enum class State
    {
        IDLE,
        WAITING_ADD_NAME,
        WAITING_ADD_LOGIN,
        WAITING_ADD_PASSWORD
    };

    static const int MAX_BYTES_PER_UPDATE = 128;

    Vault* vault;

    Storage* storage;

    String buffer;

    State state = State::IDLE;

    String pendingName;

    String pendingLogin;


    int findIndexById(int id);

    void handleCommand(const String& line);

    void handleAddInput(const String& line);

    void cmdList();

    void cmdGet(const String& args);

    void cmdAdd();

    void cmdDelete(const String& args);

    void cmdSave();


    void sendOk();

    void sendOk(const String& data);

    void sendError(int code, const String& description);


public:

    void init(
        Vault* vault,
        Storage* storage
    );

    void update();

};