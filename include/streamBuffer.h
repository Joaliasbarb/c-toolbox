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
* - The above copyright noticeand this permission notice shall be included in
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

#ifndef __STREAM_BUFFER_H_
#define __STREAM_BUFFER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/******************************************************************************
 ********************** Public Type/Constant definitions **********************
 *****************************************************************************/
#define STREAM_BUFFER_MAX_STATIC_INSTANCE_COUNT (5)
typedef struct streamBuffer *streamBufferHandle_t;

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
 * @details streamBuffer_createStatic    Create a stream buffer instance with a
 *      static array.
 * @param [in] buffer   A valid pointer to the underlying memory managed by the
 *      stream buffer.
 * @param [in] bufferSize   The size of the buffer. This shall be a power of 2.
 * @return A handle to a new static instance of stream buffer if successful,
 *      NULL otherwise. 
 */
/*****************************************************************************/
streamBufferHandle_t streamBuffer_createStatic(uint8_t *const buffer, size_t bufferSize);

/**************************** Function Description ***************************/
/**
 * @details streamBuffer_freeStatic Free a stream buffer instance.
 * @param [in] self A pointer to a stream buffer handle.
 * @return true if successful, false otherwise. 
 */
/*****************************************************************************/
bool streamBuffer_freeStatic(streamBufferHandle_t *self);

/**************************** Function Description ***************************/
/**
 * @details streamBuffer_put    Add data to the stream buffer.
 * @param [in] self The stream buffer handle.
 * @param [in] data A pointer to the data to add.
 * @param [in] size The size of the data to add in bytes.
 * @return true if successful, false otherwise. 
 */
/*****************************************************************************/
bool streamBuffer_put(streamBufferHandle_t self, const uint8_t *data, uint16_t size);

/**************************** Function Description ***************************/
/**
 * @details streamBuffer_get    Get data from the stream buffer.
 * @param [in] self The stream buffer handle.
 * @param [out] data    A pointer to the data to get.
 * @param [out] size    The size of the retreived data in bytes.
 * @return true if successful, false otherwise. 
 */
/*****************************************************************************/
bool streamBuffer_get(streamBufferHandle_t self, uint8_t *data, uint16_t *size);

/**************************** Function Description ***************************/
/**
 * @details streamBuffer_space  Get the remaining space in the stream buffer.
 * @param [in] self The stream buffer handle.
 * @param [out] byteCount   The number of available bytes in the stream buffer.
 * @return true if successful, false otherwise. 
 */
/*****************************************************************************/
bool streamBuffer_space(streamBufferHandle_t self, size_t *byteCount);

/**************************** Function Description ***************************/
/**
 * @details streamBuffer_empty  Queries a stream buffer to see if it's empty.
 * @param [in] self The stream buffer handle.
 * @return true if the stream buffer is empty, false otherwise. 
 */
/*****************************************************************************/
bool streamBuffer_empty(streamBufferHandle_t self);

#endif

#ifdef __cplusplus
}
#endif
