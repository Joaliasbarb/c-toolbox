#ifndef __TIMER_MANAGER_H_
#define __TIMER_MANAGER_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*************************************************************************
 ******************** Public Type/Constant definitions *******************
 ************************************************************************/
#define MAX_TIMER_COUNT    10

typedef void* timerHandle_t;

typedef struct
{
    void (*setInterrupt)(bool isEnable);
    void (*initFunc)();
    void (*uninitFunc)();
} timerConfig_t;

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
 * @details timerManager_init   Initialize the timeManager layer.
 * @param [in] config   A pointer to the config structure.
 */
/************************************************************************/
void timerManager_init(const timerConfig_t * const config);

/************************* Function Description *************************/
/**
 * @details timerManager_uninit Uninitialize the timeManager layer.
 */
/************************************************************************/
void timerManager_uninit();

/************************* Function Description *************************/
/**
 * @details timerManager_run    Main function of the timerManager layer.
 *                              Shall be called from the main loop.
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
timerHandle_t timerManager_createTimer(void (*callback)(timerHandle_t));

/************************* Function Description *************************/
/**
 * @details timerManager_deleteTimer    Delete a used timer.
 * @param [in] timer    The timer to delete.
 */
/************************************************************************/
void timerManager_deleteTimer(timerHandle_t timer);

/************************* Function Description *************************/
/**
 * @details timerManager_startTimer Start a timer. This function can be called even if the timer is already started.
                                    In that case, the timer will be restarted.
 * @param [in] targetTime   The time in [1/100s] after wich the timer shall expire.
 * @param [in] isPeriodic   Indicates whether the timer shall expire once (False) or periodically (True).
 */
/************************************************************************/
void timerManager_startTimer(timerHandle_t timer, uint32_t targetTime, bool isPeriodic);

/************************* Function Description *************************/
/**
 * @details timerManager_stopTimer  Stop a timer.
 * @param [in] timer    The timer to stop.
 */
/************************************************************************/
void timerManager_stopTimer(timerHandle_t timer);

/************************* Function Description *************************/
/**
 * @details timerManager_incrementTimeBase  This function shall be call regularly every 10 ms.
 */
/************************************************************************/
void timerManager_incrementTimeBase();

#endif
