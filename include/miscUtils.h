#ifdef __cplusplus
extern "C" {
#endif

#ifndef __MISC_UTILS_H_
#define __MISC_UTILS_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*************************************************************************
 ******************** Public Type/Constant definitions *******************
 ************************************************************************/
#define MISC_UTILS_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MISC_UTILS_MIN(x, y) (((x) < (y)) ? (x) : (y))

/*************************************************************************
 *********************** Public function declaration *********************
 ************************************************************************/

/************************* Function Description *************************/
/**
 * @details miscUtils_bigEndianBytesToUint64	Converts a big endian encoded byte array to a uint64_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_bigEndianBytesToUint64(const uint8_t* const bytes, uint64_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_bigEndianBytesToUint32	Converts a four bytes length big endian encoded array to a uint32_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if the conversion is successful, false otherwise.
 */
/************************************************************************/
bool miscUtils_bigEndianBytesToUint32(const uint8_t* const bytes, uint32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_bigEndianBytesToUint24	Converts a three bytes length big endian encoded array to a uint32_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_bigEndianBytesToUint24(const uint8_t* const bytes, uint32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_bigEndianBytesToUint16	Converts a big endian encoded byte array to a uint16_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_bigEndianBytesToUint16(const uint8_t* const bytes, uint16_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint64 Converts a little endian encoded byte array to a uint64_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_littleEndianBytesToUint64(const uint8_t* const bytes, uint64_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint32	Converts a four bytes length big little encoded array to a uint32_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_littleEndianBytesToUint32(const uint8_t* const bytes, uint32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint24	Converts a three bytes length big little encoded array to a uint32_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_littleEndianBytesToUint24(const uint8_t* const bytes, uint32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint16 Converts a little endian encoded byte array to a uint16_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_littleEndianBytesToUint16(const uint8_t* const bytes, uint16_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_extendSignBit64   Extend the sign bit of a valueWidth-bit value to a 64 bits result.
 * @param [in] value    The value to extend the sign of.
 * @param [in] valueWidth   The width of value in bit.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_extendSignBit64(int64_t value, uint8_t valueWidth, int64_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_extendSignBit32   Extend the sign bit of a valueWidth-bit value to a 32 bits result.
 * @param [in] value    The value to extend the sign of.
 * @param [in] valueWidth   The width of value in bit.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_extendSignBit32(int32_t value, uint8_t valueWidth, int32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_extendSignBit16   Extend the sign bit of a valueWidth-bit value to a 16 bits result.
 * @param [in] value    The value to extend the sign of.
 * @param [in] valueWidth   The width of value in bit.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_extendSignBit16(int16_t value, uint8_t valueWidth, int16_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_extendSignBit8   Extend the sign bit of a valueWidth-bit value to a 8 bits result.
 * @param [in] value    The value to extend the sign of.
 * @param [in] valueWidth   The width of value in bit.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_extendSignBit8(int8_t value, uint8_t valueWidth, int8_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint64ToBigEndianBytes	Convert a uint64_t value to a big endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_uint64ToBigEndianBytes(uint64_t value, uint8_t* const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint32ToBigEndianBytes	Convert a uint32_t (4 bytes) value to a big endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_uint32ToBigEndianBytes(uint32_t value, uint8_t* const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint24ToBigEndianBytes	Convert a uint32_t (3 bytes) value to a big endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_uint24ToBigEndianBytes(uint32_t value, uint8_t* const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint16ToBigEndianBytes	Convert a uint16_t value to a big endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_uint16ToBigEndianBytes(uint16_t value, uint8_t* const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint64ToLittleEndianBytes	Convert a uint64_t value to a little endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return true if successful, false otherwise.
 */
/************************************************************************/
bool miscUtils_uint64ToLittleEndianBytes(uint64_t value, uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint32ToLittleEndianBytes	Convert a uint32_t (4 bytes) value to a little endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return true if successful, false otherwise.
 */
/************************************************************************/
bool miscUtils_uint32ToLittleEndianBytes(uint32_t value, uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint24ToLittleEndianBytes Convert a uint32_t (3 bytes) value to a little endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return true if successful, false otherwise.
 */
/************************************************************************/
bool miscUtils_uint24ToLittleEndianBytes(uint32_t value, uint8_t *const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint16ToLittleEndianBytes	Convert a uint16_t value to a little endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return true if successful, false otherwise.
 */
/************************************************************************/
bool miscUtils_uint16ToLittleEndianBytes(uint16_t value, uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_isValueInRange	Check if a value is contained in a specific range.
 * @param [in] value    The value to compare.
 * @param [in] minValue The lower limit of the range.
 * @param [in] maxValue The upper limit of the range.
 *
 * @return  True if the value is contained in the range of [minValue, maxValue], false otherwise.
 */
/************************************************************************/
bool miscUtils_isValueInRange(const uint32_t value, const uint32_t minValue, const uint32_t maxValue);

#endif

#ifdef __cplusplus
}
#endif
