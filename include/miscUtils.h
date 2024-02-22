/*******************************************************************************
* Copyright 2021 Joakim Nicolet (joakimnicolet@gmail.com)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* - The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*******************************************************************************/
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
#define MISC_UTILS_CLAMP(val, low, high) \
    (((val) <= (low)) ? (low) : MISC_UTILS_MIN(val, high))
#define MISC_UTILS_IN_RANGE(val, min, mac) ((val) >= (min) && (val) <= (max))
#define MISC_UTILS_IS_POWER_OF_TWO(x) (((x) != 0U) && (((x) & ((x) - 1U)) == 0U))
#define MISC_UTILS_BUILD_ASSERT(cond) ((void)sizeof(char[1 - 2*!!(condition)]))

/*************************************************************************
 *********************** Public function declaration *********************
 ************************************************************************/

/************************* Function Description *************************/
/**
 * @details miscUtils_bigEndianBytesToUint64	Converts a big endian encoded byte array to a uint64_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_bigEndianBytesToUint64(const uint8_t* const bytes, uint64_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_bigEndianBytesToUint32	Converts a four bytes length big endian encoded array to a uint32_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if the conversion is successful, false otherwise.
 */
/************************************************************************/
bool miscUtils_bigEndianBytesToUint32(const uint8_t* const bytes, uint32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_bigEndianBytesToUint24	Converts a three bytes length big endian encoded array to a uint32_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_bigEndianBytesToUint24(const uint8_t* const bytes, uint32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_bigEndianBytesToUint16	Converts a big endian encoded byte array to a uint16_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_bigEndianBytesToUint16(const uint8_t* const bytes, uint16_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint64 Converts a little endian encoded byte array to a uint64_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_littleEndianBytesToUint64(const uint8_t* const bytes, uint64_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint32	Converts a four bytes length big little encoded array to a uint32_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_littleEndianBytesToUint32(const uint8_t* const bytes, uint32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint24	Converts a three bytes length big little encoded array to a uint32_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_littleEndianBytesToUint24(const uint8_t* const bytes, uint32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint16 Converts a little endian encoded byte array to a uint16_t.
 * @param [in] bytes    A pointer to the byte array to convert.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if the conversion is successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_littleEndianBytesToUint16(const uint8_t* const bytes, uint16_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_extendSignBit64   Extend the sign bit of a valueWidth-bit value to a 64 bits result.
 * @param [in] value    The value to extend the sign of.
 * @param [in] valueWidth   The width of value in bit.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_extendSignBit64(int64_t value, uint8_t valueWidth, int64_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_extendSignBit32   Extend the sign bit of a valueWidth-bit value to a 32 bits result.
 * @param [in] value    The value to extend the sign of.
 * @param [in] valueWidth   The width of value in bit.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_extendSignBit32(int32_t value, uint8_t valueWidth, int32_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_extendSignBit16   Extend the sign bit of a valueWidth-bit value to a 16 bits result.
 * @param [in] value    The value to extend the sign of.
 * @param [in] valueWidth   The width of value in bit.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_extendSignBit16(int16_t value, uint8_t valueWidth, int16_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_extendSignBit8   Extend the sign bit of a valueWidth-bit value to a 8 bits result.
 * @param [in] value    The value to extend the sign of.
 * @param [in] valueWidth   The width of value in bit.
 * @param [out] resultPtr   A pointer to the variable to store the result in.
 * @return  true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_extendSignBit8(int8_t value, uint8_t valueWidth, int8_t* const resultPtr);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint64ToBigEndianBytes	Convert a uint64_t value to a big endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return  true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_uint64ToBigEndianBytes(uint64_t value, uint8_t* const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint32ToBigEndianBytes	Convert a uint32_t (4 bytes) value to a big endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return  true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_uint32ToBigEndianBytes(uint32_t value, uint8_t* const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint24ToBigEndianBytes	Convert a uint32_t (3 bytes) value to a big endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return  true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_uint24ToBigEndianBytes(uint32_t value, uint8_t* const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint16ToBigEndianBytes	Convert a uint16_t value to a big endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return  true if successful, false otherwise.
 */
 /************************************************************************/
bool miscUtils_uint16ToBigEndianBytes(uint16_t value, uint8_t* const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint64ToLittleEndianBytes	Convert a uint64_t value to a little endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return  true if successful, false otherwise.
 */
/************************************************************************/
bool miscUtils_uint64ToLittleEndianBytes(uint64_t value, uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint32ToLittleEndianBytes	Convert a uint32_t (4 bytes) value to a little endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return  true if successful, false otherwise.
 */
/************************************************************************/
bool miscUtils_uint32ToLittleEndianBytes(uint32_t value, uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint24ToLittleEndianBytes Convert a uint32_t (3 bytes) value to a little endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return  true if successful, false otherwise.
 */
/************************************************************************/
bool miscUtils_uint24ToLittleEndianBytes(uint32_t value, uint8_t *const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint16ToLittleEndianBytes	Convert a uint16_t value to a little endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 * @return  true if successful, false otherwise.
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
 * @return  true if the value is contained in the range of [minValue, maxValue], false otherwise.
 */
/************************************************************************/
bool miscUtils_isValueInRange(const uint32_t value, const uint32_t minValue, const uint32_t maxValue);

/************************* Function Description *************************/
/**
 * @details miscUtils_isPowerOf2    Check if a value is a power of 2.
 * @param [in] value    The value to check.
 * @return  true if the value is a power of two (0 not included), false otherwise.
 */
/************************************************************************/
bool miscUtils_isPowerOf2(size_t value);

#endif

#ifdef __cplusplus
}
#endif
