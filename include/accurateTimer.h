#ifdef __cplusplus
extern "C" {
#endif

#ifndef ACCURATE_TIMER_H_
#define ACCURATE_TIMER_H_

#include <stdint.h>
#include <stdbool.h>

/*************************************************************************
 ******************** Public Type/Constant definitions *******************
 ************************************************************************/
 #define MAX_ACCURATE_TIMER_COUNT 5
 
typedef void* accurateTimerHandle_t;

typedef struct
{
    void (*initFunc)();
    void (*uninitFunc)();
} accurateTimerConfig_t;

/*************************************************************************
 *********************** Public function declaration *********************
 ************************************************************************/

/************************* Function Description *************************/
/**
 * @details accurateTimer_init  Initialize the accurateTimer layer.
 * @param [in] config   A pointer to the config structure.
 * @return true if the initialization is successful, false otherwise.
 */
/************************************************************************/
bool accurateTimer_init(const accurateTimerConfig_t * const config);

/************************* Function Description *************************/
/**
 * @details accurateTimer_uninit    Uninitialize the accurateTimer layer.
 * @return true if the uninitialization is successful, false otherwise.
 */
/************************************************************************/
bool accurateTimer_uninit();

/************************* Function Description *************************/
/**
 * @details accurateTimer_createTimer   Ask for a free instance of timer.
 * @param [in] callback A pointer to the function to call when the timer has expired.
 *      WARNING: The callback is called in the same context as the function calling accurateTimer_incrementTimeBase() !
 *
 * @return A timer instance if there's one free, NULL otherwise.
 */
/************************************************************************/
accurateTimerHandle_t accurateTimer_createTimer(void (*callback)(accurateTimerHandle_t timerHandle));

/************************* Function Description *************************/
/**
 * @details accurateTimer_deleteTimer   Delete a timer. If the call is successful, the timer handle is set to NULL.
 * @param [in] timer    A pointer to the timer to delete.
 * @return true if the timer was successfuly deleted.
 */
/************************************************************************/
bool accurateTimer_deleteTimer(accurateTimerHandle_t *timer);

/************************* Function Description *************************/
/**
 * @details accurateTimer_startTimer    Start a timer. This function can be called
 *      even if the timer is already started. In that case, the timer will be restarted.
 * @param [in] timer    The timer to start.
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

#ifdef __cplusplus
}
#endif
