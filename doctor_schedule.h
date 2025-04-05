/*
 * Author: Arsh M, Nathan O
 * Date: 2/13/2025
 * Purpose: This file contains the definition of the doctor scheduling system.
 *          It provides functionality for assigning doctors to specific time slots
 *          and displaying the complete weekly schedule.
 */

#ifndef SCHEDULE_H
#define SCHEDULE_H

/*
 * Function: initializeSchedule
 * ----------------------------
 * Initializes the weekly schedule from file or with empty slots if file doesn't exist
 */
void initializeSchedule(void);

/*
 * Function: initializeScheduleDefault
 * ----------------------------------
 * Initializes the weekly schedule with empty slots (used when file reading fails)
 */
void initializeScheduleDefault(void);

/*
 * Function: assignDoctor
 * ---------------------
 * Assigns a doctor to work at a time during the week and updates the schedule file
 */
void assignDoctor(void);

/*
 * Function: printFullSchedule
 * --------------------------
 * Displays the full doctor schedule with days, times, and assigned doctors
 */
void printFullSchedule(void);

/*
 * Function: printDoctorUtilizationReport
 * --------------------------------------
 * Calculates and prints a report detailing the number of shifts covered by each doctor.
 * Displays the report on the console and writes it to the "doctor_utilization_report.txt" file.
 */
void printDoctorUtilizationReport();

#endif // SCHEDULE_H
