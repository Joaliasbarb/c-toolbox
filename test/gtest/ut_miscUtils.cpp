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

TEST(SignExtendTest, Extend16)
{
    int16_t value = 0x02AB;
    int16_t result = 0;

    EXPECT_TRUE(miscUtils_extendSignBit16(value, 10, &result));
    EXPECT_EQ(0xFEAB, (uint16_t) result);
}