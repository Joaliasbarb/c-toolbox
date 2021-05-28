#include <stdbool.h>
#include <stdio.h>

#include "accurateTimer.h"
#include "hw_timer0.h"

/*************************************************************************
 ********************* Local Type/Constant definitions *******************
 ************************************************************************/
#define MAX_TIMER_CALLBACKS 5

typedef struct accurateTimer_t
{
    void (*callback)();
    uint32_t targetTime;
    uint32_t startTime;
    bool isStarted;
    bool isPeriodic;
} accurateTimer_t;

/*************************************************************************
 *********************** Local variables declarations ********************
 ************************************************************************/
static accurateTimer_t timerInstancesArray[MAX_TIMER_CALLBACKS] = { {.callback = NULL, .targetTime = 0, .startTime = 0, .isStarted = false,
        .isPeriodic = false}};
static uint32_t currentTime = 0;
static bool isInitialized = false;

/*************************************************************************
 *********************** Local function declarations *********************
 ************************************************************************/
static accurateTimer_t* getFirstFreeTimer();
static void timer0InterruptCallback();

/*************************************************************************
 *********************** Public function definitions *********************
 ************************************************************************/
void accurateTimer_init()
{
    if(isInitialized)
    {
        return;
    }

    // Configure timer 0 to generate interrupt at 16 kHz
    hw_timer0_init(NULL);
    hw_timer0_set_clock_source(HW_TIMER0_CLK_SRC_FAST); // Select base clock of 16 MHz
    hw_timer0_set_pwm_mode(HW_TIMER0_MODE_PWM);
    hw_timer0_set_t0_reload(499, 499); // f = (16 MHz)/(M+1)+(N+1) ==> f = (16*10^6) / (1000) = 16 kHz
    hw_timer0_set_on_clock_div(false);
    hw_timer0_set_on_reload(550); // Generate the interrupt only when M and N equal to 0
    hw_timer0_register_int(timer0InterruptCallback);

    // Start the timer 0
    hw_timer0_enable();
    isInitialized = true;
}

void accurateTimer_uninit()
{
    if(!isInitialized)
    {
        return;
    }

    hw_timer0_unregister_int();
    hw_timer0_disable();
    isInitialized = false;
}

accurateTimerHandle_t accurateTimer_createTimer(void (*callback)(accurateTimerHandle_t timerHandle))
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

void accurateTimer_deleteTimer(accurateTimerHandle_t *timer)
{
    accurateTimer_t *timerPointer = NULL;

    // Sanity check
    if(NULL == *timer)
    {
        return;
    }

    // Uninitialize the timer
    timerPointer = (accurateTimer_t *) *timer;
    timerPointer->isStarted = false;
    timerPointer->callback = NULL;
    timerPointer = NULL;
}

void accurateTimer_startTimer(accurateTimerHandle_t timer, uint32_t targetTime, bool isPeriodic)
{
    accurateTimer_t *timerPointer = NULL;

    // Sanity check
    if(NULL == timer)
    {
        return;
    }

    timerPointer = (accurateTimer_t *) timer;
    timerPointer->startTime = currentTime;
    timerPointer->targetTime = targetTime;
    timerPointer->isStarted = true;
    timerPointer->isPeriodic = isPeriodic;
}

void accurateTimer_stopTimer(accurateTimerHandle_t timer)
{
    accurateTimer_t *timerPointer = NULL;

    // Sanity check
    if(NULL == timer)
    {
        return;
    }

    timerPointer = (accurateTimer_t *) timer;
    timerPointer->isStarted = false;
    timerPointer->isPeriodic = false;
}

/*************************************************************************
 *********************** Local function definitions **********************
 ************************************************************************/
static accurateTimer_t* getFirstFreeTimer()
{
    for(size_t i = 0; i < MAX_TIMER_CALLBACKS; i++)
    {
        if(NULL == timerInstancesArray[i].callback)
        {
            return &timerInstancesArray[i];
        }
    }

    return NULL;
}

static void timer0InterruptCallback()
{
    uint32_t elapsedTime = 0;

    // Increase time counter
    currentTime++;

    // Iterate through all started timers
    for(size_t i = 0; i < MAX_TIMER_CALLBACKS; i++)
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
                    (*timerInstancesArray[i].callback)();
                }
            }
        }
    }
}
