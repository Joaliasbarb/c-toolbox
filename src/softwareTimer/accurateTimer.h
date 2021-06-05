#ifndef ACCURATE_TIMER_H_
#define ACCURATE_TIMER_H_

#include <stdint.h>
#include <stdbool.h>

/*************************************************************************
 ******************** Public Type/Constant definitions *******************
 ************************************************************************/
 #define MAX_TIMER_COUNT 5
 
typedef void* accurateTimerHandle_t;

typedef struct
{
    void (*initFunc)();
    void (*uninitFunc)();
} timerConfig_t;

/*************************************************************************
 *********************** Public function declaration *********************
 ************************************************************************/

/************************* Function Description *************************/
/**
 * @details accurateTimer_init  Initialize the timer16kHz layer.
 * @param [in] config   A pointer to the config structure.
 */
/************************************************************************/
void accurateTimer_init(const timerConfig_t * const config);

/************************* Function Description *************************/
/**
 * @details accurateTimer_uninit    Uninitialize the timer16kHz layer.
 */
/************************************************************************/
void accurateTimer_uninit();

/************************* Function Description *************************/
/**
 * @details accurateTimer_createTimer   Ask for a free instance of timer.
 * @param [in] callback A pointer to the function to call when the timer has expired.
 *      WARNING: The callback is called in an interrupt context !
 *
 * @return A timer instance if there's one free, NULL otherwise.
 */
/************************************************************************/
accurateTimerHandle_t accurateTimer_createTimer(void (*callback)(accurateTimerHandle_t timerHandle));

/************************* Function Description *************************/
/**
 * @details accurateTimer_deleteTimer   Delete a used timer.
 * @param [in] timer    A pointer to the timer to delete.
 */
/************************************************************************/
void accurateTimer_deleteTimer(accurateTimerHandle_t *timer);

/************************* Function Description *************************/
/**
 * @details accurateTimer_startTimer    Start a timer. This function can be called
 *      even if the timer is already started. In that case, the timer will be restarted.
 * @param [in] targetTime   The time in 1/16000s after which the timer shall expire.
 * @param [in] isPeriodic   Indicates whether the timer shall expire once (False) or periodically (True).
 */
/************************************************************************/
void accurateTimer_startTimer(accurateTimerHandle_t timer, uint32_t targetTime, bool isPeriodic);

/************************* Function Description *************************/
/**
 * @details accurateTimer_stopTimer Stop a timer.
 * @param [in] timer    The timer to stop.
 */
/************************************************************************/
void accurateTimer_stopTimer(accurateTimerHandle_t timer);

/************************* Function Description *************************/
/**
 * @details accurateTimer_incrementTimeBase This function shall be call regularly at 16kHz.
 */
/************************************************************************/
void accurateTimer_incrementTimeBase();

#endif
