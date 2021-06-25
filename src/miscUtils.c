#include "miscUtils.h"

/*************************************************************************
 ********************* Local Type/Constant definitions *******************
 ************************************************************************/

/*************************************************************************
 *********************** Local variables declarations ********************
 ************************************************************************/

/*************************************************************************
 *********************** Local function declarations *********************
 ************************************************************************/

/*************************************************************************
 *********************** Public function definitions *********************
 ************************************************************************/
bool miscUtils_bigEndianBytesToUint64(const uint8_t* const bytes, uint64_t* const resultPtr)
{
    // Sanity check
    if((NULL == bytes) || (NULL == resultPtr))
    {
        return false;
    }

    *resultPtr = ((uint64_t) bytes[0] << 56) | ((uint64_t) bytes[1] << 48) | 
                ((uint64_t) bytes[2] << 40) | ((uint64_t) bytes[3] << 32) |
                ((uint64_t) bytes[4] << 24) | ((uint64_t) bytes[5] << 16) | 
                ((uint64_t) bytes[6] << 8) | bytes[7];
    return true;
}

bool miscUtils_bigEndianBytesToUint32(const uint8_t* const bytes, uint32_t* const resultPtr)
{
    // Sanity check
    if((NULL == bytes) || (NULL == resultPtr))
    {
        return false;
    }

    *resultPtr = ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) | ((uint32_t)bytes[2] << 8) | bytes[3];
    return true;
}

bool miscUtils_bigEndianBytesToUint24(const uint8_t* const bytes, uint32_t* const resultPtr)
{
    // Sanity check
    if((NULL == bytes) || (NULL == resultPtr))
    {
        return false;
    }

    *resultPtr = ((uint32_t)bytes[0] << 16) | ((uint32_t)bytes[1] << 8) | bytes[2];
    return true;
}

bool miscUtils_bigEndianBytesToUint16(const uint8_t* const bytes, uint16_t* const resultPtr)
{
    // Sanity check
    if((NULL == bytes) || (NULL == resultPtr))
    {
        return false;
    }

    *resultPtr = ((uint16_t)bytes[0] << 8) | bytes[1];
    return true;
}

bool miscUtils_littleEndianBytesToUint64(const uint8_t* const bytes, uint64_t* const resultPtr)
{
    // Sanity check
    if((NULL == bytes) || (NULL == resultPtr))
    {
        return false;
    }

    *resultPtr = ((uint64_t)bytes[7] << 56) | ((uint64_t)bytes[6] << 48) |
        ((uint64_t)bytes[5] << 40) | ((uint64_t)bytes[4] << 32) |
        ((uint64_t)bytes[3] << 24) | ((uint64_t)bytes[2] << 16) |
        ((uint64_t)bytes[1] << 8) | bytes[0];
    return true;
}

bool miscUtils_littleEndianBytesToUint32(const uint8_t* const bytes, uint32_t* const resultPtr)
{
    // Sanity check
    if((NULL == bytes) || (NULL == resultPtr))
    {
        return false;
    }

    *resultPtr = ((uint32_t)bytes[3] << 24) | ((uint32_t)bytes[2] << 16) | ((uint32_t)bytes[1] << 8) | bytes[0];
    return true;
}

bool miscUtils_littleEndianBytesToUint24(const uint8_t* const bytes, uint32_t* const resultPtr)
{
    // Sanity check
    if((NULL == bytes) || (NULL == resultPtr))
    {
        return false;
    }

    *resultPtr = ((uint32_t)bytes[2] << 16) | ((uint32_t)bytes[1] << 8) | bytes[0];
    return true;
}

bool miscUtils_littleEndianBytesToUint16(const uint8_t* const bytes, uint16_t* const resultPtr)
{
    // Sanity check
    if((NULL == bytes) || (NULL == resultPtr))
    {
        return false;
    }

    *resultPtr = ((uint16_t)bytes[1] << 8) | bytes[0];
    return true;
}

bool miscUtils_extendSignBit64(int64_t value, uint8_t valueWidth, int64_t* const resultPtr)
{
    int64_t mask = 0;

    // Sanity check
    if((NULL == resultPtr) || (2 > valueWidth) || (63 < valueWidth))
    {
        return false;
    }

    mask = 1ULL << (valueWidth - 1);
    value = value & ((1ULL << valueWidth) - 1);
    *resultPtr = (value ^ mask) - mask;
    return true;
}

bool miscUtils_extendSignBit32(int32_t value, uint8_t valueWidth, int32_t* const resultPtr)
{
    int32_t mask = 0;

    // Sanity check
    if((NULL == resultPtr) || (2 > valueWidth) || (31 < valueWidth))
    {
        return false;
    }

    mask = 1UL << (valueWidth - 1);
    value = value & ((1UL << valueWidth) - 1);
    *resultPtr = (value ^ mask) - mask;
    return true;
}

bool miscUtils_extendSignBit16(int16_t value, uint8_t valueWidth, int16_t* const resultPtr)
{
    int16_t mask = 0;

    // Sanity check
    if((NULL == resultPtr) || (2 > valueWidth) || (15 < valueWidth))
    {
        return false;
    }

    mask = 1U << (valueWidth - 1);
    value = value & ((1U << valueWidth) - 1);
    *resultPtr = (value ^ mask) - mask;
    return true;
}

bool miscUtils_extendSignBit8(int8_t value, uint8_t valueWidth, int8_t* const resultPtr)
{
    int8_t mask = 0;

    // Sanity check
    if((NULL == resultPtr) || (2 > valueWidth) || (7 < valueWidth))
    {
        return false;
    }

    mask = 1U << (valueWidth - 1);
    value = value & ((1U << valueWidth) - 1);
    *resultPtr = (value ^ mask) - mask;
    return true;
}

bool miscUtils_uint64ToBigEndianBytes(uint64_t value, uint8_t* const bytes)
{
    // Sanity check
    if(NULL == bytes)
    {
        return false;
    }

    bytes[7] = value & 0xFF;
    bytes[6] = (value >> 8) & 0xFF;
    bytes[5] = (value >> 16) & 0xFF;
    bytes[4] = (value >> 24) & 0xFF;
    bytes[3] = (value >> 32) & 0xFF;
    bytes[2] = (value >> 40) & 0xFF;
    bytes[1] = (value >> 48) & 0xFF;
    bytes[0] = (value >> 56) & 0xFF;
    return true;
}

bool miscUtils_uint32ToBigEndianBytes(uint32_t value, uint8_t* const bytes)
{
    // Sanity check
    if(NULL == bytes)
    {
        return false;
    }

    bytes[3] = value & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[0] = (value >> 24) & 0xFF;
    return true;
}

bool miscUtils_uint24ToBigEndianBytes(uint32_t value, uint8_t* const bytes)
{
    // Sanity check
    if(NULL == bytes)
    {
        return false;
    }

    bytes[2] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[0] = (value >> 16) & 0xFF;
    return true;
}

bool miscUtils_uint16ToBigEndianBytes(uint16_t value, uint8_t* const bytes)
{
    // Sanity check
    if(NULL == bytes)
    {
        return false;
    }

    bytes[1] = value & 0xFF;
    bytes[0] = (value >> 8) & 0xFF;
    return true;
}

bool miscUtils_uint64ToLittleEndianBytes(uint64_t value, uint8_t *const bytes)
{
    // Sanity check
    if(NULL == bytes)
    {
        return false;
    }

    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;
    bytes[4] = (value >> 32) & 0xFF;
    bytes[5] = (value >> 40) & 0xFF;
    bytes[6] = (value >> 48) & 0xFF;
    bytes[7] = (value >> 56) & 0xFF;
    return true;
}

bool miscUtils_uint32ToLittleEndianBytes(uint32_t value, uint8_t *const bytes)
{
    // Sanity check
    if(NULL == bytes)
    {
        return false;
    }

    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;
    return true;
}

bool miscUtils_uint24ToLittleEndianBytes(uint32_t value, uint8_t *const bytes)
{
    // Sanity check
    if(NULL == bytes)
    {
        return false;
    }

    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    return true;
}

bool miscUtils_uint16ToLittleEndianBytes(uint16_t value, uint8_t *const bytes)
{
    // Sanity check
    if(NULL == bytes)
    {
        return false;
    }

    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    return true;
}

bool miscUtils_isValueInRange(const uint32_t value, const uint32_t minValue, const uint32_t maxValue)
{
    return (minValue <= value && value <= maxValue) ? true : false;
}

/*************************************************************************
 *********************** Local function definitions **********************
 ************************************************************************/
