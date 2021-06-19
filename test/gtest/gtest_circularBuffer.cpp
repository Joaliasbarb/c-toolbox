#include <gtest/gtest.h>
#include <cstring>
#include <algorithm>
#include "circularBuffer.h"

constexpr int BUFFER_SIZE = 5;

class CircularBufferTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        cb_initStatic(&testBuffer, testBufferArray, BUFFER_SIZE, sizeof(*testBufferArray));
    }

    void TearDown() override
    {

    }

    uint8_t testBufferArray[BUFFER_SIZE] = {0};
    circularBuffer_t testBuffer = {0};
};

TEST_F(CircularBufferTest, InitStaticNullPointer)
{
    EXPECT_FALSE(cb_initStatic(NULL, NULL, 0, 0));
    EXPECT_FALSE(cb_initStatic(NULL, NULL, 0, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_initStatic(NULL, NULL, BUFFER_SIZE, 0));
    EXPECT_FALSE(cb_initStatic(NULL, NULL, BUFFER_SIZE, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_initStatic(NULL, testBufferArray, 0, 0));
    EXPECT_FALSE(cb_initStatic(NULL, testBufferArray, 0, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_initStatic(NULL, testBufferArray, BUFFER_SIZE, 0));
    EXPECT_FALSE(cb_initStatic(NULL, testBufferArray, BUFFER_SIZE, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_initStatic(&testBuffer, NULL, 0, 0));
    EXPECT_FALSE(cb_initStatic(&testBuffer, NULL, 0, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_initStatic(&testBuffer, NULL, BUFFER_SIZE, 0));
    EXPECT_FALSE(cb_initStatic(&testBuffer, NULL, BUFFER_SIZE, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_initStatic(&testBuffer, testBufferArray, 0, 0));
    EXPECT_FALSE(cb_initStatic(&testBuffer, testBufferArray, 0, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_initStatic(&testBuffer, testBufferArray, BUFFER_SIZE, 0));
    EXPECT_TRUE(cb_initStatic(&testBuffer, testBufferArray, BUFFER_SIZE, sizeof(*testBufferArray)));
}

TEST_F(CircularBufferTest, InitNullPointer)
{
    bool isSuccessful = false;

    EXPECT_FALSE(cb_init(NULL, 0, 0));
    EXPECT_FALSE(cb_init(NULL, 0, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_init(NULL, BUFFER_SIZE, 0));
    EXPECT_FALSE(cb_init(NULL, BUFFER_SIZE, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_init(&testBuffer, 0, 0));
    EXPECT_FALSE(cb_init(&testBuffer, 0, sizeof(*testBufferArray)));
    EXPECT_FALSE(cb_init(&testBuffer, BUFFER_SIZE, 0));
    isSuccessful = cb_init(&testBuffer, BUFFER_SIZE, sizeof(*testBufferArray));
    EXPECT_TRUE(isSuccessful);

    if(isSuccessful)
    {
        cb_free(&testBuffer);
    }
}

TEST_F(CircularBufferTest, FreeNullPointer)
{
    bool isSuccessful = false;

    EXPECT_FALSE(cb_free(NULL));
    isSuccessful = cb_init(&testBuffer, BUFFER_SIZE, sizeof(*testBufferArray));
    EXPECT_TRUE(isSuccessful);
    if(isSuccessful)
    {
        EXPECT_TRUE(cb_free(&testBuffer));
    }
}

TEST_F(CircularBufferTest, IsEmptyInitially) 
{
    EXPECT_EQ(cb_getItemCount(&testBuffer), 0) << "Buffer not empty after initialization.\n";
}

TEST_F(CircularBufferTest, PushBack) 
{
    std::vector<uint8_t> inputData{10, 25, 37, 43, 59};
    uint8_t outputData[BUFFER_SIZE] = {0};
    size_t dataCount = 0;
    bool isAdded = false;

    // Fill the buffer
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        isAdded = cb_pushBack(&testBuffer, &inputData[i]);
        EXPECT_TRUE(isAdded) << "Failed to add data to buffer (unexpected return value).\n";
        EXPECT_EQ(i + 1, cb_getItemCount(&testBuffer)) << "Failed to add data to buffer (unexpected item count).\n";
    }

    // Check the data
    dataCount = cb_getBufferArray(&testBuffer, CB_FRONT_IDX, BUFFER_SIZE, outputData);
    EXPECT_EQ(BUFFER_SIZE, dataCount);
    EXPECT_EQ(0, memcmp(inputData.data(), outputData, BUFFER_SIZE)) << "Added data mismatch.\n";

    // Add one more data
    isAdded = cb_pushBack(&testBuffer, &inputData[0]);
    dataCount = cb_getBufferArray(&testBuffer, CB_FRONT_IDX, BUFFER_SIZE, outputData);
    EXPECT_FALSE(isAdded);
    EXPECT_EQ(BUFFER_SIZE, dataCount);
    EXPECT_EQ(0, memcmp(inputData.data(), outputData, BUFFER_SIZE)) << "Buffer was modified.\n";
}

TEST_F(CircularBufferTest, PushBackNullPointer)
{
    uint8_t dummy = 0;
    size_t dataCount = 0;
    bool isAdded = false;

    isAdded = cb_pushBack(NULL, NULL);
    EXPECT_FALSE(isAdded);

    isAdded = cb_pushBack(NULL, &dummy);
    EXPECT_FALSE(isAdded);

    isAdded = cb_pushBack(&testBuffer, NULL);
    EXPECT_FALSE(isAdded);
}

TEST_F(CircularBufferTest, PushBackOverwrite)
{
    std::vector<uint8_t> inputData{ 10, 25, 37, 43, 59 };
    uint8_t outputData[BUFFER_SIZE] = { 0 };
    uint8_t oldValue = 0;
    size_t dataCount = 0;
    bool isItemRemoved = false;

    // Fill the buffer
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        isItemRemoved = cb_pushBackOverwrite(&testBuffer, &inputData[i], &oldValue);
        EXPECT_FALSE(isItemRemoved) << "Failed to add data to buffer (unexpected return value).\n";
        EXPECT_EQ(i + 1, cb_getItemCount(&testBuffer)) << "Failed to add data to buffer (unexpected item count).\n";
    }

    // Check the data
    dataCount = cb_getBufferArray(&testBuffer, CB_FRONT_IDX, BUFFER_SIZE, outputData);
    EXPECT_EQ(BUFFER_SIZE, dataCount);
    EXPECT_EQ(0, memcmp(inputData.data(), outputData, BUFFER_SIZE)) << "Added data mismatch.\n";

    // Add one more data
    isItemRemoved = cb_pushBackOverwrite(&testBuffer, &inputData[0], &oldValue);
    dataCount = cb_getBufferArray(&testBuffer, CB_FRONT_IDX, BUFFER_SIZE, outputData);
    EXPECT_TRUE(isItemRemoved);
    EXPECT_EQ(BUFFER_SIZE, dataCount);
    EXPECT_EQ(inputData.front(), oldValue);
    std::rotate(inputData.begin(), inputData.begin() + 1, inputData.end());
    EXPECT_EQ(0, memcmp(inputData.data(), outputData, BUFFER_SIZE)) << "Added data mismatch after overwrite.\n";
}

TEST_F(CircularBufferTest, PushBackOverwriteNullPointer)
{
    uint8_t dummy = 0;
    size_t dataCount = 0;
    bool isItemRemoved = false;

    isItemRemoved = cb_pushBackOverwrite(NULL, NULL, NULL);
    EXPECT_FALSE(isItemRemoved);

    isItemRemoved = cb_pushBackOverwrite(NULL, &dummy, NULL);
    EXPECT_FALSE(isItemRemoved);

    isItemRemoved = cb_pushBackOverwrite(&testBuffer, NULL, NULL);
    EXPECT_FALSE(isItemRemoved);
    EXPECT_EQ(0, cb_getItemCount(&testBuffer));

    isItemRemoved = cb_pushBackOverwrite(&testBuffer, &dummy, NULL);
    EXPECT_FALSE(isItemRemoved);
    EXPECT_EQ(1, cb_getItemCount(&testBuffer));
}

TEST_F(CircularBufferTest, PushFront)
{
    std::vector<uint8_t> inputData{ 10, 25, 37, 43, 59 };
    uint8_t outputData[BUFFER_SIZE] = { 0 };
    size_t dataCount = 0;
    bool isAdded = false;

    // Fill the buffer
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        isAdded = cb_pushFront(&testBuffer, &inputData[i]);
        EXPECT_TRUE(isAdded) << "Failed to add data to buffer (unexpected return value).\n";
        EXPECT_EQ(i + 1, cb_getItemCount(&testBuffer)) << "Failed to add data to buffer (unexpected item count).\n";
    }

    // Check the data
    dataCount = cb_getBufferArray(&testBuffer, CB_FRONT_IDX, BUFFER_SIZE, outputData);
    std::reverse(inputData.begin(), inputData.end()); // cb_getBufferArray returns the element from the front to the back
    EXPECT_EQ(BUFFER_SIZE, dataCount);
    EXPECT_EQ(0, memcmp(inputData.data(), outputData, BUFFER_SIZE)) << "Added data mismatch.\n";

    // Add one more data
    isAdded = cb_pushFront(&testBuffer, &inputData[0]);
    dataCount = cb_getBufferArray(&testBuffer, CB_FRONT_IDX, BUFFER_SIZE, outputData);
    EXPECT_FALSE(isAdded);
    EXPECT_EQ(BUFFER_SIZE, dataCount);
    EXPECT_EQ(0, memcmp(inputData.data(), outputData, BUFFER_SIZE)) << "Buffer was modified.\n";
}

TEST_F(CircularBufferTest, PushFrontNullPointer)
{
    uint8_t dummy = 0;
    size_t dataCount = 0;
    bool isAdded = false;

    isAdded = cb_pushFront(NULL, NULL);
    EXPECT_FALSE(isAdded);

    isAdded = cb_pushFront(NULL, &dummy);
    EXPECT_FALSE(isAdded);

    isAdded = cb_pushFront(&testBuffer, NULL);
    EXPECT_FALSE(isAdded);
}

TEST_F(CircularBufferTest, PushFrontOverwrite)
{
    std::vector<uint8_t> inputData{ 10, 25, 37, 43, 59 };
    std::vector<uint8_t> reversedData(BUFFER_SIZE);
    uint8_t outputData[BUFFER_SIZE] = { 0 };
    uint8_t oldValue = 0;
    size_t dataCount = 0;
    bool isItemRemoved = false;

    // Fill the buffer
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        isItemRemoved = cb_pushFrontOverwrite(&testBuffer, &inputData[i], &oldValue);
        EXPECT_FALSE(isItemRemoved) << "Failed to add data to buffer (unexpected return value).\n";
        EXPECT_EQ(i + 1, cb_getItemCount(&testBuffer)) << "Failed to add data to buffer (unexpected item count).\n";
    }

    // Check the data
    dataCount = cb_getBufferArray(&testBuffer, CB_FRONT_IDX, BUFFER_SIZE, outputData);
    std::reverse_copy(inputData.begin(), inputData.end(), reversedData.begin()); // cb_getBufferArray returns the element from the front to the back
    EXPECT_EQ(BUFFER_SIZE, dataCount);
    EXPECT_EQ(0, memcmp(reversedData.data(), outputData, BUFFER_SIZE)) << "Added data mismatch.\n";

    // Add one more data
    isItemRemoved = cb_pushFrontOverwrite(&testBuffer, &inputData[0], &oldValue);
    dataCount = cb_getBufferArray(&testBuffer, CB_FRONT_IDX, BUFFER_SIZE, outputData);
    reversedData[0] = inputData[0]; // cb_pushFrontOverwrite overwrites the data at the front
    EXPECT_TRUE(isItemRemoved);
    EXPECT_EQ(BUFFER_SIZE, dataCount);
    EXPECT_EQ(inputData.back(), oldValue);
    EXPECT_EQ(0, memcmp(reversedData.data(), outputData, BUFFER_SIZE)) << "Added data mismatch after overwrite.\n";
}

TEST_F(CircularBufferTest, PushFrontOverwriteNullPointer)
{
    uint8_t dummy = 0;
    size_t dataCount = 0;
    bool isItemRemoved = false;

    isItemRemoved = cb_pushFrontOverwrite(NULL, NULL, NULL);
    EXPECT_FALSE(isItemRemoved);

    isItemRemoved = cb_pushFrontOverwrite(NULL, &dummy, NULL);
    EXPECT_FALSE(isItemRemoved);

    isItemRemoved = cb_pushFrontOverwrite(&testBuffer, NULL, NULL);
    EXPECT_FALSE(isItemRemoved);
    EXPECT_EQ(0, cb_getItemCount(&testBuffer));

    isItemRemoved = cb_pushFrontOverwrite(&testBuffer, &dummy, NULL);
    EXPECT_FALSE(isItemRemoved);
    EXPECT_EQ(1, cb_getItemCount(&testBuffer));
}

TEST_F(CircularBufferTest, PopBackEmpty)
{
    uint8_t dummy = 0;
    EXPECT_FALSE(cb_popBack(&testBuffer, &dummy));
}

TEST_F(CircularBufferTest, PopBack)
{
    std::vector<uint8_t> inputData{ 10, 25, 37 };
    uint8_t dummy = 0;

    // Add three data
    EXPECT_TRUE(cb_pushBack(&testBuffer, &inputData[0]));
    EXPECT_TRUE(cb_pushFront(&testBuffer, &inputData[1]));
    EXPECT_TRUE(cb_pushBack(&testBuffer, &inputData[2]));
    EXPECT_EQ(3, cb_getItemCount(&testBuffer));

    // Pop data form back
    EXPECT_TRUE(cb_popBack(&testBuffer, &dummy));
    EXPECT_EQ(inputData[2], dummy);
    EXPECT_EQ(2, cb_getItemCount(&testBuffer));

    EXPECT_TRUE(cb_popBack(&testBuffer, &dummy));
    EXPECT_EQ(inputData[0], dummy);
    EXPECT_EQ(1, cb_getItemCount(&testBuffer));

    EXPECT_TRUE(cb_popBack(&testBuffer, &dummy));
    EXPECT_EQ(inputData[1], dummy);
    EXPECT_EQ(0, cb_getItemCount(&testBuffer));
}

TEST_F(CircularBufferTest, PopBackNullPointer)
{
    uint8_t dummy = 5;

    // Add two data to the buffer
    EXPECT_TRUE(cb_pushBack(&testBuffer, &dummy));
    EXPECT_TRUE(cb_pushBack(&testBuffer, &dummy));
    EXPECT_EQ(2, cb_getItemCount(&testBuffer));

    // Remove them but pass a null pointer
    EXPECT_FALSE(cb_popBack(NULL, NULL));
    EXPECT_TRUE(cb_popBack(&testBuffer, NULL));
    EXPECT_EQ(1, cb_getItemCount(&testBuffer));
    EXPECT_TRUE(cb_popBack(&testBuffer, &dummy));
    EXPECT_EQ(5, dummy);
    EXPECT_EQ(0, cb_getItemCount(&testBuffer));
}
