/*
 * File: utils.h
 * -------------
 * This header file provides utility functions for input handling.
 */

#ifndef UTILS_H
#define UTILS_H

#define IS_NOT_VALID 0
#define IS_VALID 1

#define SUCCESSFUL_READ 1

#define YES 'y'
#define NO 'n'


/*
 * Function: clearInputBuffer
 * --------------------------
 * Clears the input buffer to remove any leftover characters,
 * especially useful after using scanf to prevent unexpected input behavior.
 */
void clearInputBuffer();

#endif // UTILS_H
