#include "timerManager.h"

/*************************************************************************
 ********************* Local Type/Constant definitions *******************
 ************************************************************************/
typedef struct timer_t
{
    void (*callback)();
    uint32_t targetTime;
    uint32_t startTime;
    bool isStarted;
    bool isPeriodic;
} timer_t;

/*************************************************************************
 *********************** Local variables declarations ********************
 ************************************************************************/
static timer_t timerInstancesArray[MAX_TIMER_COUNT] = { {.callback = NULL, .targetTime = 0, .startTime = 0, .isStarted = false, .isPeriodic = false}};
static volatile uint32_t currentTime = 0;
static timerConfig_t cfg = {0};

/*************************************************************************
 *********************** Local function declarations *********************
 ************************************************************************/
static timer_t* getFirstFreeTimer();
static uint32_t getCurrentTime();

/*************************************************************************
 *********************** Public function definitions *********************
 ************************************************************************/
void timerManager_init(const timerConfig_t *const config)
{
    cfg = *config;

    if(NULL != cfg.initFunc)
    {
        cfg.initFunc();
    }
}

void timerManager_uninit()
{
    if(NULL == cfg.uninitFunc)
    {
        return;
    }

    cfg.uninitFunc();
    cfg.initFunc = NULL;
    cfg.uninitFunc = NULL;
    cfg.setInterrupt = NULL;
}

void timerManager_run()
{
    uint32_t time = getCurrentTime();
    uint32_t elapsedTime = 0;

    // Iterate through all started timers
    for(size_t i = 0; i < MAX_TIMER_COUNT; i++)
    {
        if(timerInstancesArray[i].isStarted)
        {
            // Calculate the elapsed time
            if(time < timerInstancesArray[i].startTime)
            {
                elapsedTime = time + (UINT32_MAX - timerInstancesArray[i].startTime) + 1;
            }
            else
            {
                elapsedTime = time - timerInstancesArray[i].startTime;
            }

            // Check if the timer has expired
            if(elapsedTime >= timerInstancesArray[i].targetTime)
            {
                if(timerInstancesArray[i].isPeriodic)
                {
                    timerInstancesArray[i].startTime = getCurrentTime();
                }
                else
                {
                    timerInstancesArray[i].isStarted = false;
                }
                (*timerInstancesArray[i].callback)(&timerInstancesArray[i]);
            }
        }
    }
}

timerHandle_t timerManager_createTimer(void (*callback)(timerHandle_t))
{
    timer_t *newTimer = NULL;

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

    return (timerHandle_t) newTimer;
}

void timerManager_deleteTimer(timerHandle_t timer)
{
    timer_t *timerPointer = NULL;

    // Sanity check
    if(NULL == timer)
    {
        return;
    }

    // Uninitialize the timer
    timerPointer = (timer_t*) timer;
    timerPointer->callback = NULL;
    timerPointer->isStarted = false;
}

void timerManager_startTimer(timerHandle_t timer, uint32_t targetTime, bool isPeriodic)
{
    timer_t *timerPointer = NULL;

    // Sanity check
    if(NULL == timer)
    {
        return;
    }

    timerPointer = (timer_t*) timer;
    timerPointer->startTime = getCurrentTime();
    timerPointer->targetTime = targetTime;
    timerPointer->isStarted = true;
    timerPointer->isPeriodic = isPeriodic;
}

void timerManager_stopTimer(timerHandle_t timer)
{
    timer_t *timerPointer = NULL;

    // Sanity check
    if(NULL == timer)
    {
        return;
    }

    timerPointer = (timer_t*) timer;
    timerPointer->isStarted = false;
    timerPointer->isPeriodic = false;
}

void timerManager_incrementTimeBase()
{
    // Increment time
    currentTime++;
}

/*************************************************************************
 *********************** Local function definitions **********************
 ************************************************************************/
static timer_t* getFirstFreeTimer()
{
    for(size_t i = 0; i < MAX_TIMER_COUNT; i++)
    {
        if(NULL == timerInstancesArray[i].callback)
        {
            return &timerInstancesArray[i];
        }
    }

    return NULL;
}

static uint32_t getCurrentTime()
{
    uint32_t time = 0;

    cfg.setInterrupt(false);
    time = currentTime;
    cfg.setInterrupt(true);

    return time;
}
