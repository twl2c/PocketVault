#include "AesCipher.h"
#include "mbedtls/aes.h"
#include "esp_system.h"
#include <string.h>


namespace
{
    const size_t BLOCK_SIZE = 16;


    void bytesToHex(const uint8_t* data, size_t len, String& out)
    {
        out = "";

        char byteStr[3];


        for(size_t i = 0; i < len; i++)
        {
            sprintf(byteStr, "%02x", data[i]);

            out += byteStr;
        }
    }


    bool hexToBytes(
        const String& hex,
        uint8_t* out,
        size_t maxLen,
        size_t& outLen
    )
    {
        size_t len = hex.length();

        if(len % 2 != 0)
        {
            return false;
        }

        size_t byteCount = len / 2;

        if(byteCount > maxLen)
        {
            return false;
        }

        for(size_t i = 0; i < byteCount; i++)
        {
            String byteHex = hex.substring(i * 2, i * 2 + 2);

            out[i] = (uint8_t)strtoul(byteHex.c_str(), nullptr, 16);
        }

        outLen = byteCount;

        return true;
    }
}


String AesCipher::encryptToHex(
    const String& plaintext,
    const uint8_t key[32]
)
{
    size_t plainLen = plaintext.length();

    size_t paddedLen = ((plainLen / BLOCK_SIZE) + 1) * BLOCK_SIZE;

    uint8_t padValue = (uint8_t)(paddedLen - plainLen);


    uint8_t* padded = new uint8_t[paddedLen];

    memcpy(padded, plaintext.c_str(), plainLen);

    for(size_t i = plainLen; i < paddedLen; i++)
    {
        padded[i] = padValue;
    }


    uint8_t iv[BLOCK_SIZE];

    esp_fill_random(iv, BLOCK_SIZE);


    uint8_t ivWork[BLOCK_SIZE];

    memcpy(ivWork, iv, BLOCK_SIZE);


    uint8_t* cipherBuf = new uint8_t[paddedLen];


    mbedtls_aes_context aes;

    mbedtls_aes_init(&aes);

    mbedtls_aes_setkey_enc(&aes, key, 256);

    mbedtls_aes_crypt_cbc(
        &aes,
        MBEDTLS_AES_ENCRYPT,
        paddedLen,
        ivWork,
        padded,
        cipherBuf
    );

    mbedtls_aes_free(&aes);


    uint8_t* combined = new uint8_t[BLOCK_SIZE + paddedLen];

    memcpy(combined, iv, BLOCK_SIZE);

    memcpy(combined + BLOCK_SIZE, cipherBuf, paddedLen);


    String result;

    bytesToHex(combined, BLOCK_SIZE + paddedLen, result);


    delete[] padded;

    delete[] cipherBuf;

    delete[] combined;


    return result;
}


String AesCipher::decryptFromHex(
    const String& hexData,
    const uint8_t key[32],
    bool& ok
)
{
    ok = false;


    if(hexData.length() == 0)
    {
        return "";
    }


    size_t maxBytes = hexData.length() / 2;

    uint8_t* raw = new uint8_t[maxBytes > 0 ? maxBytes : 1];

    size_t rawLen = 0;


    if(!hexToBytes(hexData, raw, maxBytes, rawLen))
    {
        delete[] raw;

        return "";
    }


    if(rawLen < BLOCK_SIZE * 2 || (rawLen - BLOCK_SIZE) % BLOCK_SIZE != 0)
    {
        delete[] raw;

        return "";
    }


    uint8_t iv[BLOCK_SIZE];

    memcpy(iv, raw, BLOCK_SIZE);


    size_t cipherLen = rawLen - BLOCK_SIZE;

    uint8_t* cipherBuf = raw + BLOCK_SIZE;

    uint8_t* plainBuf = new uint8_t[cipherLen];


    mbedtls_aes_context aes;

    mbedtls_aes_init(&aes);

    mbedtls_aes_setkey_dec(&aes, key, 256);

    mbedtls_aes_crypt_cbc(
        &aes,
        MBEDTLS_AES_DECRYPT,
        cipherLen,
        iv,
        cipherBuf,
        plainBuf
    );

    mbedtls_aes_free(&aes);


    uint8_t padValue = plainBuf[cipherLen - 1];


    if(padValue == 0 || padValue > BLOCK_SIZE || padValue > cipherLen)
    {
        delete[] raw;

        delete[] plainBuf;

        return "";
    }


    for(size_t i = 0; i < padValue; i++)
    {
        if(plainBuf[cipherLen - 1 - i] != padValue)
        {
            delete[] raw;

            delete[] plainBuf;

            return "";
        }
    }


    size_t plainLen = cipherLen - padValue;


    String result;

    result.reserve(plainLen);

    for(size_t i = 0; i < plainLen; i++)
    {
        result += (char)plainBuf[i];
    }


    delete[] raw;

    delete[] plainBuf;


    ok = true;

    return result;
}