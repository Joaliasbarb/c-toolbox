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
* - The above copyright noticeand this permission notice shall be included in
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

/*************************************************************************
 *********************** Local function declarations *********************
 ************************************************************************/
static accurateTimer_t* getFirstFreeTimer();
static void initTimer(accurateTimer_t * const timer);

/*************************************************************************
 *********************** Public function definitions *********************
 ************************************************************************/

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
    initTimer(timerPointer);
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

bool accurateTimer_incrementTimeBase()
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
    return true;
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

static void initTimer(accurateTimer_t * const timer)
{
    timer->callback = NULL;
    timer->isPeriodic = false;
    timer->isStarted = false;
    timer->startTime = 0;
    timer->targetTime = 0;
}
