/**
 ******************************************************************************
 * @file    manchester_codec.h
 * @author  Viktor Banko S. (bankviktor14@gmail.com)
 * @date    2024-11-28
 * @brief   Header file for codec of the Manchester code.
 ******************************************************************************
 */

#ifndef MANCHESTER_CODE__H
#define MANCHESTER_CODE__H

// Public Includes ------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>

// Public Macros --------------------------------------------------------------

// Success completed
#define MANCHESTER_SUCCESS 0

// Invalid argument of the function
#define MANCHESTER_ERR_INVALID_ARGS -1

// Odd bit count in the source bit buffer
#define MANCHESTER_ERR_ODD_BIT_COUNT -2

// Not enough lenght of the destination bit buffer
#define MANCHESTER_ERR_NOT_ENOUGH_DST_BUFFER_LEN -3

// Wrong  bit combination in the source bit buffer
#define MANCHESTER_ERR_WRONG_BIT_COMBINATION -4

// Not implemented function
#define MANCHESTER_ERR_NOT_IMPLEMENTED -99

// Public Function Declarations -----------------------------------------------

/**
 * @brief Encode bytes in the source bit buffer and write encoded Manchester code bits to the destination bit buffer.
 * @param pabSrc [In] Pointer to the source bit buffer
 * @param nSrcBitCount [In] Count of bits in the source bit buffer
 * @param pabDst [Out] Pointer to the destination bit buffer for encoded bits
 * @param pnDstBitCount [Out] Pointer to count of bits in the destination bit buffer
 * @param xOutBitInverse [In] Flag indicate for inverting encoded bit before write to destination bit buffer
 * @return Error code or 0 for success. Use macros starts with MANCHESTER_SUCCESS for success and MANCHESTER_ERR_* for error codes.
 */
int16_t manchester_encode(
	const uint8_t *pabSrc,
	size_t nSrcBitCount,
	uint8_t *pabDst,
	size_t *pnDstBitCount,
	uint32_t xOutBitInverse);

/**
 * @brief Decode Manchester code in the source bit buffer and write decoded bits to the destination bit buffer.
 * @param pabSrc [In] Pointer to the source bit buffer
 * @param nSrcBitCount [In] Count of bits in the source bit buffer
 * @param pabDst [Out] Pointer to the destination bit buffer for decoded bits
 * @param pnDstBitCount [Out] Pointer to count of bits in the destination bit buffer
 * @param xOutBitInverse [In] Flag indicate for inverting decoded bit before write to destination bit buffer
 * @return Error code or 0 for success. Use macros starts with MANCHESTER_SUCCESS for success and MANCHESTER_ERR_* for error codes.
 */
int16_t manchester_decode(
	const uint8_t *pabSrc,
	size_t nSrcBitCount,
	uint8_t *pabDst,
	size_t *pnDstBitCount,
	uint32_t xOutBitInverse);

#endif

// End of file ----------------------------------------------------------------
