#ifndef DOCTOR_H
#define DOCTOR_H

/*
 * Constants used throughout the doctor scheduling system.
 * Defines values for input validation, scheduling dimensions, and status codes.
 */
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
