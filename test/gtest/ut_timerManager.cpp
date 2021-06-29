#include <gtest/gtest.h>
#include "timerManager.h"

class LockCallbackTestData
{
public:
    LockCallbackTestData(bool isLockRequestedTest, bool isInRunContextTest) :
        m_isLockRequestedTest{ isLockRequestedTest }, m_isInRunContextTest{ isInRunContextTest } {}

    bool m_isLockRequestedTest = false;
    bool m_isInRunContextTest = false;
};

static timerHandle_t expiredTimer = NULL;
static int timerExpiredCount = 0;
static std::vector<LockCallbackTestData> lockCallbackHistory;

static void addLockCallBackData(bool isLockRequested, bool isInRunContext)
{
    lockCallbackHistory.push_back(std::move(LockCallbackTestData{ isLockRequested , isInRunContext }));
}

extern "C" {
    static void timerCallback(timerHandle_t t)
    {
        expiredTimer = t;
        timerExpiredCount++;
    }

    static void lockCallback(bool isLockRequested, bool isInRunContext)
    {
        addLockCallBackData(isLockRequested, isInRunContext);
    }
}

class TimerManagerNoInitTest : public ::testing::Test
{
public:
    TimerManagerNoInitTest()
    {
        expiredTimer = NULL;
        timerExpiredCount = 0;
        lockCallbackHistory.clear();
    }

    virtual ~TimerManagerNoInitTest()
    {
    }
};

class TimerManagerTest : public TimerManagerNoInitTest
{
public:
    TimerManagerTest()
    {
        timerManager_init(lockCallback);
    }

    virtual ~TimerManagerTest()
    {
    }
};

TEST_F(TimerManagerNoInitTest, InitNullPointer)
{
    EXPECT_FALSE(timerManager_init(NULL));
}

TEST_F(TimerManagerNoInitTest, Init)
{
    EXPECT_TRUE(timerManager_init(lockCallback));
}

TEST_F(TimerManagerNoInitTest, InitTwice)
{
    EXPECT_TRUE(timerManager_init(lockCallback));
    EXPECT_FALSE(timerManager_init(lockCallback));
}

TEST_F(TimerManagerNoInitTest, Uninit)
{
    timerManager_init(lockCallback);
    EXPECT_TRUE(timerManager_uninit());
}

TEST_F(TimerManagerNoInitTest, UninitTwice)
{
    timerManager_init(lockCallback);
    EXPECT_TRUE(timerManager_uninit());
    EXPECT_FALSE(timerManager_uninit());
}

TEST_F(TimerManagerNoInitTest, FunctionCallsNoInit)
{
    timerHandle_t timer = NULL;

    timerManager_run();
    EXPECT_EQ(0, lockCallbackHistory.size());
    EXPECT_TRUE(NULL == timerManager_createTimer(timerCallback));
    EXPECT_FALSE(timerManager_incrementTimeBase());
    EXPECT_FALSE(timerManager_uninit());

    // Call init to be able to create a timer and uninitialize the layer
    ASSERT_TRUE(timerManager_init(lockCallback));
    timer = timerManager_createTimer(timerCallback);
    ASSERT_TRUE(NULL != timer);
    ASSERT_TRUE(timerManager_uninit());

    EXPECT_FALSE(timerManager_stopTimer(timer));
    EXPECT_FALSE(timerManager_deleteTimer(&timer));
}

TEST_F(TimerManagerTest, RunLockCallbackCalled)
{
    timerManager_run();
    EXPECT_EQ(2, lockCallbackHistory.size());
    EXPECT_TRUE(lockCallbackHistory.at(0).m_isInRunContextTest);
    EXPECT_TRUE(lockCallbackHistory.at(0).m_isLockRequestedTest);
    EXPECT_TRUE(lockCallbackHistory.at(1).m_isInRunContextTest);
    EXPECT_FALSE(lockCallbackHistory.at(1).m_isLockRequestedTest);
}

TEST_F(TimerManagerTest, CreateTimerNullPointer)
{
    EXPECT_TRUE(NULL == timerManager_createTimer(NULL));
}

TEST_F(TimerManagerTest, CreateTimer)
{
    EXPECT_TRUE(NULL != timerManager_createTimer(timerCallback));
}

TEST_F(TimerManagerTest, CreateTimerTooMuch)
{
    std::vector<timerHandle_t> timers{ MAX_TIMER_COUNT , NULL };
    timerHandle_t extraTimer = NULL;

    for(size_t i = 0; i < MAX_TIMER_COUNT; i++)
    {
        timers.at(i) = timerManager_createTimer(timerCallback);
        EXPECT_TRUE(NULL != timers.at(i));
    }

    extraTimer = timerManager_createTimer(timerCallback);
    EXPECT_TRUE(NULL == extraTimer);
}

TEST_F(TimerManagerTest, DeleteTimerNullPointer)
{
    timerHandle_t timer = NULL;

    EXPECT_FALSE(timerManager_deleteTimer(NULL));
    EXPECT_FALSE(timerManager_deleteTimer(&timer));
}

TEST_F(TimerManagerTest, DeleteTimer)
{
    timerHandle_t timer = NULL;

    timer = timerManager_createTimer(timerCallback);
    ASSERT_TRUE(NULL != timer);

    EXPECT_TRUE(timerManager_deleteTimer(&timer));
    EXPECT_TRUE(NULL == timer);
}

TEST_F(TimerManagerTest, StartTimerNullPointer)
{
    EXPECT_FALSE(timerManager_startTimer(NULL, 20, false));
}

TEST_F(TimerManagerTest, StartTimerOnePeriodic)
{
    constexpr int tickCount = 5;
    timerHandle_t timer = NULL;

    timer = timerManager_createTimer(timerCallback);
    EXPECT_TRUE(timer != NULL);
    EXPECT_TRUE(timerManager_startTimer(timer, tickCount, true));

    // Increment the time tick but don't call the run function
    for(size_t i = 0; i < tickCount; i++)
    {
        timerManager_incrementTimeBase();
    }
    EXPECT_EQ(0, timerExpiredCount);
    EXPECT_TRUE(NULL == expiredTimer);

    // Now call the run function and verify that the callback was called
    timerManager_run();
    EXPECT_EQ(1, timerExpiredCount);
    EXPECT_TRUE(timer == expiredTimer);
    expiredTimer = NULL;

    // Repeat the same thing
    for(size_t i = 0; i < tickCount; i++)
    {
        timerManager_incrementTimeBase();
    }
    EXPECT_EQ(1, timerExpiredCount);
    EXPECT_TRUE(NULL == expiredTimer);

    timerManager_run();
    EXPECT_EQ(2, timerExpiredCount);
    EXPECT_TRUE(timer == expiredTimer);
}

TEST_F(TimerManagerTest, StartTimerTwoPeriodic)
{
    constexpr int tickCountTimer1 = 5;
    constexpr int tickCountTimer2 = 4;
    timerHandle_t timer1 = NULL;
    timerHandle_t timer2 = NULL;

    timer1 = timerManager_createTimer(timerCallback);
    timer2 = timerManager_createTimer(timerCallback);
    EXPECT_TRUE(timer1 != NULL);
    EXPECT_TRUE(timer2 != NULL);
    EXPECT_TRUE(timerManager_startTimer(timer1, tickCountTimer1, true));
    EXPECT_TRUE(timerManager_startTimer(timer2, tickCountTimer2, true));

    for(size_t i = 0; i < 4; i++)
    {
        timerManager_incrementTimeBase();
    }
    timerManager_run();
    EXPECT_EQ(1, timerExpiredCount);
    EXPECT_TRUE(timer2 == expiredTimer);
    expiredTimer = NULL;

    timerManager_incrementTimeBase();
    timerManager_run();
    EXPECT_EQ(2, timerExpiredCount);
    EXPECT_TRUE(timer1 == expiredTimer);
    expiredTimer = NULL;

    for(size_t i = 0; i < 3; i++)
    {
        timerManager_incrementTimeBase();
    }
    timerManager_run();
    EXPECT_EQ(3, timerExpiredCount);
    EXPECT_TRUE(timer2 == expiredTimer);
    expiredTimer = NULL;

    for(size_t i = 0; i < 2; i++)
    {
        timerManager_incrementTimeBase();
    }
    timerManager_run();
    EXPECT_EQ(4, timerExpiredCount);
    EXPECT_TRUE(timer1 == expiredTimer);
}

TEST_F(TimerManagerTest, StartTimerOneShot)
{
    constexpr int tickCount = 5;
    timerHandle_t timer = NULL;

    timer = timerManager_createTimer(timerCallback);
    EXPECT_TRUE(timer != NULL);
    EXPECT_TRUE(timerManager_startTimer(timer, tickCount, false));

    for(size_t i = 0; i < tickCount; i++)
    {
        timerManager_incrementTimeBase();
    }
    timerManager_run();
    EXPECT_EQ(1, timerExpiredCount);
    EXPECT_TRUE(timer == expiredTimer);
    expiredTimer = NULL;

    for(size_t i = 0; i < tickCount; i++)
    {
        timerManager_incrementTimeBase();
    }
    timerManager_run();
    EXPECT_EQ(1, timerExpiredCount);
    EXPECT_TRUE(NULL == expiredTimer);
}

TEST_F(TimerManagerTest, StopTimerNullPointer)
{
    EXPECT_FALSE(timerManager_stopTimer(NULL));
}

TEST_F(TimerManagerTest, StopTimer)
{
    constexpr int tickCount = 5;
    timerHandle_t timer = NULL;

    timer = timerManager_createTimer(timerCallback);
    ASSERT_TRUE(timer != NULL);
    ASSERT_TRUE(timerManager_startTimer(timer, tickCount, false));
    EXPECT_TRUE(timerManager_stopTimer(timer));

    for(size_t i = 0; i < tickCount; i++)
    {
        timerManager_incrementTimeBase();
    }
    timerManager_run();
    EXPECT_EQ(0, timerExpiredCount);
    EXPECT_TRUE(NULL == expiredTimer);
}

TEST_F(TimerManagerTest, IncrementTimeBaseLockCallbackCalled)
{
    EXPECT_TRUE(timerManager_incrementTimeBase());
    EXPECT_EQ(2, lockCallbackHistory.size());
    EXPECT_FALSE(lockCallbackHistory.at(0).m_isInRunContextTest);
    EXPECT_TRUE(lockCallbackHistory.at(0).m_isLockRequestedTest);
    EXPECT_FALSE(lockCallbackHistory.at(1).m_isInRunContextTest);
    EXPECT_FALSE(lockCallbackHistory.at(1).m_isLockRequestedTest);
}