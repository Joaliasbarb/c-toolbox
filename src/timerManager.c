#include "timerManager.h"

/*************************************************************************
 ********************* Local Type/Constant definitions *******************
 ************************************************************************/
typedef struct timer_t
{
    timerExpired_t callback;
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
static timerLockCb_t requestLock;
static bool isInitialized = false;

/*************************************************************************
 *********************** Local function declarations *********************
 ************************************************************************/
static timer_t* getFirstFreeTimer();
static uint32_t getCurrentTime();
static void initTimer(timer_t* const timer);

/*************************************************************************
 *********************** Public function definitions *********************
 ************************************************************************/
bool timerManager_init(timerLockCb_t lockCb)
{
    // Sanity check
    if((NULL == lockCb) || isInitialized)
    {
        return false;
    }

    requestLock = lockCb;
    return true;
}

bool timerManager_uninit()
{
    // Sanity check
    if(!isInitialized)
    {
        return false;
    }

    requestLock = NULL;
    isInitialized = false;
    return true;
}

void timerManager_run()
{
    uint32_t time = getCurrentTime();
    uint32_t elapsedTime = 0;

    if(!isInitialized)
    {
        return;
    }

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
                    timerInstancesArray[i].startTime = time;
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

timerHandle_t timerManager_createTimer(timerExpired_t callback)
{
    timer_t *newTimer = NULL;

    // Sanity check
    if((NULL == callback) || !isInitialized)
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

bool timerManager_deleteTimer(timerHandle_t* timer)
{
    timer_t *timerPointer = NULL;

    // Sanity check
    if((NULL == timer) || (NULL == *timer) || !isInitialized)
    {
        return false;
    }

    // Uninitialize the timer
    timerPointer = (timer_t*) *timer;
    initTimer(timerPointer);
    *timer = NULL;
    return true;
}

bool timerManager_startTimer(timerHandle_t timer, uint32_t tickCount, bool isPeriodic)
{
    timer_t *timerPointer = NULL;

    // Sanity check
    if((NULL == timer) || !isInitialized)
    {
        return false;
    }

    timerPointer = (timer_t*) timer;
    timerPointer->startTime = getCurrentTime();
    timerPointer->targetTime = tickCount;
    timerPointer->isStarted = true;
    timerPointer->isPeriodic = isPeriodic;
    return true;
}

bool timerManager_stopTimer(timerHandle_t timer)
{
    timer_t *timerPointer = NULL;

    // Sanity check
    if((NULL == timer) || !isInitialized)
    {
        return false;
    }

    timerPointer = (timer_t*) timer;
    timerPointer->isStarted = false;
    timerPointer->isPeriodic = false;
    return true;
}

void timerManager_incrementTimeBase()
{
    // Sanity check
    if(!isInitialized)
    {
        return;
    }

    // Increment time
    requestLock(true, false);
    currentTime++;
    requestLock(false, false);
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

    requestLock(true, true);
    time = currentTime;
    requestLock(false, true);

    return time;
}

static void initTimer(timer_t * const timer)
{
    timer->callback = NULL;
    timer->isPeriodic = false;
    timer->isStarted = false;
    timer->startTime = 0;
    timer->targetTime = 0;
}
