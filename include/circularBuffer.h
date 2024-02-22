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

#ifndef __CIRCULAR_BUFFER_H_
#define __CIRCULAR_BUFFER_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*************************************************************************
 ******************** Public Type/Constant definitions *******************
 ************************************************************************/
#define CB_FRONT_IDX    (0)     /**< Circular buffer front item index  */

typedef struct circularBuffer
{
    void *buffer;           // data buffer
    void *buffer_end;       // end of data buffer
    size_t capacity;        // maximum number of items in the buffer
    volatile size_t count;  // number of items in the buffer
    size_t size;            // size of each item in the buffer
    void *back;             // pointer to the back
    void *front;            // pointer to the front
} circularBuffer_t;

/*************************************************************************
 *********************** Public function declaration *********************
 ************************************************************************/

/************************* Function Description *************************/
/**
 * @details cb_initStatic   Create a circular buffer instance with a static array.
 *      This buffer can only contain elements of the same type.
 * @param [out] cb      A pointer to the circular buffer instance. 
 * @param [in] capacity The max number of elements in the buffer.
 * @param [in] size     The size of the buffer elements in byte.
 * @param [in] array    The array to manage as circular buffer.
 * @return true if the initialization was successful, false otherwise. 
 */
/************************************************************************/
bool cb_initStatic(circularBuffer_t *cb, void *array, size_t capacity, size_t size);

/************************* Function Description *************************/
/**
 * @details cb_init     Create a circulat buffer instance. The memory is dynamically allocated with malloc.
 *      This buffer can only contain elements of the same type.
 * @param [out] cb      A pointer to the circular buffer instance. 
 * @param [in] capacity The max number of elements in the buffer.
 * @param [in] size     The size of the buffer elements in byte.
 * @return true if the initialization was successful, false otherwise.
 */
/************************************************************************/
bool cb_init(circularBuffer_t *cb, size_t capacity, size_t size);

/************************* Function Description *************************/
/**
 * @details cb_free Delete a circulat buffer instance.
 * @param [in] cb   A pointer to the circular buffer instance. 
 * @return true if the uninitialization was successful, false otherwise.
 */
/************************************************************************/
bool cb_free(circularBuffer_t *cb);

/************************* Function Description *************************/
/**
 * @details cb_pushBack Add an element to the back of the buffer.
 * @param [in] cb   A pointer to the circular buffer instance. 
 * @param [in] item A pointer to the element to add.
 *
 * @return true is the element was successfuly added, false otherwise. 
 */
/************************************************************************/
bool cb_pushBack(circularBuffer_t *cb, const void *item);

/************************* Function Description *************************/
/**
 * @details cb_pushBackOverwrite    Add an element to the back of the buffer.
 *      If the buffer is full remove the element at the front of the buffer.
 * @param [in] cb   A pointer to the circular buffer instance.
 * @param [in] item A pointer to the element to add.
 * @param [out] oldItem A pointer to the oldest element if the buffer is full.
 *
 * @return true is an element was removed from the buffer, false otherwise.
 */
/************************************************************************/
bool cb_pushBackOverwrite(circularBuffer_t * const cb, void * const item, void * const oldItem);

/************************* Function Description *************************/
/**
 * @details cb_pushFront Add an element to the front of the buffer.
 * @param [in] cb   A pointer to the circular buffer instance. 
 * @param [in] item A pointer to the element to add.
 *
 * @return true is the element was successfuly added, false otherwise. 
 */
/************************************************************************/
bool cb_pushFront(circularBuffer_t *cb, const void *item);

/************************* Function Description *************************/
/**
 * @details cb_pushFrontOverwrite   Add an element to the front of the buffer.
 *      If the buffer is full remove the element at the front of the buffer.
 * @param [in] cb   A pointer to the circular buffer instance.
 * @param [in] item A pointer to the element to add.
 * @param [out] oldItem A pointer to the oldest element if the buffer is full.
 *
 * @return true is an element was removed from the buffer, false otherwise.
 */
/************************************************************************/
bool cb_pushFrontOverwrite(circularBuffer_t * const cb, void * const item, void * const oldItem);

/************************* Function Description *************************/
/**
 * @details cb_popBack  Get an element from the back of the buffer.
 * @param [in] cb       A pointer to the circular buffer instance. 
 * @param [out] item    A pointer to the item to get from the buffer.
 *      If this parameter is NULL, the element is still removed from the buffer.
 *
 * @return true is the element was successfuly taken, false otherwise. 
 */
/************************************************************************/
bool cb_popBack(circularBuffer_t *cb, void *item);

/************************* Function Description *************************/
/**
 * @details cb_popFront Get an element from the front of the buffer.
 * @param [in] cb       A pointer to the circular buffer instance. 
 * @param [out] item    A pointer to the item to get from the buffer.
 *      If this parameter is NULL, the element is still removed from the buffer.
 *
 * @return true is the element was successfuly taken, false otherwise. 
 */
/************************************************************************/
bool cb_popFront(circularBuffer_t *cb, void *item);

/************************* Function Description *************************/
/**
 * @details cb_peek     Get an element from the buffer without actually removing it.
 * @param [in] cb       A pointer to the circular buffer instance.
 * @param [in] itemIndex    The index of the item to get. 0 is the index of the item at the front of the buffer.
 * @param [out] item    A pointer to the item to get from the buffer.
 *
 * @return true is the element was successfuly taken, false otherwise.
 */
/************************************************************************/
bool cb_peek(circularBuffer_t * const cb, size_t itemIndex, void * const item);

/************************* Function Description *************************/
/**
 * @details cb_empty    Empty a circular buffer instance.
 * @param [in] cb   A pointer to the circular buffer instance. 
 */
/************************************************************************/
void cb_empty(circularBuffer_t *cb);

/************************* Function Description *************************/
/**
 * @details cb_getItemCount Get the number of item in the buffer.
 * @param [in] cb       A pointer to the circular buffer instance. 
 *
 * @return The number of item in the buffer. 
 */
/************************************************************************/
size_t cb_getItemCount(circularBuffer_t *cb);

/************************* Function Description *************************/
/**
 * @details cb_getArray     Get an array containing all the items in the buffer from the front to the back.
 * @param [in] cb           A pointer to the circular buffer instance.
 * @param [in] startIndex   The index of the item to get. 0 is the index of the item at the front of the buffer.
 * @param [in] nbOfItems    Number of items to copy in array. If nbOfItems is greater than the number of items between
 *      startIndex and the end of the buffer, no item is copied.
 * @param [out] array       A pointer to the array to copy the items in.
 *
 * @return The number of copied items.
 */
/************************************************************************/
size_t cb_getArray(circularBuffer_t * const cb, size_t startIndex, size_t nbOfItems, void * const array);
#endif

#ifdef __cplusplus
}
#endif
