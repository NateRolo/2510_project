/*
 * Author: Arsh M, Nathan O
 * Date: Feb 6, 2025
 * Purpose: This file defines a structure for representing a patient in a hospital system, 
 *          along with necessary macros and function prototypes for patient management.
 */

#ifndef HOSPITAL_PATIENT_H
#define HOSPITAL_PATIENT_H

// Function prototypes for patient management

/*
 * Function: addPatientRecord
 * --------------------------
 * Adds a new patient record to the system.
 */
void addPatientRecord();

/*
 * Function: viewPatientRecords
 * ----------------------------
 * Displays all patient records currently stored in the system.
 */
void viewPatientRecords();

/*
 * Function: searchPatientById
 * ---------------------------
 * Searches for a patient record using their unique ID.
 */
void searchPatientById();

/*
 * Function: dischargePatient
 * --------------------------
 * Removes a patient from the system once they are discharged.
 */
void dischargePatient();

#endif // HOSPITAL_PATIENT_H
