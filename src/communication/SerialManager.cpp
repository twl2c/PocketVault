#include "SerialManager.h"


void SerialManager::init(
    Vault* vault,
    Storage* storage
)
{
    this->vault = vault;

    this->storage = storage;

    buffer = "";

    state = State::IDLE;

    pendingName = "";

    pendingLogin = "";
}


void SerialManager::update()
{
    if(!Serial)
    {
        // USB CDC не подключён к хосту — нечего читать,

        // не трогаем буфер вообще, чтобы не зависнуть в while().

        return;
    }


    int bytesRead = 0;


    while(Serial.available() && bytesRead < MAX_BYTES_PER_UPDATE)
    {
        int incoming = Serial.read();

        bytesRead++;


        if(incoming < 0)
        {
            // available() соврал / поток закрылся — выходим сразу,

            // а не крутимся дальше.

            break;
        }

        char c = (char)incoming;


        if(c == '\n')
        {
            buffer.trim();


            if(state == State::IDLE)
            {
                handleCommand(buffer);
            }
            else
            {
                handleAddInput(buffer);
            }


            buffer = "";
        }
        else if(c != '\r')
        {
            buffer += c;

            // Защита от переполнения буфера, если хост шлёт мусор без '\n'

            if(buffer.length() > 256)
            {
                buffer = "";
            }
        }
    }
}


// ---------- Формат ответа ----------

void SerialManager::sendOk()
{
    Serial.println("OK");
}


void SerialManager::sendOk(const String& data)
{
    Serial.println("OK");

    Serial.println(data);
}


void SerialManager::sendError(int code, const String& description)
{
    Serial.print("ERROR:");

    Serial.print(code);

    Serial.print(":");

    Serial.println(description);
}


// ---------- Разбор команд ----------

int SerialManager::findIndexById(int id)
{
    for(int i = 0; i < vault->getCount(); i++)
    {
        if(vault->get(i).id == id)
        {
            return i;
        }
    }

    return -1;
}


void SerialManager::handleCommand(const String& line)
{
    if(line == "LIST")
    {
        cmdList();

        return;
    }

    if(line.startsWith("GET ") || line == "GET")
    {
        cmdGet(line.startsWith("GET ") ? line.substring(4) : "");

        return;
    }

    if(line == "ADD")
    {
        cmdAdd();

        return;
    }

    if(line.startsWith("DELETE ") || line == "DELETE")
    {
        cmdDelete(line.startsWith("DELETE ") ? line.substring(7) : "");

        return;
    }

    if(line == "SAVE")
    {
        cmdSave();

        return;
    }

    if(line.length() == 0)
    {
        return;
    }

    sendError(1, "Unknown command");
}


void SerialManager::handleAddInput(const String& line)
{
    if(state == State::WAITING_ADD_NAME)
    {
        pendingName = line;

        state = State::WAITING_ADD_LOGIN;

        sendOk("SEND_LOGIN");

        return;
    }

    if(state == State::WAITING_ADD_LOGIN)
    {
        pendingLogin = line;

        state = State::WAITING_ADD_PASSWORD;

        sendOk("SEND_PASSWORD");

        return;
    }

    if(state == State::WAITING_ADD_PASSWORD)
    {
        String pendingPassword = line;


        int id = vault->getCount() + 1;

        while(vault->exists(id))
        {
            id++;
        }

        Account account(
            id,
            pendingName,
            pendingLogin,
            pendingPassword
        );


        bool added = vault->add(account);


        state = State::IDLE;

        pendingName = "";

        pendingLogin = "";


        if(added)
        {
            sendOk("ADDED:" + String(id));
        }
        else
        {
            sendError(3, "Vault is full");
        }

        return;
    }
}


void SerialManager::cmdList()
{
    Serial.println("OK");

    Serial.println(
        vault->getCount()
    );


    for(int i = 0; i < vault->getCount(); i++)
    {
        Account& account = vault->get(i);


        Serial.print(account.id);

        Serial.print("|");


        Serial.print(account.name);

        Serial.print("|");


        Serial.print(account.login);

        Serial.print("|");


        Serial.println(account.password);
    }


    Serial.println("END");
}


void SerialManager::cmdGet(const String& args)
{
    if(args.length() == 0)
    {
        sendError(5, "Missing id argument");

        return;
    }

    int id = args.toInt();

    int index = findIndexById(id);


    if(index < 0)
    {
        sendError(2, "Account not found");

        return;
    }


    Account& account = vault->get(index);

    String data =
        String(account.id) + "|" +
        account.name + "|" +
        account.login + "|" +
        account.password;


    sendOk(data);
}


void SerialManager::cmdAdd()
{
    state = State::WAITING_ADD_NAME;

    pendingName = "";

    pendingLogin = "";

    sendOk("SEND_NAME");
}


void SerialManager::cmdDelete(const String& args)
{
    if(args.length() == 0)
    {
        sendError(5, "Missing id argument");

        return;
    }

    int id = args.toInt();

    int index = findIndexById(id);


    if(index < 0)
    {
        sendError(2, "Account not found");

        return;
    }


    vault->remove(index);


    sendOk("DELETED:" + String(id));
}


void SerialManager::cmdSave()
{
    bool ok = storage->save(*vault);


    if(ok)
    {
        sendOk("SAVED");
    }
    else
    {
        sendError(4, "Save failed");
    }
}