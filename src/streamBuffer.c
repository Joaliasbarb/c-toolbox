#include <string.h>

#include "streamBuffer.h"
#include "miscUtils.h"

/******************************************************************************
 ********************** Local Type/Constant definitions ***********************
 *****************************************************************************/
#define QUEUE_ELEMENT_PREFIX_LENGTH_SIZE (2)
#define QUEUE_ELEMENT_PREFIX_SIZE (QUEUE_ELEMENT_PREFIX_LENGTH_SIZE)

typedef struct streamBuffer
{
    uint32_t r_ptr;
    uint32_t w_ptr;
    uint32_t mask;
    uint32_t size;
    uint8_t *buffer;
} streamBufferMetadata_t;

/******************************************************************************
 ************************ Local function declarations *************************
 *****************************************************************************/
static streamBufferMetadata_t* getNextFreeStaticInstance(void);
static void writeDataInBuffer(streamBufferHandle_t self, const uint8_t *data, uint16_t size);
static void readDataFromBuffer(streamBufferHandle_t self, uint8_t *data, uint16_t size);

/******************************************************************************
 ************************ Global variables definitions ************************
 *****************************************************************************/

/******************************************************************************
 ************************ Local variables declarations ************************
 *****************************************************************************/
static streamBufferMetadata_t staticInstances[STREAM_BUFFER_MAX_STATIC_INSTANCE_COUNT] = { 0 };

/******************************************************************************
 ************************ Public function definitions *************************
 *****************************************************************************/
streamBufferHandle_t streamBuffer_createStatic(uint8_t *const buffer, size_t bufferSize)
{
    streamBufferMetadata_t *newInstance = NULL;

    // Sanity checks
    if((NULL == buffer) || !miscUtils_isPowerOf2(bufferSize))
    {
        return NULL;
    }

    // Instantiate the queue
    newInstance = getNextFreeStaticInstance();
    if(NULL != newInstance)
    {
        newInstance->r_ptr = 0;
        newInstance->w_ptr = 0;
        newInstance->mask = bufferSize - 1;
        newInstance->size = bufferSize;
        newInstance->buffer = buffer;
    }
    return newInstance;
}

bool streamBuffer_freeStatic(streamBufferHandle_t *self)
{
    streamBufferMetadata_t *instance = NULL;

    // Sanity checks
    if((NULL == self) || (NULL == *self))
    {
        return false;
    }

    instance = (streamBufferMetadata_t*) *self;
    instance->buffer = NULL;
    *self = NULL;
    return true;
}

bool streamBuffer_put(streamBufferHandle_t self, const uint8_t *data, uint16_t size)
{
    size_t usedMemory = 0;
    uint8_t dataPrefix[QUEUE_ELEMENT_PREFIX_SIZE] = { 0 };

    // Sanity checks
    if((NULL == self) || (NULL == data) || (0 == size))
    {
        return false;
    }

    // Check if there's enough space in the queue
    streamBuffer_space(self, &usedMemory);
    if((QUEUE_ELEMENT_PREFIX_SIZE + size) > (self->size - usedMemory))
    {
        return false;
    }

    // Serialize the prefix
    miscUtils_uint16ToBigEndianBytes(size, dataPrefix);

    // Write the data
    writeDataInBuffer(self, dataPrefix, QUEUE_ELEMENT_PREFIX_SIZE);
    writeDataInBuffer(self, data, size);

    return true;
}

bool streamBuffer_get(streamBufferHandle_t self, uint8_t *data, uint16_t *size)
{
    size_t usedMemory = 0;
    uint8_t prefix[QUEUE_ELEMENT_PREFIX_SIZE] = { 0 };

    // Sanity checks
    if((NULL == self) || (NULL == data) || (NULL == size))
    {
        return false;
    }

    // Check if the queue is empty
    streamBuffer_space(self, &usedMemory);
    if(0 == usedMemory)
    {
        *size = 0;
        return false;
    }

    // Deserialize the prefix
    readDataFromBuffer(self, prefix, QUEUE_ELEMENT_PREFIX_SIZE);
    miscUtils_bigEndianBytesToUint16(prefix, size);

    // Read the element
    readDataFromBuffer(self, data, *size);
    return true;
}

bool streamBuffer_space(streamBufferHandle_t self, size_t *byteCount)
{
    // Sanity checks
    if((NULL == self) || (NULL == byteCount))
    {
        return false;
    }

    *byteCount = ((uint32_t) (self->w_ptr - self->r_ptr)) & self->mask;
    return true;
}

bool streamBuffer_empty(streamBufferHandle_t self)
{
    // Sanity checks
    if((NULL == self))
    {
        return false;
    }

    self->r_ptr = 0;
    self->w_ptr = 0;
    return true;
}

/******************************************************************************
 ************************* Local function definitions *************************
 *****************************************************************************/
static streamBufferMetadata_t* getNextFreeStaticInstance(void)
{
    size_t i = 0;
    bool isInstanceFound = false;
    streamBufferMetadata_t *ret = NULL;

    while((i < STREAM_BUFFER_MAX_STATIC_INSTANCE_COUNT) && !isInstanceFound)
    {
        if(NULL == staticInstances[i].buffer)
        {
            isInstanceFound = true;
            ret = &staticInstances[i];
        }
        i++;
    }
    return ret;
}

static void writeDataInBuffer(streamBufferHandle_t self, const uint8_t *data, uint16_t size)
{
    uint32_t over = 0;
    uint32_t remainingBytesCount = 0;

    // Check if the end address is reached
    over = (self->w_ptr + size) & self->mask;
    if((0 == over) || (over > self->w_ptr))
    {
        // The element may be written in one go
        memcpy(&self->buffer[self->w_ptr], data, size);
        self->w_ptr = over;
    }
    else
    {
        // The element shall be written in two chunk.
        // The over variable contains the number of bytes in the second chunk
        remainingBytesCount = size - over;
        memcpy(&self->buffer[self->w_ptr], data, remainingBytesCount);
        memcpy(&self->buffer[0], &data[remainingBytesCount], over);
        self->w_ptr = over;
    }
}

static void readDataFromBuffer(streamBufferHandle_t self, uint8_t *data, uint16_t size)
{
    uint32_t over = 0;
    uint32_t remainingBytesCount = 0;

    // Check if the end address is reached
    over = (self->r_ptr + size) & self->mask;
    if((0 == over) || (over > self->r_ptr))
    {
        // The element may be read in one go
        memcpy(data, &self->buffer[self->r_ptr], size);
        self->r_ptr = over;
    }
    else
    {
        // The element shall be read in two chunk.
        // The over variable contains the number of bytes in the second chunk
        remainingBytesCount = size - over;
        memcpy(data, &self->buffer[self->r_ptr], remainingBytesCount);
        memcpy(&data[remainingBytesCount], &self->buffer[0], over);
        self->r_ptr = over;
    }
}
