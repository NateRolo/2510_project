/*
 * Author: Arsh M, Nathan O
 * Date: 2/6/2025
 * Purpose: This file implements functions for managing patient records in a hospital system.
 */

#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "utils.h"

// Function prototypes for internal (static) functions
static int getPatientName(char patientName[]);
static int getPatientAge(int *patientAge);
static int getPatientDiagnosis(char patientDiagnosis[]);
static int getRoomNumber(int *roomNumber);
static Patient createNewPatient(const char patientName[],
                                int patientAge,
                                const char patientDiagnosis[],
                                int roomNumber);
static void printPatientInfo(const Patient *patient);
static int getPatientIndexForDischarge();
static int confirmDischarge(int patientIndex);
static void removePatientFromSystem(int index);
static int validatePatientName(char patientName[]);
static int validatePatientAge(int patientAge);
static int validatePatientDiagnosis(char patientDiagnosis[]);
static int validateRoomNumber(int roomNumber);
static int patientExists(int id);
static int checkRoomOccupancy(int roomNumber);

// Array to store patient records
Patient patients[MAX_PATIENT_CAPACITY];

// Tracks total number of patients in the system
int totalPatients = IS_EMPTY;

// Counter for assigning unique patient IDs
int patientIDCounter = DEFAULT_ID;

/*
 * Function: addPatientRecord
 * --------------------------
 * Adds a new patient record to the system after validating input fields.
 */
void addPatientRecord()
{
    if (totalPatients >= MAX_PATIENT_CAPACITY)
    {
        printf("Max patient capacity reached!\n");
        return;
    }

    char patientName[MAX_PATIENT_NAME_LENGTH];
    int patientAge;
    char patientDiagnosis[MAX_DIAGNOSIS_LENGTH];
    int roomNumber;

    // Get and validate patient details
    if (getPatientName(patientName) == IS_NOT_VALID)
    {
        return;
    }

    if (getPatientAge(&patientAge) == IS_NOT_VALID)
    {
        return;
    }

    if (getPatientDiagnosis(patientDiagnosis) == IS_NOT_VALID)
    {
        return;
    }

    if (getRoomNumber(&roomNumber) == IS_NOT_VALID)
    {
        return;
    }

    // Create and store new patient record
    Patient newPatient = createNewPatient(patientName, 
                                          patientAge, 
                                          patientDiagnosis, 
                                          roomNumber);
    patients[totalPatients] = newPatient;
    totalPatients++;
    patientIDCounter++;

    printf("--- Patient Added ---\n");
    printPatientInfo(&patients[totalPatients - 1]);
}

/*
 * Function: viewPatientRecords
 * ----------------------------
 * Displays all patient records stored in the system.
 */
void viewPatientRecords()
{
    if (totalPatients == IS_EMPTY)
    {
        printf("No Patients Admitted...\n");
        return;
    }

    for (int i = 0; i < MAX_PATIENT_CAPACITY; i++)
    {
        if (patients[i].patientId != INVALID_ID)
        {
            printPatientInfo(&patients[i]);
        }
    }
}

/*
 * Function: searchPatientById
 * ---------------------------
 * Searches for a patient by ID and displays their details if found.
 */
void searchPatientById()
{
    int id, index;

    if (totalPatients == IS_EMPTY)
    {
        printf("No Patients Admitted...\n");
        return;
    }

    printf("Enter A Patient Id: ");
    scanf("%d", &id);
    clearInputBuffer();

    index = patientExists(id);

    if (index == PATIENT_NOT_FOUND)
    {
        printf("Patient does not exist!\n");
    }
    else
    {
        printPatientInfo(&patients[index]);
    }
}

/*
 * Function: dischargePatient
 * --------------------------
 * Removes a patient from the system if they exist and discharge is confirmed.
 */
void dischargePatient()
{
    if (totalPatients == IS_EMPTY)
    {
        printf("No patients to discharge!\n");
        return;
    }

    int index = getPatientIndexForDischarge();

    if (index == PATIENT_NOT_FOUND)
    {
        printf("Patient is not in system.\n");
        return;
    }

    if (confirmDischarge(index))
    {
        removePatientFromSystem(index);
        printf("Patient has been discharged!\n");
    }
    else
    {
        printf("Patient discharge cancelled.\n");
    }
}

/*
 * Function: getPatientName
 * ------------------------
 * Reads and validates the patient’s name from user input.
 */
static int getPatientName(char patientName[])
{
    printf("Enter Patient Name:\n");
    fgets(patientName, MAX_PATIENT_NAME_LENGTH, stdin);
    patientName[strcspn(patientName, "\n")] = NULL_TERMINATOR;

    return validatePatientName(patientName);
}

/*
 * Function: getPatientAge
 * -----------------------
 * Reads and validates the patient’s age from user input.
 */
static int getPatientAge(int *patientAge)
{
    printf("Enter Patient Age:\n");
    scanf("%d", patientAge);
    clearInputBuffer();

    return validatePatientAge(*patientAge);
}

/*
 * Function: getPatientDiagnosis
 * -----------------------------
 * Reads and validates the patient’s diagnosis from user input.
 */
static int getPatientDiagnosis(char patientDiagnosis[])
{
    printf("Enter Patient Diagnosis:\n");
    fgets(patientDiagnosis, MAX_DIAGNOSIS_LENGTH, stdin);
    patientDiagnosis[strcspn(patientDiagnosis, "\n")] = NULL_TERMINATOR;

    return validatePatientDiagnosis(patientDiagnosis);
}

/*
 * Function: getRoomNumber
 * -----------------------
 * Reads and validates the room number for the patient.
 */
static int getRoomNumber(int *roomNumber)
{
    printf("Enter Patient Room:\n");
    scanf("%d", roomNumber);
    clearInputBuffer();

    return validateRoomNumber(*roomNumber);
}

/*
 * Function: createNewPatient
 * --------------------------
 * Creates a new patient record with given details.
 */
static Patient createNewPatient(const char patientName[], 
                                int patientAge,
                                const char patientDiagnosis[], 
                                int roomNumber)
{
    Patient newPatient;
    newPatient.patientId = patientIDCounter;
    strcpy(newPatient.name, patientName);
    newPatient.ageInYears = patientAge;
    strcpy(newPatient.diagnosis, patientDiagnosis);
    newPatient.roomNumber = roomNumber;
    return newPatient;
}

/*
 * Function: getPatientIndexForDischarge
 * -------------------------------------
 * Prompts user for a patient ID and returns their index in the system.
 */
static int getPatientIndexForDischarge()
{
    int patientId;
    printf("Enter ID of patient to discharge:\n");
    scanf("%d", &patientId);
    clearInputBuffer();
    return patientExists(patientId);
}

/*
 * Function: confirmDischarge
 * --------------------------
 * Asks the user to confirm the discharge of a patient.
 */
static int confirmDischarge(int patientIndex)
{
    char confirm;
    printf("Patient ID: %d\n", patients[patientIndex].patientId);
    printf("Patient Name: %s\n", patients[patientIndex].name);
    printf("Are you sure you want to discharge this patient? (y/n)\n");
    scanf("%c", &confirm);
    clearInputBuffer();
    return confirm == 'y';
}

/*
 * Function: removePatientFromSystem
 * ---------------------------------
 * Removes a patient from the system by shifting array elements.
 */
static void removePatientFromSystem(int index)
{
    for (int i = index; i < REMOVE_PATIENT_ARRAY_MAX; i++)
    {
        patients[i] = patients[i + NEXT_INDEX_OFFSET];
    }
    totalPatients--;
}

/*
 * Function: patientExists
 * -----------------------
 * Checks if a patient with a given ID exists and returns their index.
 */
static int patientExists(int id)
{
    for (int i = 0; i < MAX_PATIENT_CAPACITY; i++)
    {
        if (patients[i].patientId == id)
        {
            return i;
        }
    }
    return PATIENT_NOT_FOUND;
}

/*
 * Function: checkRoomOccupancy
 * ----------------------------
 * Checks if a room is currently occupied by any patient.
 */
static int checkRoomOccupancy(int roomNumber)
{
    for (int i = 0; i <= MAX_ROOM_NUMBER; i++)
    {
        if (patients[i].roomNumber == roomNumber)
        {
            return i;
        }
    }
    return -1;
}

/*
 * Function: printPatientInfo
 * --------------------------
 * Displays detailed information about a patient.
 */
static void printPatientInfo(const Patient *patient)
{
    printf("---------------------------------------\n");
    printf("Patient ID: %d\n", patient->patientId);
    printf("Patient Name: %s\n", patient->name);
    printf("Age: %d\n", patient->ageInYears);
    printf("Diagnosis: %s\n", patient->diagnosis);
    printf("Room Number: %d\n", patient->roomNumber);
    printf("---------------------------------------\n");
}
