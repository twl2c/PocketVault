#pragma once

#include <Arduino.h>

class PasswordUtil
{

public:

    static String sha256Hex(const String& input);

    static void sha256Bytes(const String& input, uint8_t output[32]);

    static void deriveKey(const String& password, uint8_t key[32]);

};     