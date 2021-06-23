#include <stdbool.h>
#include <stdio.h>

#include "accurateTimer.h"

/*************************************************************************
 ********************* Local Type/Constant definitions *******************
 ************************************************************************/
typedef struct accurateTimer_t
{
    accurateTimerExpired_t callback;
    uint32_t targetTime;
    uint32_t startTime;
    bool isStarted;
    bool isPeriodic;
} accurateTimer_t;

/*************************************************************************
 *********************** Local variables declarations ********************
 ************************************************************************/
static accurateTimer_t timerInstancesArray[MAX_ACCURATE_TIMER_COUNT] = { {.callback = NULL, .targetTime = 0, .startTime = 0, .isStarted = false,
        .isPeriodic = false}};
static uint32_t currentTime = 0;
static bool isInitialized = false;
static accurateTimerConfig_t cfg = {0};

/*************************************************************************
 *********************** Local function declarations *********************
 ************************************************************************/
static accurateTimer_t* getFirstFreeTimer();

/*************************************************************************
 *********************** Public function definitions *********************
 ************************************************************************/
bool accurateTimer_init(const accurateTimerConfig_t * const config)
{
    if((NULL == config) || isInitialized)
    {
        return false;
    }
    
    cfg = *config;

    if(NULL != cfg.initFunc)
    {
        cfg.initFunc();
    }

    isInitialized = true;
    return true;
}

bool accurateTimer_uninit()
{
    if(!isInitialized)
    {
        return false;
    }

    if(NULL != cfg.uninitFunc)
    {
        cfg.uninitFunc();
    }

    cfg.initFunc = NULL;
    cfg.uninitFunc = NULL;
    isInitialized = false;
    return true;
}

accurateTimerHandle_t accurateTimer_createTimer(accurateTimerExpired_t callback)
{
    accurateTimer_t *newTimer = NULL;

    // Sanity check
    if(NULL == callback)
    {
        return NULL;
    }

    // Check if there's a free timer
    newTimer = getFirstFreeTimer();
    if(NULL == newTimer)
    {
        return NULL;
    }

    // Initialize the timer
    newTimer->callback = callback;
    newTimer->isStarted = false;
    newTimer->isPeriodic = false;

    return (accurateTimerHandle_t) newTimer;
}

bool accurateTimer_deleteTimer(accurateTimerHandle_t *timer)
{
    accurateTimer_t *timerPointer = NULL;

    // Sanity check
    if((NULL == timer) || (NULL == *timer))
    {
        return false;
    }

    // Uninitialize the timer
    timerPointer = (accurateTimer_t *) *timer;
    timerPointer->isStarted = false;
    timerPointer->callback = NULL;
    *timer = NULL;
    return true;
}

bool accurateTimer_startTimer(accurateTimerHandle_t timer, uint32_t targetTime, bool isPeriodic)
{
    accurateTimer_t *timerPointer = NULL;

    // Sanity check
    if(NULL == timer)
    {
        return false;
    }

    timerPointer = (accurateTimer_t *) timer;
    timerPointer->startTime = currentTime;
    timerPointer->targetTime = targetTime;
    timerPointer->isStarted = true;
    timerPointer->isPeriodic = isPeriodic;
    return true;
}

bool accurateTimer_stopTimer(accurateTimerHandle_t timer)
{
    accurateTimer_t *timerPointer = NULL;

    // Sanity check
    if(NULL == timer)
    {
        return false;
    }

    timerPointer = (accurateTimer_t *) timer;
    timerPointer->isStarted = false;
    timerPointer->isPeriodic = false;
    return true;
}

void accurateTimer_incrementTimeBase()
{
    uint32_t elapsedTime = 0;

    // Increase time counter
    currentTime++;

    // Iterate through all started timers
    for(size_t i = 0; i < MAX_ACCURATE_TIMER_COUNT; i++)
    {
        if(timerInstancesArray[i].isStarted)
        {
            // Calculate the elapsed time
            if(currentTime < timerInstancesArray[i].startTime)
            {
                elapsedTime = currentTime + (UINT32_MAX - timerInstancesArray[i].startTime) + 1;
            }
            else
            {
                elapsedTime = currentTime - timerInstancesArray[i].startTime;
            }

            // Check if the timer has expired
            if(elapsedTime >= timerInstancesArray[i].targetTime)
            {
                if(timerInstancesArray[i].isPeriodic)
                {
                    timerInstancesArray[i].startTime = currentTime;
                }
                else
                {
                    timerInstancesArray[i].isStarted = false;
                }

                // Call the callback if not NULL
                if(NULL != timerInstancesArray[i].callback)
                {
                    (*timerInstancesArray[i].callback)(&timerInstancesArray[i]);
                }
            }
        }
    }
}

/*************************************************************************
 *********************** Local function definitions **********************
 ************************************************************************/
static accurateTimer_t* getFirstFreeTimer()
{
    for(size_t i = 0; i < MAX_ACCURATE_TIMER_COUNT; i++)
    {
        if(NULL == timerInstancesArray[i].callback)
        {
            return &timerInstancesArray[i];
        }
    }

    return NULL;
}
