/*
 * Author: Arsh M, Nathan O
 * Date: Feb 12, 2025
 * Purpose: This file contains the definition of the doctor scheduling system.
 *          It provides functionality for assigning doctors to specific time slots
 *          and displaying the complete weekly schedule.
 */

#ifndef DOCTOR_H
#define DOCTOR_H

#define INVALID_INPUT (-1)
#define DAYS_IN_WEEK 7
#define TIMES_OF_DAY 3
#define DOCTOR_COUNT 3
#define NAME_LENGTH 100
#define UNASSIGNED_ID 0
#define MIN_INDEX 0

#define NO_DOCTOR 0

#define RAYMOND_ID 10
#define GEORGE_ID 20
#define SOFIA_ID 30

#define RAYMOND_AGE 44
#define GEORGE_AGE 67
#define SOFIA_AGE 33


void assignDoctor();
void printFullSchedule();

#endif // DOCTOR_H
