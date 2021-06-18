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
 * @details miscUtils_bigEndianBytesToUint32	Convert a Big Endian encoded byte array to a Uint32.
 * @param [in] bytes    A pointer to the byte array to convert.
 *
 * @return The converted uint32 value.
 */
/************************************************************************/
uint32_t miscUtils_bigEndianBytesToUint32(const uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_bigEndianBytesToInt24 Convert a Big Endian encoded byte array to an int24.
 * @param [in] bytes    A pointer to the byte array to convert.
 *
 * @return The converted int24 value.
 */
/************************************************************************/
int32_t miscUtils_bigEndianBytesToInt24(const uint8_t *const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint64	Convert a Little Endian encoded byte array to a Uint64.
 * @param [in] bytes    A pointer to the byte array to convert.
 *
 * @return The converted uint64 value.
 */
/************************************************************************/
uint64_t miscUtils_littleEndianBytesToUint64(const uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint32	Convert a Little Endian encoded byte array to a Uint32.
 * @param [in] bytes    A pointer to the byte array to convert.
 *
 * @return The converted uint32 value.
 */
/************************************************************************/
uint32_t miscUtils_littleEndianBytesToUint32(const uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_littleEndianBytesToUint16	Convert a Little Endian encoded byte array to a Uint16.
 * @param [in] bytes    A pointer to the byte array to convert.
 *
 * @return The converted uint16 value.
 */
/************************************************************************/
uint16_t miscUtils_littleEndianBytesToUint16(const uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint64ToLittleEndianBytes	Convert a Uint64 value to a little Endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 */
/************************************************************************/
void miscUtils_uint64ToLittleEndianBytes(uint64_t value, uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint32ToLittleEndianBytes	Convert a Uint32 value to a little Endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 */
/************************************************************************/
void miscUtils_uint32ToLittleEndianBytes(uint32_t value, uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint32ToBigEndianBytes	Convert a Uint32 value to a big Endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 */
/************************************************************************/
void miscUtils_uint32ToBigEndianBytes(uint32_t value, uint8_t * const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint24ToLittleEndianBytes Convert a Uint24 value to a little Endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 */
/************************************************************************/
void miscUtils_uint24ToLittleEndianBytes(uint32_t value, uint8_t *const bytes);

/************************* Function Description *************************/
/**
 * @details miscUtils_uint16ToLittleEndianBytes	Convert a Uint16 value to a little Endian encoded byte array.
 * @param [in] value    The value to convert.
 * @param [out] bytes   A pointer to the byte array.
 */
/************************************************************************/
void miscUtils_uint16ToLittleEndianBytes(uint16_t value, uint8_t * const bytes);

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

/************************* Function Description *************************/
/**
 * @details miscUtils_computeCrc32	Calculate the CRC 32 bit.
 * @param [in] data         The data on which to compute the CRC.
 * @param [in] length       The length of the data in bytes.
 *
 * @return The CRC 32 bits.
 */
/************************************************************************/
uint32_t miscUtils_computeCrc32(uint8_t *data, size_t length);

#endif

#ifdef __cplusplus
}
#endif
