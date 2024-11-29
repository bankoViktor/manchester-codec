#include <unity.h>
#include <manchester_codec.h>
#include "../data.h"
#include <memory.h>

void args_src_buffer_ptr_null()
{
	uint8_t abDst[32] = {};
	size_t nDstBitCount = 256;
	int16_t wState;

	wState = manchester_decode(0, nSrcBitCountRight, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_INVALID_ARGS, wState, "Null pointer to Src bit buffer.");
}

void args_src_buffer_len()
{
	uint8_t abDst[32] = {};
	size_t nDstBitCount;
	int16_t wState;

	nDstBitCount = 256;
	wState = manchester_decode(abSrcRight, 0, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_INVALID_ARGS, wState, "Zero length of Src bit buffer.");

	nDstBitCount = 256;
	wState = manchester_decode(abSrcRight, 2, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Min length of Src bit buffer.");

	nDstBitCount = 256;
	wState = manchester_decode(abSrcRight, nSrcBitCountRight, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Positive length of Src bit buffer.");
}

void args_src_buffer_len_odd()
{
	uint8_t abDst[32] = {};
	size_t nDstBitCount = 256;
	int16_t wState;

	wState = manchester_decode(abSrcRight, 13, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_ODD_BIT_COUNT, wState, "Odd length of Src bit buffer.");
}

void args_src_buffer_wrong_bit_combination_00()
{
	uint8_t abSrc[128] = {};
	size_t nSrcBytes = (size_t)ceil(nSrcBitCountRight / 8.0);
	uint8_t abDst[32] = {};
	size_t nDstBitCount = 256;
	int16_t wState;

	memcpy(abSrc, abDstRight, nSrcBytes);
	abSrc[3] |= 0x00;
	wState = manchester_decode(abSrc, nSrcBitCountRight, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_WRONG_BIT_COMBINATION, wState, "Wrong combination 0b00.");
}

void args_src_buffer_wrong_bit_combination_11()
{
	uint8_t abSrc[128] = {};
	size_t nSrcBytes = (size_t)ceil(nSrcBitCountRight / 8.0);
	uint8_t abDst[32] = {};
	size_t nDstBitCount = 256;
	int16_t wState;

	memcpy(abSrc, abDstRight, nSrcBytes);
	abSrc[3] |= 0x03;
	wState = manchester_decode(abSrc, nSrcBitCountRight, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_WRONG_BIT_COMBINATION, wState, "Wrong combination 0b11.");
}

void args_dst_buffer_ptr_null()
{
	uint8_t abDst[32] = {};
	size_t nDstBitCount = 256;
	int16_t wState;

	wState = manchester_decode(abSrcRight, nSrcBitCountRight, 0, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_INVALID_ARGS, wState, "Null pointer to Dst bit buffer.");
}

void args_dst_buffer_len_more_than_src_buffer_len()
{
	uint8_t abDst[32] = {};
	size_t nDstBitCount;
	int16_t wState;

	nDstBitCount = 50;
	wState = manchester_decode(abSrcRight, nSrcBitCountRight, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_NOT_ENOUGH_DST_BUFFER_LEN, wState, "Dst bit buffer len less than needed.");

	nDstBitCount = 500;
	wState = manchester_decode(abSrcRight, nSrcBitCountRight, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Dst bit buffer len enough.");
}

void correct_result()
{
	uint8_t abDst[32] = {};
	size_t nDstBitCount = 256;
	int16_t wState;

	wState = manchester_decode(abSrcRight, nSrcBitCountRight, abDst, &nDstBitCount, 0);

	// Check state value
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Decode failed.");

	// Check decoded bit count equals
	TEST_ASSERT_EQUAL_size_t_MESSAGE(nSrcBitCountRight / 2, nDstBitCount, "Dst bit buffer length not expected.");

	// Check decoded buffer equals
	size_t nDstBytes = (size_t)ceil(nDstBitCountRight / 8.0);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(abDstRight, abDst, nDstBytes, "Src & Dst bit buffer mismatch.");
}

void correct_result_inverse()
{
	uint8_t abDst[32] = {};
	size_t nDstBitCount = 256;
	int16_t wState;

	wState = manchester_decode(abSrcRight, nSrcBitCountRight, abDst, &nDstBitCount, 1);

	// Check state value
	TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Decode failed.");

	// Check decoded bit count equals
	TEST_ASSERT_EQUAL_size_t_MESSAGE(nSrcBitCountRight / 2, nDstBitCount, "Dst bit buffer length not expected.");

	// Check decoded buffer equals
	size_t nDstBytes = (size_t)ceil(nDstBitCountRight / 8.0);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(abDstRightInversed, abDst, nDstBytes, "Src & Dst bit buffer mismatch.");
}

void setUp() {}

void tearDown() {}

int main(int argc, char **argv)
{
	UNITY_BEGIN();

	RUN_TEST(args_src_buffer_ptr_null);
	RUN_TEST(args_src_buffer_len);
	RUN_TEST(args_src_buffer_len_odd);
	RUN_TEST(args_src_buffer_wrong_bit_combination_00);
	RUN_TEST(args_src_buffer_wrong_bit_combination_11);
	RUN_TEST(args_dst_buffer_ptr_null);
	RUN_TEST(args_dst_buffer_len_more_than_src_buffer_len);
	RUN_TEST(correct_result);
	RUN_TEST(correct_result_inverse);

	UNITY_END();
}
