#include <unity.h>
#include <manchester_codec.h>
#include "../data.h"

void args_src_buffer_ptr_null()
{
    uint8_t abDst[32] = {};
    size_t nDstBitCount = 256;
    int16_t wState;

    wState = manchester_encode(0, nDecodedBitCountRight, abDst, &nDstBitCount, 0);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_INVALID_ARGS, wState, "Null pointer to Src bit buffer.");
}

void args_src_buffer_len()
{
    uint8_t abDst[32] = {};
    size_t nDstBitCount;
    int16_t wState;

    nDstBitCount = 256;
    wState = manchester_encode(abDecodedRight, 0, abDst, &nDstBitCount, 0);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_INVALID_ARGS, wState, "Zero length of Src bit buffer.");

    nDstBitCount = 256;
    wState = manchester_encode(abDecodedRight, 1, abDst, &nDstBitCount, 0);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Min length of Src bit buffer.");

    nDstBitCount = 256;
    wState = manchester_encode(abDecodedRight, nDecodedBitCountRight, abDst, &nDstBitCount, 0);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Positive length of Src bit buffer.");
}

void args_src_and_dst_buffer_same()
{
    uint8_t abDst[32] = {};
    size_t nDstBitCount = 256;
    int16_t wState;

    wState = manchester_encode(abDecodedRight, nDecodedBitCountRight, (uint8_t *)abDecodedRight, &nDstBitCount, 0);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_SRC_AND_DST_SAME, wState, "The pointer to Src and Dst match.");
}

void args_dst_buffer_ptr_null()
{
    uint8_t abDst[32] = {};
    size_t nDstBitCount = 256;
    int16_t wState;

    wState = manchester_encode(abDecodedRight, nDecodedBitCountRight, 0, &nDstBitCount, 0);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_INVALID_ARGS, wState, "Null pointer to Dst bit buffer.");
}

void args_dst_buffer_len_more_than_src_buffer_len()
{
    uint8_t abDst[32] = {};
    size_t nDstBitCount;
    int16_t wState;

    nDstBitCount = nEncodedBitCountRight - 10;
    wState = manchester_encode(abDecodedRight, nDecodedBitCountRight, abDst, &nDstBitCount, 0);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_ERR_NOT_ENOUGH_DST_BUFFER_LEN, wState, "Dst bit buffer len less than needed.");

    nDstBitCount = 500;
    wState = manchester_encode(abDecodedRight, nDecodedBitCountRight, abDst, &nDstBitCount, 0);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Dst bit buffer len enough.");
}

void correct_result()
{
    uint8_t abDst[32] = {};
    size_t nDstBitCount = 256;
    int16_t wState;

    wState = manchester_encode(abDecodedRight, nDecodedBitCountRight, abDst, &nDstBitCount, 0);

    // Check state value
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Encode failed.");

    // Check encoded bit count equals
    TEST_ASSERT_EQUAL_size_t_MESSAGE(nDecodedBitCountRight * 2, nDstBitCount, "Dst bit buffer length not expected.");

    // Check encoded buffer equals
    size_t nDstBytes = (size_t)ceil(nEncodedBitCountRight / 8.0);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(abEncodedRight, abDst, nDstBytes, "Dst bit buffer not correct.");
}

void correct_result_inverse()
{
    uint8_t abDst[32] = {};
    size_t nDstBitCount = 256;
    int16_t wState;

    wState = manchester_encode(abDecodedRightInversed, nDecodedBitCountRight, abDst, &nDstBitCount, 1);

    // Check state value
    TEST_ASSERT_EQUAL_INT16_MESSAGE(MANCHESTER_SUCCESS, wState, "Encode failed.");

    // Check encoded bit count equals
    TEST_ASSERT_EQUAL_size_t_MESSAGE(nDecodedBitCountRight * 2, nDstBitCount, "Dst bit buffer length not expected.");

    // Check encoded buffer equals
    size_t nDstBytes = (size_t)ceil(nEncodedBitCountRight / 8.0);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(abEncodedRight, abDst, nDstBytes, "Dst bit buffer not correct.");
}

void setUp() {}

void tearDown() {}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(args_src_buffer_ptr_null);
    RUN_TEST(args_src_buffer_len);
    RUN_TEST(args_src_and_dst_buffer_same);
    RUN_TEST(args_dst_buffer_ptr_null);
    RUN_TEST(args_dst_buffer_len_more_than_src_buffer_len);
    RUN_TEST(correct_result);
    RUN_TEST(correct_result_inverse);

    UNITY_END();
}
