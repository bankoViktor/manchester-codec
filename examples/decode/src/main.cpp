#include <Arduino.h>
#include <manchester_codec.h>
#include <math.h>

constexpr uint32_t UART_BAUDRATE = 115200;

// Encoded: 699995A99695959A9655996655569A6A6A5655AAAA6A55
const uint8_t abSrc[] = {0x69, 0x99, 0x95, 0xa9, 0x96, 0x95, 0x95, 0x9a, 0x96, 0x55, 0x99, 0x66, 0x55, 0x56, 0x9a, 0x6a, 0x6a, 0x56, 0x55, 0xaa, 0xaa, 0x6a, 0x55};
const size_t nSrcBitCount = 46 * 4;

void setup()
{
    Serial.begin(UART_BAUDRATE);
    Serial.println();

    Serial.print("Source:  ");
    size_t nSrcBytes = (size_t)ceil(nSrcBitCount / 8.0);
    for (size_t i = 0; i < nSrcBytes; i++)
    {
        Serial.printf("%02X", abSrc[i]);
    }
    Serial.println();

    Serial.print("Decoded: ");
    uint8_t abDst[32] = { 0 };
    size_t nDstBitCount = 32 * 8;
    int16_t wState = manchester_decode(abSrc, nSrcBitCount, abDst, &nDstBitCount, 0);
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
    Serial.println();
    Serial.print("TARGET:  6A8E988B90A501B7710FF70_");
}

void loop() {}
