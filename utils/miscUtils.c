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
uint32_t miscUtils_bigEndianBytesToUint32(const uint8_t *const bytes)
{
    return ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3]);
}

int32_t miscUtils_bigEndianBytesToInt24(const uint8_t *const bytes)
{
    int32_t retValue = 0;

    // Invert the byte order
    retValue = ((bytes[0] << 16) + (bytes[1] << 8) + bytes[2]);

    // Check if the value is negative and propagate the sign bit
    if(retValue & 0x800000L)
    {
        retValue |= 0xFF000000L;
    }

    return retValue;
}

uint64_t miscUtils_littleEndianBytesToUint64(const uint8_t *const bytes)
{
    return (((uint64_t) (bytes[7]) << 56) + ((uint64_t) (bytes[6]) << 48) +
            ((uint64_t) (bytes[5]) << 40) + ((uint64_t) (bytes[4]) << 32) +
            (bytes[3] << 24) + (bytes[2] << 16) + (bytes[1] << 8) + bytes[0]);
}

uint32_t miscUtils_littleEndianBytesToUint32(const uint8_t *const bytes)
{
    return ((bytes[3] << 24) + (bytes[2] << 16) + (bytes[1] << 8) + bytes[0]);
}

uint16_t miscUtils_littleEndianBytesToUint16(const uint8_t *const bytes)
{
    return ((bytes[1] << 8) + bytes[0]);
}

void miscUtils_uint64ToLittleEndianBytes(uint64_t value, uint8_t *const bytes)
{
    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;
    bytes[4] = (value >> 32) & 0xFF;
    bytes[5] = (value >> 40) & 0xFF;
    bytes[6] = (value >> 48) & 0xFF;
    bytes[7] = (value >> 56) & 0xFF;
}

void miscUtils_uint32ToLittleEndianBytes(uint32_t value, uint8_t *const bytes)
{
    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;
}

void miscUtils_uint32ToBigEndianBytes(uint32_t value, uint8_t *const bytes)
{
    bytes[3] = value & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[0] = (value >> 24) & 0xFF;
}

void miscUtils_uint24ToLittleEndianBytes(uint32_t value, uint8_t *const bytes)
{
    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
}

void miscUtils_uint16ToLittleEndianBytes(uint16_t value, uint8_t *const bytes)
{
    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
}

bool miscUtils_isValueInRange(const uint32_t value, const uint32_t minValue, const uint32_t maxValue)
{
    return (minValue <= value && value <= maxValue) ? true : false;
}

/*************************************************************************
 *********************** Local function definitions **********************
 ************************************************************************/
