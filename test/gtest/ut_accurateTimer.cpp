#include <gtest/gtest.h>
#include "accurateTimer.h"

static bool isInitCallbackCalled = false;
static bool isUninitCallbackCalled = false;

extern "C" {
    static void initCallback() { isInitCallbackCalled = true; }
    static void uninitCallback() { isUninitCallbackCalled = true; }
    static void timerCallback(accurateTimerHandle_t t) {}
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
    cfg.initFunc = initCallback;
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
    cfg.uninitFunc = uninitCallback;
    EXPECT_TRUE(accurateTimer_init(&cfg));
    EXPECT_TRUE(accurateTimer_uninit());
    EXPECT_TRUE(isUninitCallbackCalled);
    EXPECT_FALSE(accurateTimer_uninit());
}

TEST_F(AccurateTimerTest, CreateTimerNullPointer)
{
    EXPECT_TRUE(NULL == accurateTimer_createTimer(NULL));
}

TEST_F(AccurateTimerTest, CreateTimer)
{
    EXPECT_TRUE(NULL != accurateTimer_createTimer(timerCallback));
}

TEST_F(AccurateTimerTest, CreateTimerTooMuch)
{
    std::vector<accurateTimerHandle_t> timers{ MAX_ACCURATE_TIMER_COUNT , NULL};
    accurateTimerHandle_t extraTimer = NULL;

    for(size_t i = 0; i < MAX_ACCURATE_TIMER_COUNT; i++)
    {
        timers.at(i) = accurateTimer_createTimer(timerCallback);
        EXPECT_TRUE(NULL != timers.at(i));
    }

    extraTimer = accurateTimer_createTimer(timerCallback);
    EXPECT_TRUE(NULL == extraTimer);
}

TEST_F(AccurateTimerTest, DeleteTimerNullPointer)
{
    accurateTimerHandle_t timer = NULL;

    EXPECT_FALSE(accurateTimer_deleteTimer(NULL));
    EXPECT_FALSE(accurateTimer_deleteTimer(&timer));
}

TEST_F(AccurateTimerTest, DeleteTimer)
{
    accurateTimerHandle_t timer = NULL;

    timer = accurateTimer_createTimer(timerCallback);
    ASSERT_TRUE(NULL != timer);

    EXPECT_TRUE(accurateTimer_deleteTimer(&timer));
    EXPECT_TRUE(NULL == timer);
}