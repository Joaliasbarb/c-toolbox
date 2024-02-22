/*******************************************************************************
* Copyright 2021 Joakim Nicolet (joakimnicolet@gmail.com)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* - The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*******************************************************************************/
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
    isInitialized = true;
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
    uint32_t time = 0;
    uint32_t elapsedTime = 0;

    if(!isInitialized)
    {
        return;
    }

    time = getCurrentTime();
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

bool timerManager_incrementTimeBase()
{
    // Sanity check
    if(!isInitialized)
    {
        return false;
    }

    // Increment time
    requestLock(true, false);
    currentTime++;
    requestLock(false, false);
    return true;
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
