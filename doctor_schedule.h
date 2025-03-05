/*
 * Author: Arsh M, Nathan O
 * Date: 2/13/2025
 * Purpose: This file contains the definition of the doctor scheduling system.
 *          It provides functionality for assigning doctors to specific time slots
 *          and displaying the complete weekly schedule.
 */

#ifndef SHCEDULE_H
#define SCHEDULE_H

/*
 * Function: initializeSchedule
 * ----------------------------
 * Initializes the weekly schedule with empty slots
 */
void initializeSchedule(void);

/*
 * Function: assignDoctor
 * ----------------------------
 * Assigns a doctor to work at a time during the week
 */
void assignDoctor(void);

/*
 * Function: printFullSchedule
 * ----------------------------
 * Displays the full doctor schedule with days, times, and assigned doctors
 */
void printFullSchedule(void);

#endif // SCHEDULE_H
