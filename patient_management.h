/*
 * Author: Arsh M, Nathan O
 * Date: Feb 6, 2025
 * Purpose: This file defines functions for managing patient records in a hospital system.
 */

#ifndef PATIENT_MANAGEMENT_H
#define PATIENT_MANAGEMENT_H
#include "patient_data.h"
#include <stdio.h>

typedef struct PatientNode
{
    Patient data;
    struct PatientNode *nextNode;
} PatientNode;

typedef struct DischargedPatient {
    Patient patient;
    time_t dischargeDate;  // Time of discharge
} DischargedPatient;

/*
 * Function: initializePatientSystem
 * --------------------------------
 * Initializes the patient management system by attempting to load existing patient records
 * from patients.dat. 
 */
void initializePatientSystem(void);

/*
 * Function: initializePatientSystemDefault
 * ----------------------------------------
 * Initializes the patient management system with default settings.
 * This function can be used when no custom configuration is needed.
 */
void initializePatientSystemDefault(void);

/*
 * Function: addPatientRecord
 * --------------------------
 * Adds a new patient record to the system.
 */
void addPatientRecord(void);

/*
 * Function: viewPatientRecords
 * ----------------------------
 * Displays all patient records currently stored in the system.
 */
void viewPatientRecords(void);

/*
 * Function: searchPatientById
 * ---------------------------
 * Searches for a patient record using their unique ID.
 */
void searchPatientById(void);

/*
 * Function: dischargePatient
 * --------------------------
 * Removes a patient from the system once they are discharged.
 */
void dischargePatient(void);

/*
 * Function: backupPatientSystem
 * -----------------------------
 * Saves all current patient records to a file for backup purposes.
 */
void backupPatientSystem(void);

/*
 * Function: restoreDataFromFile
 * -----------------------------
 * Restores patient records from a previously backed-up file.
 */
void restoreDataFromFile(void);

/*
 * Function: clearMemory
 * ---------------------
 * Frees all dynamically allocated memory used for storing patient records.
 */
void clearMemory();

/*
 * Function: printList
 * -------------------
 * Iterates through the patient linked list and prints each patient's details.
 */
void printList(PatientNode *head);

/*
 * Function: displayPatientReport
 * ------------------------------
 * Displays and logs a report of admitted patients for a given timeframe.
 *
 * choice: Timeframe (1: Daily, 2: Weekly, 3: Monthly).
 */
void displayPatientReport(int choice);

/*
 * Function: displayDischargedPatientReport
 * ----------------------------------------
 * Displays and logs a report of discharged patients for a given timeframe.
 *
 * choice: Timeframe (1: Daily, 2: Weekly, 3: Monthly).
 */
void displayDischargedPatientReport(int choice);

/*
 * Function: displayRoomUsageReport
 * --------------------------------
 * Displays a report summarizing room usage based on "room_usage.txt".
 */
void displayRoomUsageReport(void);

/*
 * Function: printFormattedReport
 * ------------------------------
 * Helper to print a patient report (admission/discharge) to console and file.
 *
 * file: Output file stream.
 * header: Report title.
 * result: Total patient count for the report.
 * timeframe: Timeframe used for filtering patient details.
 */
void printFormattedReport(FILE *file, const char *header, int result, int timeframe);


#endif // PATIENT_MANAGEMENT_H 