/*
 * Author: Arsh M, Nathan O
 * Date: Feb 11,2025
 * Purpose: Utility functions for general use across the hospital management system.
 */

#include <stdio.h>
#include "utils.h"

/*
 * Function: clearInputBuffer
 * --------------------------
 * Clears the input buffer to prevent issues caused by leftover newline characters
 * after using `scanf()`. This ensures correct handling of user input.
 */
void clearInputBuffer()
{
    while (getchar() != '\n'); // Consume characters until a newline is found
}
