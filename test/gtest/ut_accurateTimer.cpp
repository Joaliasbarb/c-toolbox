#include <gtest/gtest.h>
#include "accurateTimer.h"

static accurateTimerHandle_t expiredTimer = NULL;
static int timerExpiredCount = 0;

extern "C" {
    static void timerCallback(accurateTimerHandle_t t)
    { 
        expiredTimer = t;
        timerExpiredCount++;
    }
}

class AccurateTimerNoInitTest : public ::testing::Test
{
public:
    AccurateTimerNoInitTest()
    {
        expiredTimer = NULL;
        timerExpiredCount = 0;
    }
};

class AccurateTimerTest : public AccurateTimerNoInitTest
{
public:
    AccurateTimerTest()
    {
        accurateTimer_init();
    }

    virtual ~AccurateTimerTest()
    {
        accurateTimer_uninit();
    }
};

TEST_F(AccurateTimerNoInitTest, InitTwice)
{
    EXPECT_TRUE(accurateTimer_init());
    EXPECT_FALSE(accurateTimer_init());
}

TEST_F(AccurateTimerNoInitTest, Uninit)
{
    EXPECT_TRUE(accurateTimer_init());
    EXPECT_TRUE(accurateTimer_uninit());
}

TEST_F(AccurateTimerNoInitTest, UninitTwice)
{
    EXPECT_TRUE(accurateTimer_init());
    EXPECT_TRUE(accurateTimer_uninit());
    EXPECT_FALSE(accurateTimer_uninit());
}

TEST_F(AccurateTimerTest, UninitShouldDeleteAllTimers)
{
    std::vector<accurateTimerHandle_t> timers{ MAX_ACCURATE_TIMER_COUNT , NULL };
    accurateTimerHandle_t extraTimer = NULL;

    for(size_t i = 0; i < MAX_ACCURATE_TIMER_COUNT; i++)
    {
        timers.at(i) = accurateTimer_createTimer(timerCallback);
        ASSERT_TRUE(NULL != timers.at(i));
    }

    EXPECT_TRUE(accurateTimer_uninit());
    EXPECT_TRUE(accurateTimer_init());
    extraTimer = accurateTimer_createTimer(timerCallback);
    ASSERT_TRUE(NULL != extraTimer);
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

TEST_F(AccurateTimerTest, StartTimerNullPointer)
{
    EXPECT_FALSE(accurateTimer_startTimer(NULL, 20, false));
}

TEST_F(AccurateTimerTest, StartTimerOnePeriodic)
{
    constexpr int tickCount = 5;
    accurateTimerHandle_t timer = NULL;

    timer = accurateTimer_createTimer(timerCallback);
    EXPECT_TRUE(timer != NULL);
    EXPECT_TRUE(accurateTimer_startTimer(timer, tickCount, true));

    for(size_t i = 0; i < tickCount; i++)
    {
        EXPECT_EQ(0, timerExpiredCount);
        EXPECT_TRUE(NULL == expiredTimer);
        accurateTimer_incrementTimeBase();
    }

    EXPECT_EQ(1, timerExpiredCount);
    EXPECT_TRUE(timer == expiredTimer);
    expiredTimer = NULL;

    for(size_t i = 0; i < tickCount; i++)
    {
        EXPECT_EQ(1, timerExpiredCount);
        EXPECT_TRUE(NULL == expiredTimer);
        accurateTimer_incrementTimeBase();
    }

    EXPECT_EQ(2, timerExpiredCount);
    EXPECT_TRUE(timer == expiredTimer);
}

TEST_F(AccurateTimerTest, StartTimerTwoPeriodic)
{
    constexpr int tickCountTimer1 = 5;
    constexpr int tickCountTimer2 = 4;
    accurateTimerHandle_t timer1 = NULL;
    accurateTimerHandle_t timer2 = NULL;

    timer1 = accurateTimer_createTimer(timerCallback);
    timer2 = accurateTimer_createTimer(timerCallback);
    EXPECT_TRUE(timer1 != NULL);
    EXPECT_TRUE(timer2 != NULL);
    EXPECT_TRUE(accurateTimer_startTimer(timer1, tickCountTimer1, true));
    EXPECT_TRUE(accurateTimer_startTimer(timer2, tickCountTimer2, true));

    for(size_t i = 0; i < 4; i++)
    {
        EXPECT_EQ(0, timerExpiredCount);
        EXPECT_TRUE(NULL == expiredTimer);
        accurateTimer_incrementTimeBase();
    }

    EXPECT_EQ(1, timerExpiredCount);
    EXPECT_TRUE(timer2 == expiredTimer);
    expiredTimer = NULL;

    for(size_t i = 0; i < 1; i++)
    {
        EXPECT_EQ(1, timerExpiredCount);
        EXPECT_TRUE(NULL == expiredTimer);
        accurateTimer_incrementTimeBase();
    }

    EXPECT_EQ(2, timerExpiredCount);
    EXPECT_TRUE(timer1 == expiredTimer);
    expiredTimer = NULL;

    for(size_t i = 0; i < 3; i++)
    {
        EXPECT_EQ(2, timerExpiredCount);
        EXPECT_TRUE(NULL == expiredTimer);
        accurateTimer_incrementTimeBase();
    }

    EXPECT_EQ(3, timerExpiredCount);
    EXPECT_TRUE(timer2 == expiredTimer);
    expiredTimer = NULL;

    for(size_t i = 0; i < 2; i++)
    {
        EXPECT_EQ(3, timerExpiredCount);
        EXPECT_TRUE(NULL == expiredTimer);
        accurateTimer_incrementTimeBase();
    }

    EXPECT_EQ(4, timerExpiredCount);
    EXPECT_TRUE(timer1 == expiredTimer);
}

TEST_F(AccurateTimerTest, StartTimerOneShot)
{
    constexpr int tickCount = 5;
    accurateTimerHandle_t timer = NULL;

    timer = accurateTimer_createTimer(timerCallback);
    EXPECT_TRUE(timer != NULL);
    EXPECT_TRUE(accurateTimer_startTimer(timer, tickCount, false));

    for(size_t i = 0; i < tickCount; i++)
    {
        EXPECT_EQ(0, timerExpiredCount);
        EXPECT_TRUE(NULL == expiredTimer);
        accurateTimer_incrementTimeBase();
    }

    EXPECT_EQ(1, timerExpiredCount);
    EXPECT_TRUE(timer == expiredTimer);
    expiredTimer = NULL;

    for(size_t i = 0; i < tickCount; i++)
    {
        EXPECT_EQ(1, timerExpiredCount);
        EXPECT_TRUE(NULL == expiredTimer);
        accurateTimer_incrementTimeBase();
    }

    EXPECT_EQ(1, timerExpiredCount);
    EXPECT_TRUE(NULL == expiredTimer);
}

TEST_F(AccurateTimerTest, StopTimerNullPointer)
{
    EXPECT_FALSE(accurateTimer_stopTimer(NULL));
}

TEST_F(AccurateTimerTest, StopTimer)
{
    constexpr int tickCount = 5;
    accurateTimerHandle_t timer = NULL;

    timer = accurateTimer_createTimer(timerCallback);
    ASSERT_TRUE(timer != NULL);
    ASSERT_TRUE(accurateTimer_startTimer(timer, tickCount, false));
    EXPECT_TRUE(accurateTimer_stopTimer(timer));

    for(size_t i = 0; i < tickCount; i++)
    {
        EXPECT_EQ(0, timerExpiredCount);
        EXPECT_TRUE(NULL == expiredTimer);
        accurateTimer_incrementTimeBase();
    }

    EXPECT_EQ(0, timerExpiredCount);
    EXPECT_TRUE(NULL == expiredTimer);
}