#include "PasswordUtil.h"
#include "mbedtls/sha256.h"


void PasswordUtil::sha256Bytes(const String& input, uint8_t output[32])
{
    mbedtls_sha256(
        (const unsigned char*)input.c_str(),
        input.length(),
        output,
        0 // 0 = SHA-256 (не SHA-224)
    );
}


String PasswordUtil::sha256Hex(const String& input)
{
    uint8_t hash[32];

    sha256Bytes(input, hash);


    String result = "";

    char byteStr[3];


    for(int i = 0; i < 32; i++)
    {
        sprintf(byteStr, "%02x", hash[i]);

        result += byteStr;
    }


    return result;
}


void PasswordUtil::deriveKey(const String& password, uint8_t key[32])
{
    // Отдельный контекст ("AES_KEY_V1:") гарантирует,

    // что AES-ключ не совпадает с хэшем, который хранится

    // для проверки пароля (иначе ключ был бы виден в открытую во Flash).

    String keyInput = "AES_KEY_V1:" + password;

    sha256Bytes(keyInput, key);
}