#include <stdlib.h>
#include <string.h>

#include "circularBuffer.h"

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
bool cb_initStatic(circularBuffer_t *cb, void *array, size_t capacity, size_t size)
{
    // Sanity check
    if((NULL == cb) || (NULL == array) || (0 == capacity) || (0 == size))
    {
        return false;
    }

    cb->buffer = array;
    cb->buffer_end = (char *)cb->buffer + capacity * size;
    cb->capacity = capacity;
    cb->count = 0;
    cb->size = size;
    cb->back = cb->buffer;
    cb->front = cb->buffer;
    return true;
}

bool cb_init(circularBuffer_t *cb, size_t capacity, size_t size)
{
    // Sanity check
    if((NULL == cb) || (0 == capacity) || (0 == size))
    {
        return false;
    }

    // Allocate memory for the buffer
    cb->buffer = malloc(capacity * size);
    if(NULL == cb->buffer)
    {
        return false;
    }

    cb->buffer_end = (char *)cb->buffer + capacity * size;
    cb->capacity = capacity;
    cb->count = 0;
    cb->size = size;
    cb->back = cb->buffer;
    cb->front = cb->buffer;
    return true;
}

bool cb_free(circularBuffer_t *cb)
{
    // Sanity check
    if(NULL == cb)
    {
        return false;
    }

    free(cb->buffer);
    cb->count = 0;
    cb->size = 0;
    return true;
}

bool cb_pushBack(circularBuffer_t *cb, const void *item)
{
    // Sanity check
    if((NULL == cb) || (NULL == item) || (cb->count == cb->capacity))
    {
        return false;
    }
        
    memcpy(cb->back, item, cb->size);
    cb->back = (char*)cb->back + cb->size;
    if(cb->back == cb->buffer_end)
    {
        cb->back = cb->buffer;
    }
    cb->count++;
    
    return true;
}

bool cb_pushBackOverwrite(circularBuffer_t * const cb, void * const item, void * const oldItem)
{
    bool isBufferFullBeforeAdd = false;

    // Sanity check
    if((NULL == cb) || (NULL == item))
    {
        return false;
    }

    // Check if buffer is full
    if(cb->count == cb->capacity)
    {
        isBufferFullBeforeAdd = true;
        cb_popFront(cb, oldItem);
        cb_pushBack(cb, item);
    }
    else
    {
        cb_pushBack(cb, item);
    }

    return isBufferFullBeforeAdd;
}

bool cb_pushFront(circularBuffer_t *cb, const void *item)
{
    // Sanity check
    if((NULL == cb) || (NULL == item) || (cb->count == cb->capacity))
    {
        return false;
    }
    
    cb->front = (char*)cb->front - cb->size;
    if(cb->front < cb->buffer)
    {
        cb->front = (char*)cb->buffer_end - cb->size;
    }
    memcpy(cb->front, item, cb->size);
    cb->count++;
    
    return true;
}

bool cb_pushFrontOverwrite(circularBuffer_t * const cb, void * const item, void * const oldItem)
{
    bool isBufferFullBeforeAdd = false;

    // Sanity check
    if ((NULL == cb) || (NULL == item))
    {
        return false;
    }

    // Check if buffer is full
    if(cb->count == cb->capacity)
    {
        isBufferFullBeforeAdd = true;
        cb_popFront(cb, oldItem);
        cb_pushFront(cb, item);
    }
    else
    {
        cb_pushFront(cb, item);
    }

    return isBufferFullBeforeAdd;
}

bool cb_popBack(circularBuffer_t *cb, void *item)
{
    // Sanity check
    if((NULL == cb) || (0 == cb->count))
    {
        return false;
    }

    cb->back = (char*)cb->back - cb->size;
    if(cb->back < cb->buffer)  
    {
        cb->back = (char*)cb->buffer_end - cb->size;
    }
    
    if(NULL != item)
    {
        memcpy(item, cb->back, cb->size);
    }
    cb->count--;
        
    return true;
}

bool cb_popFront(circularBuffer_t *cb, void *item)
{
    // Sanity check
    if((NULL == cb) || (0 == cb->count))
    {
        return false;
    }
        
    if(NULL != item)
    {
        memcpy(item, cb->front, cb->size);
    }

    cb->front = (char*)cb->front + cb->size;
    if(cb->front == cb->buffer_end)  
    {
        cb->front = cb->buffer;
    }
    cb->count--;
        
    return true;
}

bool cb_peek(circularBuffer_t * const cb, size_t itemIndex, void * const item)
{
    char *copyPointer = NULL;

    // Sanity check
    if((NULL == cb) || (itemIndex >= cb->count) || (NULL == item))
    {
        return false;
    }

    // calculate the address of the item
    copyPointer = cb->front;
    while(0 != itemIndex)
    {
        copyPointer += cb->size;
        if(copyPointer == cb->buffer_end)
        {
            copyPointer = cb->buffer;
        }
        itemIndex--;
    }

    memcpy(item, copyPointer, cb->size);
    return true;
}
    
void cb_empty(circularBuffer_t *cb)
{
    // Sanity check
    if(NULL == cb)
    {
        return;
    }

    cb->count = 0;
    cb->back = cb->buffer;
    cb->front = cb->buffer;
}

size_t cb_getItemCount(circularBuffer_t *cb)
{
    // Sanity check
    if(NULL == cb)
    {
        return 0;
    }

    return cb->count;
}

size_t cb_getArray(circularBuffer_t * const cb, size_t startIndex, size_t nbOfItems, void * const array)
{
    char *copyPointer = NULL;

    // Sanity check
    if((NULL == cb) || (NULL == array) || (startIndex >= cb->count) || ((nbOfItems + startIndex) > cb->count))
    {
        return 0;
    }

    // Calculate the address of the item
    copyPointer = cb->front;
    while(0 != startIndex)
    {
        copyPointer += cb->size;
        if(copyPointer == cb->buffer_end)
        {
            copyPointer = cb->buffer;
        }
        startIndex--;
    }

    // Copy nbOfItems to array
    for(size_t i = 0; i < nbOfItems; i++)
    {
        // Copy the element to the array
        memcpy((char *) (array) + (i * cb->size), copyPointer, cb->size);

        // Increment the copy pointer
        copyPointer += cb->size;
        if(copyPointer == cb->buffer_end)
        {
            copyPointer = cb->buffer;
        }
    }

    return nbOfItems;
}

/*************************************************************************
 *********************** Local function definitions **********************
 ************************************************************************/
