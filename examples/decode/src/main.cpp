#include <Arduino.h>
#include <manchester_codec.h>
#include <math.h>

constexpr uint32_t UART_BAUDRATE = 115200;

#define countof(v) (sizeof(v) / sizeof(v[0]))
#define FALSE 0
#define TRUE 1

const size_t nEncodedBitCount = 46 * 4;

// Encoded: 699995A99695959A9655996655569A6A6A5655AAAA6A55
const uint8_t abEncoded[] = {0x69, 0x99, 0x95, 0xA9, 0x96, 0x95, 0x95, 0x9A, 0x96, 0x55, 0x99, 0x66, 0x55, 0x56, 0x9A, 0x6A, 0x6A, 0x56, 0x55, 0xAA, 0xAA, 0x6A, 0x55};

// Decoded: 6A8E988B90A501B7710FF700
const uint8_t abDecoded[] = {0x6a, 0x8e, 0x98, 0x8b, 0x90, 0xa5, 0x01, 0xb7, 0x71, 0x0f, 0xf7, 0x00};

// Decoded: 957167746F5AFE488EF008F0 (inversed)
const uint8_t abDecodedInversed[] = {0x95, 0x71, 0x67, 0x74, 0x6f, 0x5a, 0xfe, 0x48, 0x8e, 0xf0, 0x08, 0xf0};

void setup()
{
    Serial.begin(UART_BAUDRATE);
    Serial.println();

    Serial.print("Encoded (S): ");
    size_t nSrcBytes = (size_t)ceil(nEncodedBitCount / 8.0);
    for (size_t i = 0; i < nSrcBytes; i++)
    {
        Serial.printf("%02X", abEncoded[i]);
    }
    Serial.println();

    Serial.println("Decoded (T): 6A8E988B90A501B7710FF700");

    Serial.print("Decoded:     ");
    uint8_t abDst[32] = {0};
    size_t nDstBitCount = 32 * 8;
    int16_t wState = manchester_decode(abEncoded, nEncodedBitCount, abDst, &nDstBitCount, FALSE);
    if (wState == MANCHESTER_SUCCESS)
    {
        size_t nDstBytes = (size_t)ceil(nDstBitCount / 8.0);
        for (size_t i = 0; i < nDstBytes; i++)
        {
            Serial.printf("%02X", abDst[i]);
        }
    }
    else
    {
        Serial.print("error, code ");
        Serial.print(wState);
    }

    // Check matching
    uint8_t xMatch = 1;
    for (size_t i = 0; i < countof(abDecoded); i++)
    {
        if (abDecoded[i] != abDst[i])
        {
            xMatch = 0;
            break;
        }
    }
    Serial.println(xMatch ? " MATCH" : " NOT MATCH");

    // -----------------------------------------------------------
    Serial.println("Inversed");

    Serial.println("Decoded (T): 957167746F5AFE488EF008F0");

    Serial.print("Decoded:     ");
    nDstBitCount = 32 * 8;
    wState = manchester_decode(abEncoded, nEncodedBitCount, abDst, &nDstBitCount, TRUE);
    if (wState == MANCHESTER_SUCCESS)
    {
        size_t nDstBytes = (size_t)ceil(nDstBitCount / 8.0);
        for (size_t i = 0; i < nDstBytes; i++)
        {
            Serial.printf("%02X", abDst[i]);
        }
    }
    else
    {
        Serial.print("error, code ");
        Serial.print(wState);
    }

    // Check matching
    xMatch = 1;
    for (size_t i = 0; i < countof(abDecodedInversed); i++)
    {
        if (abDecodedInversed[i] != abDst[i])
        {
            xMatch = 0;
            break;
        }
    }
    Serial.println(xMatch ? " MATCH" : " NOT MATCH");
}

void loop() {}
