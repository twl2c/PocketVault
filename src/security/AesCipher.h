#pragma once

#include <Arduino.h>

class AesCipher
{

public:

    // Возвращает hex-строку: IV (16 байт) + шифротекст (PKCS7-padded)

    static String encryptToHex(
        const String& plaintext,
        const uint8_t key[32]
    );


    // ok = false при повреждённых данных / неверном ключе

    static String decryptFromHex(
        const String& hexData,
        const uint8_t key[32],
        bool& ok
    );

};