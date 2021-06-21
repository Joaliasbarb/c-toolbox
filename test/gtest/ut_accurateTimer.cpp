#include <gtest/gtest.h>
#include "accurateTimer.h"

static bool isInitCallbackCalled = false;
static bool isUninitCallbackCalled = false;

extern "C" {
    static void initCallbackWrapper() { isInitCallbackCalled = true; }
    static void uninitCallbackWrapper() { isUninitCallbackCalled = true; }
}

class AccurateTimerNoInitTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        isInitCallbackCalled = false;
        isUninitCallbackCalled = false;
    }
    void TearDown() override {}
};

class AccurateTimerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        accurateTimerConfig_t cfg = { 0 };
        accurateTimer_init(&cfg);
    }

    void TearDown() override
    {
        accurateTimer_uninit();
    }
};

TEST_F(AccurateTimerNoInitTest, InitNullPointer)
{
    EXPECT_FALSE(accurateTimer_init(NULL));
}

TEST_F(AccurateTimerNoInitTest, InitNoCallback)
{
    accurateTimerConfig_t cfg = { 0 };
    EXPECT_TRUE(accurateTimer_init(&cfg));
    EXPECT_FALSE(isInitCallbackCalled);
}

TEST_F(AccurateTimerNoInitTest, InitCallback)
{
    accurateTimerConfig_t cfg = { 0 };
    cfg.initFunc = initCallbackWrapper;
    EXPECT_TRUE(accurateTimer_init(&cfg));
    EXPECT_TRUE(isInitCallbackCalled);
    EXPECT_FALSE(accurateTimer_init(&cfg));
}

TEST_F(AccurateTimerNoInitTest, UninitNoCallback)
{
    accurateTimerConfig_t cfg = { 0 };
    EXPECT_TRUE(accurateTimer_init(&cfg));
    EXPECT_TRUE(accurateTimer_uninit());
    EXPECT_FALSE(isUninitCallbackCalled);
}

TEST_F(AccurateTimerNoInitTest, UninitCallback)
{
    accurateTimerConfig_t cfg = { 0 };
    cfg.uninitFunc = uninitCallbackWrapper;
    EXPECT_TRUE(accurateTimer_init(&cfg));
    EXPECT_TRUE(accurateTimer_uninit());
    EXPECT_TRUE(isUninitCallbackCalled);
    EXPECT_FALSE(accurateTimer_uninit());
}