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
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef __CRCUTILS_H_
#define __CRCUTILS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/******************************************************************************
 ********************** Public Type/Constant definitions **********************
 *****************************************************************************/

/******************************************************************************
 ************************ Global functions declaration ************************
 *****************************************************************************/

/******************************************************************************
 ************************ Global variables declaration ************************
 *****************************************************************************/

/******************************************************************************
 ************************ Public function declaration *************************
 *****************************************************************************/

/**************************** Function Description ***************************/
/**
 * @details crcUtils_Ccitt8Compute  Calculate the CRC8 over a data area using
 *      the CCITT 8 algorithm.
 * @param [in] data The pointer to the data.
 * @param [in] length   The length of the data.
 * @param [out] result  A pointer to the variable in which the result is
 *      stored.
 * @return  true if successful, false otherwise.
 */
/*****************************************************************************/
bool crcUtils_Ccitt8Compute(const void *data, size_t length, uint8_t *result);

#endif

#ifdef __cplusplus
}
#endif
