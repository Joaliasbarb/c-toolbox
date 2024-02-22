#include <gtest/gtest.h>
#include <limits>
#include "miscUtils.h"

TEST(BigEndianBytesToVariableTest, bigEndianBytesToUint64)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    uint64_t result = 0;

    EXPECT_TRUE(miscUtils_bigEndianBytesToUint64(buffer.data(), &result));
    EXPECT_EQ(0x0123456789ABCDEF, result);
}

TEST(BigEndianBytesToVariableTest, bigEndianBytesToUint64NullPointer)
{
    std::vector<uint8_t> buffer { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    uint64_t result = 0;

    EXPECT_FALSE(miscUtils_bigEndianBytesToUint64(NULL, NULL));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint64(NULL, &result));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint64(buffer.data(), NULL));
}

TEST(BigEndianBytesToVariableTest, bigEndianBytesToUint32)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45, 0x67 };
    uint32_t result = 0;

    EXPECT_TRUE(miscUtils_bigEndianBytesToUint32(buffer.data(), &result));
    EXPECT_EQ(0x01234567, result);
}

TEST(BigEndianBytesToVariableTest, bigEndianBytesToUint32NullPointer)
{
    std::vector<uint8_t> buffer { 0x01, 0x23, 0x45, 0x67 };
    uint32_t result = 0;

    EXPECT_FALSE(miscUtils_bigEndianBytesToUint32(NULL, NULL));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint32(NULL, &result));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint32(buffer.data(), NULL));
}

TEST(BigEndianBytesToVariableTest, bigEndianBytesToUint24)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45};
    uint32_t result = 0;

    EXPECT_TRUE(miscUtils_bigEndianBytesToUint24(buffer.data(), &result));
    EXPECT_EQ(0x012345, result);
}

TEST(BigEndianBytesToVariableTest, bigEndianBytesToUint24NullPointer)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45};
    uint32_t result = 0;

    EXPECT_FALSE(miscUtils_bigEndianBytesToUint24(NULL, NULL));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint24(NULL, &result));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint24(buffer.data(), NULL));
}

TEST(BigEndianBytesToVariableTest, bigEndianBytesToUint16)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23 };
    uint16_t result = 0;

    EXPECT_TRUE(miscUtils_bigEndianBytesToUint16(buffer.data(), &result));
    EXPECT_EQ(0x0123, result);
}

TEST(BigEndianBytesToVariableTest, bigEndianBytesToUint16NullPointer)
{
    std::vector<uint8_t> buffer { 0x01, 0x23 };
    uint16_t result = 0;

    EXPECT_FALSE(miscUtils_bigEndianBytesToUint16(NULL, NULL));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint16(NULL, &result));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint16(buffer.data(), NULL));
}

TEST(LittleEndianBytesToVariableTest, littleEndianBytesToUint64)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    uint64_t result = 0;

    EXPECT_TRUE(miscUtils_littleEndianBytesToUint64(buffer.data(), &result));
    EXPECT_EQ(0xEFCDAB8967452301, result);
}

TEST(LittleEndianBytesToVariableTest, littleEndianBytesToUint64NullPointer)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    uint64_t result = 0;

    EXPECT_FALSE(miscUtils_littleEndianBytesToUint64(NULL, NULL));
    EXPECT_FALSE(miscUtils_littleEndianBytesToUint64(NULL, &result));
    EXPECT_FALSE(miscUtils_littleEndianBytesToUint64(buffer.data(), NULL));
}

TEST(LittleEndianBytesToVariableTest, littleEndianBytesToUint32)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45, 0x67 };
    uint32_t result = 0;

    EXPECT_TRUE(miscUtils_littleEndianBytesToUint32(buffer.data(), &result));
    EXPECT_EQ(0x67452301, result);
}

TEST(LittleEndianBytesToVariableTest, littleEndianBytesToUint32NullPointer)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45, 0x67 };
    uint32_t result = 0;

    EXPECT_FALSE(miscUtils_littleEndianBytesToUint32(NULL, NULL));
    EXPECT_FALSE(miscUtils_littleEndianBytesToUint32(NULL, &result));
    EXPECT_FALSE(miscUtils_littleEndianBytesToUint32(buffer.data(), NULL));
}

TEST(LittleEndianBytesToVariableTest, littleEndianBytesToUint24)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45 };
    uint32_t result = 0;

    EXPECT_TRUE(miscUtils_littleEndianBytesToUint24(buffer.data(), &result));
    EXPECT_EQ(0x452301, result);
}

TEST(LittleEndianBytesToVariableTest, littleEndianBytesToUint24NullPointer)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45, 0x67 };
    uint32_t result = 0;

    EXPECT_FALSE(miscUtils_littleEndianBytesToUint24(NULL, NULL));
    EXPECT_FALSE(miscUtils_littleEndianBytesToUint24(NULL, &result));
    EXPECT_FALSE(miscUtils_littleEndianBytesToUint24(buffer.data(), NULL));
}

TEST(LittleEndianBytesToVariableTest, littleEndianBytesToUint16)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23 };
    uint16_t result = 0;

    EXPECT_TRUE(miscUtils_littleEndianBytesToUint16(buffer.data(), &result));
    EXPECT_EQ(0x2301, result);
}

TEST(LittleEndianBytesToVariableTest, littleEndianBytesToUint16NullPointer)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23 };
    uint16_t result = 0;

    EXPECT_FALSE(miscUtils_littleEndianBytesToUint16(NULL, NULL));
    EXPECT_FALSE(miscUtils_littleEndianBytesToUint16(NULL, &result));
    EXPECT_FALSE(miscUtils_littleEndianBytesToUint16(buffer.data(), NULL));
}

TEST(ExtendSignBitTest, extendSignBit64)
{
    int64_t value = 0x2A;
    int64_t result = 0;

    EXPECT_TRUE(miscUtils_extendSignBit64(value, 6, &result));
    EXPECT_EQ(0xFFFFFFFFFFFFFFEA, (uint64_t)result);

    EXPECT_TRUE(miscUtils_extendSignBit64(value, 7, &result));
    EXPECT_EQ(0x2A, (uint64_t)result);

    EXPECT_TRUE(miscUtils_extendSignBit64(value, 5, &result));
    EXPECT_EQ(0xA, (uint64_t)result);
}

TEST(ExtendSignBitTest, extendSignBit64InvalidInputs)
{
    int64_t value = 0;
    int64_t result = 10;

    EXPECT_FALSE(miscUtils_extendSignBit64(value, 64, &result));
    EXPECT_EQ(10, result);

    EXPECT_FALSE(miscUtils_extendSignBit64(value, 1, &result));
    EXPECT_EQ(10, result);

    EXPECT_FALSE(miscUtils_extendSignBit64(value, 5, NULL));
}

TEST(ExtendSignBitTest, extendSignBit32)
{
    int32_t value = 0x2A;
    int32_t result = 0;

    EXPECT_TRUE(miscUtils_extendSignBit32(value, 6, &result));
    EXPECT_EQ(0xFFFFFFEA, (uint32_t)result);

    EXPECT_TRUE(miscUtils_extendSignBit32(value, 7, &result));
    EXPECT_EQ(0x2A, (uint32_t)result);

    EXPECT_TRUE(miscUtils_extendSignBit32(value, 5, &result));
    EXPECT_EQ(0xA, (uint32_t)result);
}

TEST(ExtendSignBitTest, extendSignBit32InvalidInputs)
{
    int32_t value = 0;
    int32_t result = 10;

    EXPECT_FALSE(miscUtils_extendSignBit32(value, 32, &result));
    EXPECT_EQ(10, result);

    EXPECT_FALSE(miscUtils_extendSignBit32(value, 1, &result));
    EXPECT_EQ(10, result);

    EXPECT_FALSE(miscUtils_extendSignBit32(value, 5, NULL));
}

TEST(ExtendSignBitTest, extendSignBit16)
{
    int16_t value = 0x2A;
    int16_t result = 0;

    EXPECT_TRUE(miscUtils_extendSignBit16(value, 6, &result));
    EXPECT_EQ(0xFFEA, (uint16_t)result);

    EXPECT_TRUE(miscUtils_extendSignBit16(value, 7, &result));
    EXPECT_EQ(0x2A, (uint16_t)result);

    EXPECT_TRUE(miscUtils_extendSignBit16(value, 5, &result));
    EXPECT_EQ(0xA, (uint16_t)result);
}

TEST(ExtendSignBitTest, extendSignBit16InvalidInputs)
{
    int16_t value = 0;
    int16_t result = 10;

    EXPECT_FALSE(miscUtils_extendSignBit16(value, 16, &result));
    EXPECT_EQ(10, result);

    EXPECT_FALSE(miscUtils_extendSignBit16(value, 1, &result));
    EXPECT_EQ(10, result);

    EXPECT_FALSE(miscUtils_extendSignBit16(value, 5, NULL));
}

TEST(ExtendSignBitTest, extendSignBit8)
{
    int8_t value = 0x2A;
    int8_t result = 0;

    EXPECT_TRUE(miscUtils_extendSignBit8(value, 6, &result));
    EXPECT_EQ(0xEA, (uint8_t)result);

    EXPECT_TRUE(miscUtils_extendSignBit8(value, 7, &result));
    EXPECT_EQ(0x2A, (uint8_t)result);

    EXPECT_TRUE(miscUtils_extendSignBit8(value, 5, &result));
    EXPECT_EQ(0xA, (uint8_t)result);
}

TEST(ExtendSignBitTest, extendSignBit8InvalidInputs)
{
    int8_t value = 0;
    int8_t result = 10;

    EXPECT_FALSE(miscUtils_extendSignBit8(value, 8, &result));
    EXPECT_EQ(10, result);

    EXPECT_FALSE(miscUtils_extendSignBit8(value, 1, &result));
    EXPECT_EQ(10, result);

    EXPECT_FALSE(miscUtils_extendSignBit8(value, 5, NULL));
}

TEST(VariableToBigEndianBytes, uint64ToBigEndianBytes)
{
    uint64_t input = 0x0123456789ABCDEF;
    uint8_t result[8] = { 0 };
    std::vector<uint8_t> expectedResult{ 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };

    EXPECT_TRUE(miscUtils_uint64ToBigEndianBytes(input, result));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToBigEndianBytes, uint64ToBigEndianBytesNullPointer)
{
    uint64_t input = 0x0123456789ABCDEF;
    uint8_t result[8] = { 0 };
    std::vector<uint8_t> expectedResult(8, 0);

    EXPECT_FALSE(miscUtils_uint64ToBigEndianBytes(input, NULL));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToBigEndianBytes, uint32ToBigEndianBytes)
{
    uint32_t input = 0x01234567;
    uint8_t result[4] = { 0 };
    std::vector<uint8_t> expectedResult{ 0x01, 0x23, 0x45, 0x67 };

    EXPECT_TRUE(miscUtils_uint32ToBigEndianBytes(input, result));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToBigEndianBytes, uint32ToBigEndianBytesNullPointer)
{
    uint32_t input = 0x01234567;
    uint8_t result[4] = { 0 };
    std::vector<uint8_t> expectedResult(4, 0);

    EXPECT_FALSE(miscUtils_uint32ToBigEndianBytes(input, NULL));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToBigEndianBytes, uint24ToBigEndianBytes)
{
    uint32_t input = 0x012345;
    uint8_t result[3] = { 0 };
    std::vector<uint8_t> expectedResult{ 0x01, 0x23, 0x45 };

    EXPECT_TRUE(miscUtils_uint24ToBigEndianBytes(input, result));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToBigEndianBytes, uint24ToBigEndianBytesNullPointer)
{
    uint32_t input = 0x012345;
    uint8_t result[3] = { 0 };
    std::vector<uint8_t> expectedResult(3, 0);

    EXPECT_FALSE(miscUtils_uint24ToBigEndianBytes(input, NULL));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToBigEndianBytes, uint16ToBigEndianBytes)
{
    uint16_t input = 0x0123;
    uint8_t result[2] = { 0 };
    std::vector<uint8_t> expectedResult{ 0x01, 0x23 };

    EXPECT_TRUE(miscUtils_uint16ToBigEndianBytes(input, result));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToBigEndianBytes, uint16ToBigEndianBytesNullPointer)
{
    uint16_t input = 0x0123;
    uint8_t result[2] = { 0 };
    std::vector<uint8_t> expectedResult(2, 0);

    EXPECT_FALSE(miscUtils_uint16ToBigEndianBytes(input, NULL));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToLittleEndianBytes, uint64ToLittleEndianBytes)
{
    uint64_t input = 0x0123456789ABCDEF;
    uint8_t result[8] = { 0 };
    std::vector<uint8_t> expectedResult{ 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };

    EXPECT_TRUE(miscUtils_uint64ToLittleEndianBytes(input, result));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToLittleEndianBytes, uint64ToLittleEndianBytesNullPointer)
{
    uint64_t input = 0x0123456789ABCDEF;
    uint8_t result[8] = { 0 };
    std::vector<uint8_t> expectedResult(8, 0);

    EXPECT_FALSE(miscUtils_uint64ToLittleEndianBytes(input, NULL));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToLittleEndianBytes, uint32ToLittleEndianBytes)
{
    uint32_t input = 0x01234567;
    uint8_t result[4] = { 0 };
    std::vector<uint8_t> expectedResult{ 0x67, 0x45, 0x23, 0x01 };

    EXPECT_TRUE(miscUtils_uint32ToLittleEndianBytes(input, result));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToLittleEndianBytes, uint32ToLittleEndianBytesNullPointer)
{
    uint32_t input = 0x01234567;
    uint8_t result[4] = { 0 };
    std::vector<uint8_t> expectedResult(4, 0);

    EXPECT_FALSE(miscUtils_uint32ToLittleEndianBytes(input, NULL));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToLittleEndianBytes, uint24ToLittleEndianBytes)
{
    uint32_t input = 0x012345;
    uint8_t result[3] = { 0 };
    std::vector<uint8_t> expectedResult{ 0x45, 0x23, 0x01 };

    EXPECT_TRUE(miscUtils_uint24ToLittleEndianBytes(input, result));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToLittleEndianBytes, uint24ToLittleEndianBytesNullPointer)
{
    uint32_t input = 0x012345;
    uint8_t result[3] = { 0 };
    std::vector<uint8_t> expectedResult(3, 0);

    EXPECT_FALSE(miscUtils_uint24ToLittleEndianBytes(input, NULL));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToLittleEndianBytes, uint16ToLittleEndianBytes)
{
    uint16_t input = 0x0123;
    uint8_t result[2] = { 0 };
    std::vector<uint8_t> expectedResult{ 0x23, 0x01 };

    EXPECT_TRUE(miscUtils_uint16ToLittleEndianBytes(input, result));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(VariableToLittleEndianBytes, uint16ToLittleEndianBytesNullPointer)
{
    uint16_t input = 0x0123;
    uint8_t result[2] = { 0 };
    std::vector<uint8_t> expectedResult(2, 0);

    EXPECT_FALSE(miscUtils_uint16ToLittleEndianBytes(input, NULL));
    EXPECT_EQ(0, memcmp(expectedResult.data(), result, expectedResult.size()));
}

TEST(IsValueInRangeTest, isValueInRange)
{
    EXPECT_FALSE(miscUtils_isValueInRange(0, 1, 5));
    EXPECT_TRUE(miscUtils_isValueInRange(1, 1, 5));
    EXPECT_TRUE(miscUtils_isValueInRange(5, 1, 5));
    EXPECT_FALSE(miscUtils_isValueInRange(6, 1, 5));
}

TEST(MinMaxMacrosTest, max)
{
    EXPECT_EQ(50, MISC_UTILS_MAX(5, 50));
    EXPECT_EQ(45.2, MISC_UTILS_MAX(5, 45.2));
    EXPECT_EQ(80.6, MISC_UTILS_MAX(5, 80.6));
    EXPECT_EQ(50, MISC_UTILS_MAX(50, 5));
    EXPECT_EQ(50, MISC_UTILS_MAX(45.2, 50));
    EXPECT_EQ(80.6, MISC_UTILS_MAX(45.2, 80.6));
    EXPECT_EQ(80.6, MISC_UTILS_MAX(80.6, 45.2));
}

TEST(MinMaxMacrosTest, min)
{
    EXPECT_EQ(5, MISC_UTILS_MIN(5, 50));
    EXPECT_EQ(5, MISC_UTILS_MIN(5, 45.2));
    EXPECT_EQ(5, MISC_UTILS_MIN(5, 80.6));
    EXPECT_EQ(5, MISC_UTILS_MIN(50, 5));
    EXPECT_EQ(45.2, MISC_UTILS_MIN(45.2, 50));
    EXPECT_EQ(45.2, MISC_UTILS_MIN(45.2, 80.6));
    EXPECT_EQ(45.2, MISC_UTILS_MIN(80.6, 45.2));
}

TEST(IsPowerOf2Test, isPowerOf2)
{
    EXPECT_FALSE(miscUtils_isPowerOf2(0));
    EXPECT_TRUE(miscUtils_isPowerOf2(1));
    EXPECT_TRUE(miscUtils_isPowerOf2(2));
    EXPECT_FALSE(miscUtils_isPowerOf2(3));
}