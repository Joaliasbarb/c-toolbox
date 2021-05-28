#include "timerManager.h"
#include "stm32f0xx.h"
#include "Firmware_param.h"

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
static timer_t timerInstancesArray[MAX_TIMER_COUNT] = {{.callback = NULL, .targetTime = 0, .startTime = 0, .isStarted = false, .isPeriodic = false}};
static volatile uint32_t currentTime = 0;

/*************************************************************************
 *********************** Local function declarations *********************
 ************************************************************************/
static timer_t* getFirstFreeTimer();
static uint32_t getCurrentTime();

/*************************************************************************
 *********************** Public function definitions *********************
 ************************************************************************/
void timerManager_init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_DeInit(TIM16);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    
    // Enable TIM16 Periph clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16 , ENABLE);
    
    // Time base configuration
    TIM_TimeBaseStructure.TIM_Prescaler = (1000-1); // 48MHz/1000 = 48kHz     
    TIM_TimeBaseStructure.TIM_Period = 480;         // 48kHz/48 = 100Hz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);
    
    // Configure the interrupt
    NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = TIMER_MANAGER_INTERRUPT_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // Enable the capture compare 1 interrupt
    TIM_ITConfig(TIM16, TIM_IT_CC1, ENABLE);
    TIM_Cmd(TIM16, ENABLE);
}

void timerManager_uninit()
{
    TIM_Cmd(TIM16, DISABLE);
    TIM_ITConfig(TIM16, TIM_IT_CC1, DISABLE);
    NVIC_DisableIRQ(TIM16_IRQn);
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
    timerPointer = (timer_t *) timer;
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
    
    timerPointer = (timer_t *) timer;
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
    
    timerPointer = (timer_t *) timer;
    timerPointer->isStarted = false;
    timerPointer->isPeriodic = false;
}
    
void TIM16_IRQHandler()
{
    if(TIM_GetITStatus(TIM16, TIM_IT_CC1) != RESET)
    {
        // Clear TIM16 Capture Compare1 interrupt pending bit
        TIM_ClearITPendingBit(TIM16, TIM_IT_CC1);
        
        // Increment time
        currentTime++;
    }
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
    
    NVIC_DisableIRQ(TIM3_IRQn);
    time = currentTime;
    NVIC_EnableIRQ(TIM3_IRQn);
    
    return time;
}