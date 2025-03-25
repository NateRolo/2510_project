/*
 * Author: Arsh M, Nathan O
 * Date: Feb 6, 2025
 * Purpose: This file defines the patient data structure and functions for
 *          creating, validating, and displaying patient information.
 */

#ifndef PATIENT_DATA_H
#define PATIENT_DATA_H

// Constants for patient data
#define MAX_PATIENT_NAME_LENGTH 100
#define MAX_DIAGNOSIS_LENGTH 255

/*
 * Structure representing a patient in the system.
 * Contains identifying information and medical details.
 */
typedef struct
{
    int patientId;
    char name[MAX_PATIENT_NAME_LENGTH];
    int ageInYears;
    char diagnosis[MAX_DIAGNOSIS_LENGTH];
    int roomNumber;
} Patient;

/*
 * Function: createPatient
 * -----------------------
 * Creates a new patient record with the given details.
 * 
 * patientName: The name of the patient
 * patientAge: The age of the patient in years
 * patientDiagnosis: The medical diagnosis
 * roomNumber: The assigned room number
 * patientId: The unique identifier for the patient
 * 
 * Returns: A new Patient structure with the provided information
 */
Patient createPatient(const char patientName[], 
                      int patientAge,
                      const char patientDiagnosis[], 
                      int roomNumber,
                      int patientId);

/*
 * Function: validatePatientName
 * ----------------------------
 * Validates if a patient name is acceptable.
 * 
 * patientName: The name to validate
 * 
 * Returns: 1 if valid, 0 if invalid
 */
int validatePatientName(char patientName[]);

/*
 * Function: validatePatientAge
 * ---------------------------
 * Validates if a patient age is within acceptable range.
 * 
 * patientAge: The age to validate
 * 
 * Returns: 1 if valid, 0 if invalid
 */
int validatePatientAge(int patientAge);

/*
 * Function: validatePatientDiagnosis
 * ---------------------------------
 * Validates if a patient diagnosis is acceptable.
 * 
 * patientDiagnosis: The diagnosis to validate
 * 
 * Returns: 1 if valid, 0 if invalid
 */
int validatePatientDiagnosis(char patientDiagnosis[]);

/*
 * Function: validateRoomNumber
 * ---------------------------
 * Validates if a room number is within acceptable range.
 * 
 * roomNumber: The room number to validate
 * 
 * Returns: 1 if valid, 0 if invalid
 */
int validateRoomNumber(int roomNumber);

/*
 * Function: printPatient
 * ---------------------
 * Displays detailed information about a patient.
 * 
 * patient: Pointer to the patient to display
 */
void printPatient(const Patient patient);

/*
 * Function: isRoomOccupied
 * -----------------------
 * Checks if a room is currently occupied.
 * 
 * roomNumber: The room number to check
 * patients: Array of patients to check against
 * maxPatients: Size of the patients array
 * 
 * Returns: Index of patient occupying the room, or -1 if unoccupied
 */
int isRoomOccupied(int roomNumber, const Patient patients[], int maxPatients);

#endif // PATIENT_DATA_H
