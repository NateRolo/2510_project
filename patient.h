/*
 * Author: Arsh M, Nathan O
 * Date: Feb 6, 2025
 * Purpose: This file defines a structure for representing a patient in a hospital system, 
 *          along with necessary macros and function prototypes for patient management.
 */

#ifndef HOSPITAL_PATIENT_H
#define HOSPTAL_PATIENT_H

#define MAX_PATIENT_CAPACITY 50

#define MAX_ROOM_NUMBER 50
#define MIN_ROOM_NUMBER 1

#define MIN_PATIENT_NAME_LENGTH 1
#define MAX_PATIENT_NAME_LENGTH 100

#define MIN_DIAGNOSIS_LENGTH 1
#define MAX_DIAGNOSIS_LENGTH 255

#define MIN_ROOM_NUMBER 1
#define MAX_ROOM_NUMBER 50

#define MIN_AGE_YEARS 0
#define MAX_AGE_YEARS 120

#define PATIENT_NOT_FOUND -1

#define DEFAULT_ID 1
#define INVALID_ID 0

#define NULL_TERMINATOR 0

#define REMOVE_PATIENT_ARRAY_MAX 49
#define NEXT_INDEX_OFFSET 1

#define ROOM_UNOCCUPIED -1

#define NUMBER_ZERO 0
#define NUMBER_NINE 9

#define NO_LETTERS 0
#define HAS_LETTERS 1

#define IS_EMPTY 0

/*
 * Struct: Patient
 * ----------------
 * Represents a patient in the hospital system, storing basic details
 * such as ID, name, age, diagnosis, and assigned room number.
 */
typedef struct
{
    int patientId;                           
    char name[MAX_PATIENT_NAME_LENGTH];      
    int ageInYears;                                 
    char diagnosis[MAX_DIAGNOSIS_LENGTH];    
    int roomNumber;                          
} Patient;

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
