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
typedef void (*accurateTimerExpired_t)(accurateTimerHandle_t timerHandle);

/*************************************************************************
 *********************** Public function declaration *********************
 ************************************************************************/

/************************* Function Description *************************/
/**
 * @details accurateTimer_createTimer   Ask for a free instance of timer.
 * @param [in] callback A callback function called when the timer expires.
 *      WARNING: The callback is called in the same context as the function calling accurateTimer_incrementTimeBase() !
 *
 * @return A timer instance if successful, NULL otherwise.
 */
/************************************************************************/
accurateTimerHandle_t accurateTimer_createTimer(accurateTimerExpired_t callback);

/************************* Function Description *************************/
/**
 * @details accurateTimer_deleteTimer   Delete a timer. If the call is successful, the timer handle is set to NULL.
 * @param [in] timer    A pointer to the timer to delete.
 * @return true if the timer is successfuly deleted, false otherwise.
 */
/************************************************************************/
bool accurateTimer_deleteTimer(accurateTimerHandle_t *timer);

/************************* Function Description *************************/
/**
 * @details accurateTimer_startTimer    Start a timer. This function can be called
 *      even if the timer is already started. In that case, the timer will be restarted.
 * @param [in] timer    The timer to start.
 * @param [in] tickCount    The number of ticks after which the timer shall expire.
 * @param [in] isPeriodic   Indicates whether the timer shall expire once (False) or periodically (True).
 * @return true if the timer is successfuly started, false otherwise.
 */
/************************************************************************/
bool accurateTimer_startTimer(accurateTimerHandle_t timer, uint32_t tickCount, bool isPeriodic);

/************************* Function Description *************************/
/**
 * @details accurateTimer_stopTimer Stop a timer.
 * @param [in] timer    The timer to stop.
 * @return true if the timer is successfuly stopped, false otherwise.
 */
/************************************************************************/
bool accurateTimer_stopTimer(accurateTimerHandle_t timer);

/************************* Function Description *************************/
/**
 * @details accurateTimer_incrementTimeBase Increments the internal tick counter. This function shall
 *      be called at regular intervals so that a tick represent a fixed time span.
 * @return true if the internal tick counter is successfuly incremented, false otherwise.
 */
/************************************************************************/
bool accurateTimer_incrementTimeBase();

#endif

#ifdef __cplusplus
}
#endif
