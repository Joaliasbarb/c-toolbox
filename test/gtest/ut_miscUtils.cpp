#include <gtest/gtest.h>
#include "miscUtils.h"

TEST(BigEndianBytesToVariableTest, ToUint64)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    uint64_t result = 0;

    EXPECT_TRUE(miscUtils_bigEndianBytesToUint64(buffer.data(), &result));
    EXPECT_EQ(0x0123456789ABCDEF, result);
}

TEST(BigEndianBytesToVariableTest, ToUint64NullPointer)
{
    std::vector<uint8_t> buffer { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    uint64_t result = 0;

    EXPECT_FALSE(miscUtils_bigEndianBytesToUint64(NULL, NULL));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint64(NULL, &result));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint64(buffer.data(), NULL));
}

TEST(BigEndianBytesToVariableTest, ToUint32)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45, 0x67 };
    uint32_t result = 0;

    EXPECT_TRUE(miscUtils_bigEndianBytesToUint32(buffer.data(), &result));
    EXPECT_EQ(0x01234567, result);
}

TEST(BigEndianBytesToVariableTest, ToUint32NullPointer)
{
    std::vector<uint8_t> buffer { 0x01, 0x23, 0x45, 0x67 };
    uint32_t result = 0;

    EXPECT_FALSE(miscUtils_bigEndianBytesToUint32(NULL, NULL));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint32(NULL, &result));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint32(buffer.data(), NULL));
}

TEST(BigEndianBytesToVariableTest, ToUint24)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45};
    uint32_t result = 0;

    EXPECT_TRUE(miscUtils_bigEndianBytesToUint24(buffer.data(), &result));
    EXPECT_EQ(0x012345, result);
}

TEST(BigEndianBytesToVariableTest, ToUint24NullPointer)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23, 0x45};
    uint32_t result = 0;

    EXPECT_FALSE(miscUtils_bigEndianBytesToUint24(NULL, NULL));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint24(NULL, &result));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint24(buffer.data(), NULL));
}

TEST(BigEndianBytesToVariableTest, ToUint16)
{
    std::vector<uint8_t> buffer{ 0x01, 0x23 };
    uint16_t result = 0;

    EXPECT_TRUE(miscUtils_bigEndianBytesToUint16(buffer.data(), &result));
    EXPECT_EQ(0x0123, result);
}

TEST(BigEndianBytesToVariableTest, ToUint16NullPointer)
{
    std::vector<uint8_t> buffer { 0x01, 0x23 };
    uint16_t result = 0;

    EXPECT_FALSE(miscUtils_bigEndianBytesToUint16(NULL, NULL));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint16(NULL, &result));
    EXPECT_FALSE(miscUtils_bigEndianBytesToUint16(buffer.data(), NULL));
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