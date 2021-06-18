#ifdef __cplusplus
extern "C" {
#endif

#ifndef __QUICK_SORT_H_
#define __QUICK_SORT_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*************************************************************************
 ******************** Public Type/Constant definitions *******************
 ************************************************************************/

/*************************************************************************
 *********************** Public function declaration *********************
 ************************************************************************/
void quicksort(void *array, size_t length, size_t size, int(*compare)(const void *, const void *));

#endif

#ifdef __cplusplus
}
#endif
