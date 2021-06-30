#ifdef __cplusplus
extern "C" {
#endif

#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*************************************************************************
 ******************** Public Type/Constant definitions *******************
 ************************************************************************/
#define MAX_TIMER_COUNT    10

typedef void* timerHandle_t;
typedef void (*timerExpired_t)(timerHandle_t timerHandle);
typedef void (*timerLockCb_t)(bool isLockRequested, bool isInRunContext);

/*************************************************************************
 *************************** Macros definitions **************************
 ************************************************************************/

/*************************************************************************
 ********************** Global variables declaration *********************
 ************************************************************************/

/*************************************************************************
 *********************** Public function declaration *********************
 ************************************************************************/

/************************* Function Description *************************/
/**
 * @details timerManager_init   Initialize the timeManager layer. This function shall be
 *      called before any other functions in this layer.
 * @param [in] lockCb   A pointer to a function which shall implement a locking mechanism
 *      to avoid concurrency on the internal tick counter. The concurrency is due to the timerManager_run
 *      and timerManager_incrementTimeBase functions accessing the internal tick counter variable in a 
 *      potentialy different context.
 * @return true if the initialization is successful, false otherwise.
 */
/************************************************************************/
bool timerManager_init(timerLockCb_t lockCb);

/************************* Function Description *************************/
/**
 * @details timerManager_uninit Uninitialize the timeManager layer. This function doesn't delete
 *      any timer and shall be called only at the end of the program execution.
 * @return true if the uninitialization is successful, false otherwise.
 */
/************************************************************************/
bool timerManager_uninit();

/************************* Function Description *************************/
/**
 * @details timerManager_run    Main function of the timerManager layer. This function checks if a
        timer expired and call it's callback function if it did. Therefore, it shall be called regularly.
 */
/************************************************************************/
void timerManager_run();

/************************* Function Description *************************/
/**
 * @details timerManager_createTimer    Ask for a free instance of timer.
 * @param [in] callback A pointer to the function to call when the timer has expired.
 *
 * @return A timer instance if there's one free, NULL otherwise.
 */
/************************************************************************/
timerHandle_t timerManager_createTimer(timerExpired_t callback);

/************************* Function Description *************************/
/**
 * @details timerManager_deleteTimer    Delete a timer. If the call is successful, the timer handle is set to NULL.
 * @param [in] timer    A pointer to the timer to delete.
 * @return true if the timer is successfuly deleted, false otherwise.
 */
/************************************************************************/
bool timerManager_deleteTimer(timerHandle_t *timer);

/************************* Function Description *************************/
/**
 * @details timerManager_startTimer Start a timer. This function can be called even if the timer is already started.
 *      In that case, the timer will be restarted.
 * @param [in] tickCount    The number of ticks after which the timer shall expire.
 * @param [in] isPeriodic   Indicates whether the timer shall expire once (false) or periodically (true).
 * @return true if the timer is successfuly started, false otherwise.
 */
/************************************************************************/
bool timerManager_startTimer(timerHandle_t timer, uint32_t tickCount, bool isPeriodic);

/************************* Function Description *************************/
/**
 * @details timerManager_stopTimer  Stop a timer.
 * @param [in] timer    The timer to stop.
 * @return true if the timer is successfuly stopped, false otherwise.
 */
/************************************************************************/
bool timerManager_stopTimer(timerHandle_t timer);

/************************* Function Description *************************/
/**
 * @details timerManager_incrementTimeBase  Increments the internal tick counter. This function shall
 *      be called at regular intervals so that a tick represent a fixed time span.
 * @return true if the internal tick counter is successfuly incremented, false otherwise.
 */
 /************************************************************************/
bool timerManager_incrementTimeBase();

#endif

#ifdef __cplusplus
}
#endif
