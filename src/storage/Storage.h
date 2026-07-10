#pragma once

#include <Preferences.h>
#include "../vault/Vault.h"


class Storage
{

private:

    Preferences preferences;

    static const int STORAGE_VERSION = 1;

    uint8_t encryptionKey[32];

    bool hasKey = false;


    int readVersion();

    void writeVersion(int version);

    void migrate(int fromVersion);

    void loadAccounts(Vault& vault);

    void saveAccounts(Vault& vault);


public:

    void init();


    bool save(
        Vault& vault
    );


    bool load(
        Vault& vault
    );


    bool hasMasterPassword();

    bool saveMasterPasswordHash(const String& hashHex);

    String loadMasterPasswordHash();


    void setEncryptionKey(const uint8_t key[32]);

};