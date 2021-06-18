#include <gtest/gtest.h>
#include "circularBuffer.h"

class CircularBufferTest : public ::testing::Test {
protected:
    void SetUp() override {
        cb_initStatic(&testBuffer, testBufferArray, 5, sizeof(*testBufferArray));
    }

    void TearDown() override {

    }

    uint8_t testBufferArray[5];
    circularBuffer_t testBuffer;
};

TEST_F(CircularBufferTest, IsEmptyInitially) {
    EXPECT_EQ(cb_getItemCount(&testBuffer), 0) << "Buffer not empty after initialization !";
}
