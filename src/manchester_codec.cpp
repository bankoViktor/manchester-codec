/**
 ******************************************************************************
 * @file    manchester_codec.cpp
 * @author  Viktor Banko S. (bankviktor14@gmail.com)
 * @date    2024-11-28
 * @brief   Source file for codec of the Manchester code.
 ******************************************************************************
 */

// Private Includes -----------------------------------------------------------

#include "manchester_codec.h"
#include <math.h>

// Public Function Definitions ------------------------------------------------

int16_t manchester_encode(
    const uint8_t *pabSrc,
    size_t nSrcBitCount,
    uint8_t *pabDst,
    size_t *pnDstBitCount,
    uint32_t xOutBitInverse)
{
    if (pabSrc == 0 || nSrcBitCount < 1 || pabDst == 0)
    {
        return MANCHESTER_ERR_INVALID_ARGS;
    }

    if (pabSrc == pabDst)
    {
        return MANCHESTER_ERR_SRC_AND_DST_SAME;
    }

    size_t nDstBytesMin = (size_t)ceil((nSrcBitCount * 2) / 8.0);
    size_t nDstBytes = (size_t)ceil(*pnDstBitCount / 8.0);
    if (nDstBytes < nDstBytesMin)
    {
        return MANCHESTER_ERR_NOT_ENOUGH_DST_BUFFER_LEN;
    }

    size_t nDstByteIndex = 0;
    size_t bDstBitInByteIndex = 0;
    for (size_t nSrcBitIndex = 0; nSrcBitIndex < nSrcBitCount; nSrcBitIndex++)
    {
        size_t nSrcByteIndex = nSrcBitIndex / 8;
        uint8_t nSrcBitInByteIndex = 7 - (nSrcBitIndex - nSrcByteIndex * 8);
        uint8_t bSrcByte = pabSrc[nSrcByteIndex];

        // Clear bits
        pabDst[nDstByteIndex] &= ~(0b11 << (6 - bDstBitInByteIndex));

        // Set bits
        uint8_t bSrcBit = (bSrcByte >> nSrcBitInByteIndex) & 0b1;
        switch (bSrcBit)
        {
        case 0b0:
            if (xOutBitInverse)
            {
                pabDst[nDstByteIndex] |= (0b10 << (6 - bDstBitInByteIndex));
            }
            else
            {
                pabDst[nDstByteIndex] |= (0b01 << (6 - bDstBitInByteIndex));
            }
            break;

        case 0b1:
            if (xOutBitInverse)
            {
                pabDst[nDstByteIndex] |= (0b01 << (6 - bDstBitInByteIndex));
            }
            else
            {
                pabDst[nDstByteIndex] |= (0b10 << (6 - bDstBitInByteIndex));
            }
            break;

        default:
            return MANCHESTER_ERR_WRONG_BIT_COMBINATION;
        }

        bDstBitInByteIndex += 2;
        if (bDstBitInByteIndex >= 8)
        {
            nDstByteIndex++;
            bDstBitInByteIndex = 0;
        }
    }

    *pnDstBitCount = nDstByteIndex * 8 + bDstBitInByteIndex;
    return MANCHESTER_SUCCESS;
}

int16_t manchester_decode(
    const uint8_t *pabSrc,
    size_t nSrcBitCount,
    uint8_t *pabDst,
    size_t *pnDstBitCount,
    uint32_t xOutBitInverse)
{
    if (pabSrc == 0 || nSrcBitCount < 2 || pabDst == 0)
    {
        return MANCHESTER_ERR_INVALID_ARGS;
    }

    if (nSrcBitCount % 2 != 0)
    {
        return MANCHESTER_ERR_ODD_BIT_COUNT;
    }

    size_t nDstBytesMin = (size_t)ceil((nSrcBitCount / 2) / 8.0);
    size_t nDstBytes = (size_t)ceil(*pnDstBitCount / 8.0);
    if (nDstBytes < nDstBytesMin)
    {
        return MANCHESTER_ERR_NOT_ENOUGH_DST_BUFFER_LEN;
    }

    size_t nDstByteIndex = 0;
    size_t bDstBitInByteIndex = 0;
    for (size_t nSrcBitIndex = 0; nSrcBitIndex < nSrcBitCount; nSrcBitIndex += 2)
    {
        size_t nSrcByteIndex = nSrcBitIndex / 8;
        uint8_t bSrcByte = pabSrc[nSrcByteIndex];
        uint8_t bMask = (1 << (7 - bDstBitInByteIndex));

        // Clear bit
        pabDst[nDstByteIndex] &= ~bMask;

        // Set bit
        uint8_t bSrcBitInByteIndex = 8 - nSrcBitIndex + nSrcByteIndex * 8 - 2;
        uint8_t bSrcBits = (bSrcByte >> bSrcBitInByteIndex) & 0b11;
        switch (bSrcBits)
        {
        case 0b01:
            if (xOutBitInverse)
            {
                pabDst[nDstByteIndex] |= bMask;
            }
            break;

        case 0b10:
            if (!xOutBitInverse)
            {
                pabDst[nDstByteIndex] |= bMask;
            }
            break;

        default:
            return MANCHESTER_ERR_WRONG_BIT_COMBINATION;
        }

        bDstBitInByteIndex++;
        if (bDstBitInByteIndex >= 8)
        {
            nDstByteIndex++;
            bDstBitInByteIndex = 0;
        }
    }

    *pnDstBitCount = nDstByteIndex * 8 + bDstBitInByteIndex;
    return MANCHESTER_SUCCESS;
}

// End of file ----------------------------------------------------------------
