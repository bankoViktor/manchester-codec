#include <unity.h>
#include <manchester_codec.h>
#include "../data.h"

void not_implemented()
{
	uint8_t abDst[32] = {};
	size_t nDstBitCount = 256;
	int16_t wState;

	wState = manchester_encode(abSrcRight, nSrcBitCountRight, abDst, &nDstBitCount, 0);
	TEST_ASSERT_EQUAL_INT16(MANCHESTER_ERR_NOT_IMPLEMENTED, wState);
}

void setUp() {}

void tearDown() {}

int main(int argc, char **argv)
{
	UNITY_BEGIN();

	RUN_TEST(not_implemented);

	UNITY_END();
}
