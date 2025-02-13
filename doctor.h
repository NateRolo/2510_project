/*
 * Author: Arsh M, Nathan O
 * Date: Feb 12, 2025
 * Purpose: This file contains the definition of the doctor scheduling system.
 *          It provides functionality for assigning doctors to specific time slots
 *          and displaying the complete weekly schedule.
 */

#ifndef DOCTOR_H
#define DOCTOR_H

/*
 * Function: assignDoctor
 * ----------------------------
 * Assigns a doctor to work at a time during the week
 */
void assignDoctor();

/*
 * Function: printFullSchedule
 * ----------------------------
 * Displays the full doctor schedule with days, times, and assigned doctors
 */
void printFullSchedule();

#endif // DOCTOR_H
