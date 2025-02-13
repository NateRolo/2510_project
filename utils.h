/*
 * Author: Arsh M, Nathan O
 * Date: Feb 11, 2025
 * Purpose: Utility functions for general use across the hospital management system.
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
