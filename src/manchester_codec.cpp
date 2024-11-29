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
	return MANCHESTER_ERR_NOT_IMPLEMENTED;
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
	size_t bDstBitIndexInByte = 0;
	for (size_t nSrcBitIndex = 0; nSrcBitIndex < nSrcBitCount; nSrcBitIndex += 2)
	{
		size_t nSrcByteIndex = nSrcBitIndex / 8;
		uint8_t bSrcByte = pabSrc[nSrcByteIndex];

		uint8_t bSrcBitIndexInByte = 8 - nSrcBitIndex + nSrcByteIndex * 8 - 2;
		uint8_t bSrcBits = (bSrcByte >> bSrcBitIndexInByte) & 0b11;

		switch (bSrcBits)
		{
		case 0b01:
			if (xOutBitInverse)
			{
				pabDst[nDstByteIndex] |= (1 << (7 - bDstBitIndexInByte));
			}
			break;

		case 0b10:
			if (!xOutBitInverse)
			{
				pabDst[nDstByteIndex] |= (1 << (7 - bDstBitIndexInByte));
			}
			break;

		default:
			return MANCHESTER_ERR_WRONG_BIT_COMBINATION;
		}

		bDstBitIndexInByte++;
		if (bDstBitIndexInByte >= 8)
		{
			nDstByteIndex++;
			bDstBitIndexInByte = 0;
		}
	}

	*pnDstBitCount = nDstByteIndex * 8 + bDstBitIndexInByte;
	return MANCHESTER_SUCCESS;
}

// End of file ----------------------------------------------------------------
