#include "Storage.h"
#include "../security/AesCipher.h"
#include <string.h>



void Storage::init()
{

}



int Storage::readVersion()
{
    preferences.begin("vault", true);

    int version = preferences.getInt("version", 0);

    preferences.end();

    return version;
}



void Storage::writeVersion(int version)
{
    preferences.begin("vault", false);

    preferences.putInt("version", version);

    preferences.end();
}



void Storage::migrate(int fromVersion)
{
    // Точка расширения для будущих миграций схемы хранения.

    writeVersion(STORAGE_VERSION);
}



void Storage::saveAccounts(Vault& vault)
{
    preferences.begin("vault", false);


    int count = vault.getCount();


    preferences.putInt(
        "count",
        count
    );


    for(int i = 0; i < count; i++)
    {
        Account& account = vault.get(i);


        String prefix = "acc" + String(i);


        // Имя хранится в открытом виде — не относится к login/password

        preferences.putString(
            (prefix + "_name").c_str(),
            account.name
        );


        // Login и password шифруются AES-256-CBC перед записью

        String encryptedLogin = AesCipher::encryptToHex(
            account.login,
            encryptionKey
        );

        String encryptedPassword = AesCipher::encryptToHex(
            account.password,
            encryptionKey
        );


        preferences.putString(
            (prefix + "_login").c_str(),
            encryptedLogin
        );

        preferences.putString(
            (prefix + "_pass").c_str(),
            encryptedPassword
        );
    }


    preferences.end();
}



void Storage::loadAccounts(Vault& vault)
{
    preferences.begin("vault", true);


    int count = preferences.getInt(
        "count",
        0
    );


    vault.clear();


    for(int i = 0; i < count; i++)
    {
        String prefix = "acc" + String(i);


        String name =
            preferences.getString(
                (prefix + "_name").c_str(),
                ""
            );


        String encryptedLogin =
            preferences.getString(
                (prefix + "_login").c_str(),
                ""
            );

        String encryptedPassword =
            preferences.getString(
                (prefix + "_pass").c_str(),
                ""
            );


        bool loginOk = false;

        bool passwordOk = false;


        String login = AesCipher::decryptFromHex(
            encryptedLogin,
            encryptionKey,
            loginOk
        );

        String password = AesCipher::decryptFromHex(
            encryptedPassword,
            encryptionKey,
            passwordOk
        );


        // Если расшифровать не удалось (неверный ключ / повреждённые данные),

        // не подставляем мусор — оставляем поле пустым.

        if(!loginOk)
        {
            login = "";
        }

        if(!passwordOk)
        {
            password = "";
        }


        Account account(
            i,
            name,
            login,
            password
        );


        vault.add(account);
    }


    preferences.end();
}



bool Storage::save(Vault& vault)
{
    if(!hasKey)
    {
        return false;
    }

    saveAccounts(vault);

    writeVersion(STORAGE_VERSION);

    return true;
}



bool Storage::load(Vault& vault)
{
    if(!hasKey)
    {
        return false;
    }

    preferences.begin("vault", true);

    bool hasVersion = preferences.isKey("version");

    bool hasLegacyData = preferences.isKey("count");

    preferences.end();


    if(!hasVersion && !hasLegacyData)
    {
        return false;
    }


    if(!hasVersion && hasLegacyData)
    {
        migrate(0);
    }
    else
    {
        int version = readVersion();

        if(version != STORAGE_VERSION)
        {
            migrate(version);
        }
    }


    loadAccounts(vault);


    return true;
}



bool Storage::hasMasterPassword()
{
    preferences.begin("auth", true);

    bool exists = preferences.isKey("pwhash");

    preferences.end();

    return exists;
}



bool Storage::saveMasterPasswordHash(const String& hashHex)
{
    preferences.begin("auth", false);

    size_t written = preferences.putString("pwhash", hashHex);

    preferences.end();

    return written > 0;
}



String Storage::loadMasterPasswordHash()
{
    preferences.begin("auth", true);

    String hash = preferences.getString("pwhash", "");

    preferences.end();

    return hash;
}



void Storage::setEncryptionKey(const uint8_t key[32])
{
    memcpy(encryptionKey, key, 32);

    hasKey = true;
}