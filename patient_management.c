/*
 * Author: Arsh M, Nathan O
 * Date: Feb 6, 2025
 * Purpose: This file implements functions for managing patient records in a hospital system.
 */

#include "patient_management.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "patient_data.h"
#include "utils.h"

// Private constants
#define INITIAL_CAPACITY 1
#define IS_EMPTY 0
#define DEFAULT_ID 1

static const int PATIENT_NOT_FOUND        = -1;
static const int INVALID_ID               = 0;
static const int REMOVE_PATIENT_ARRAY_MAX = 49;
static const int NEXT_INDEX_OFFSET        = 1;
static const int ROOM_UNOCCUPIED          = -1;

// Global patient data
static Patient *patients;
static int     totalPatients    = IS_EMPTY;
static int     patientIDCounter = DEFAULT_ID;
static int	   currentPatientCapacity = INITIAL_CAPACITY;

// Function prototypes for internal helper functions
static char *getPatientName(char patientName[]);
static int   getPatientAge(int *patientAge);
static char *getPatientDiagnosis(char patientDiagnosis[]);
static int   getRoomNumber(int *roomNumber);
static int   getPatientIndexForDischarge(void);
static int   confirmDischarge(int patientIndex);
static void  removePatientFromSystem(int index);
static int   patientExists(int id);

/*
 * Initializes the patient management system.
 */
void initializePatientSystem(void)
{
    patients = malloc(sizeof(Patient) * INITIAL_CAPACITY);

    if(patients == NULL)
    {
		free(patients);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < INITIAL_CAPACITY ; i++)
    {
        patients[i]. patientId    = INVALID_ID;
        patients[i].name[0]      = '\0';
        patients[i].ageInYears   = 0;
        patients[i].diagnosis[0] = '\0';
        patients[i].roomNumber   = 0;
    }
    totalPatients    = IS_EMPTY;
    patientIDCounter = DEFAULT_ID;
    currentPatientCapacity = INITIAL_CAPACITY;
}

/*
 * Adds a new patient record to the system after validating input fields.
 */
void addPatientRecord(void)
{
    if(totalPatients >= currentPatientCapacity)
    {
		Patient *temp = realloc(patients, sizeof(Patient) * (currentPatientCapacity + 1));
		if(temp == NULL)
        {
            free(patients);
            exit(EXIT_FAILURE);
        }
        patients = temp;
        currentPatientCapacity++;
    }

    char patientName[MAX_PATIENT_NAME_LENGTH];
    int  patientAge;
    char patientDiagnosis[MAX_DIAGNOSIS_LENGTH];
    int  roomNumber;

    getPatientName(patientName);
    getPatientAge(&patientAge);
    getPatientDiagnosis(patientDiagnosis);
    getRoomNumber(&roomNumber);

    // Create and store new patient record
    Patient newPatient      = createPatient(patientName, patientAge, patientDiagnosis, roomNumber, patientIDCounter);
    patients[totalPatients] = newPatient;
    totalPatients++;
    patientIDCounter++;

    printf("--- Patient Added ---\n");
    printPatient(patients[totalPatients - 1]);
}

/*
 * Displays all patient records stored in the system.
 */
void viewPatientRecords(void)
{
    if(totalPatients == IS_EMPTY)
    {
        printf("No Patients Admitted...\n");
        return;
    }

    for(int i = 0; i < currentPatientCapacity ; i++)
    {
        if(patients[i].patientId != INVALID_ID)
        {
            printPatient(patients[i]);
        }
    }
}

/*
 * Searches for a patient by ID and displays their details if found.
 */
void searchPatientById(void)
{
    int id, index;

    if(totalPatients == IS_EMPTY)
    {
        printf("No Patients Admitted...\n");
        return;
    }

    printf("Enter A Patient Id: ");
    scanf("%d", &id);
    clearInputBuffer();

    index = patientExists(id);

    if(index == PATIENT_NOT_FOUND)
    {
        printf("Patient does not exist!\n");
    }
    else
    {
        printPatient(patients[index]);
    }
}

/*
 * Removes a patient from the system if they exist and discharge is confirmed.
 */

// after discharge, check to see if we need to reallocate memory to reduce size of array.
void dischargePatient(void)
{
    if(totalPatients == IS_EMPTY)
    {
        printf("No patients to discharge!\n");
        return;
    }

    int index = getPatientIndexForDischarge();

    if(index == PATIENT_NOT_FOUND)
    {
        printf("Patient is not in system.\n");
        return;
    }

    if(confirmDischarge(index))
    {
        removePatientFromSystem(index);
        printf("Patient has been discharged!\n");
    }
    else
    {
        printf("Patient discharge cancelled.\n");
    }
}

void clearMemory()
{
//    for(int i = 0; i < currentPatientCapacity; i++)
//	{
//    	free(patients[i]);
//    }
    free(patients);
    puts("Memory freed");
}

/*
 * Reads and validates the patient's name from user input.
 */
static char *getPatientName(char patientName[])
{
    int isValid;

    do
    {
        printf("Enter Patient Name:\n");
        fgets(patientName, 101, stdin);
        patientName[strcspn(patientName, "\n")] = '\0';

        isValid = validatePatientName(patientName);

        if(isValid == IS_NOT_VALID)
        {
            printf("Invalid patient name. Please try again.\n");
        }
    }
    while(isValid == IS_NOT_VALID);

    return patientName;
}

/*
 * Reads and validates the patient's age from user input.
 */
static int getPatientAge(int *patientAge)
{
    int isValid;
    int scanResult;

    do
    {
        printf("Enter Patient Age:\n");
        scanResult = scanf("%d", patientAge);
        clearInputBuffer();

        if(scanResult != SUCCESSFUL_READ)
        {
            printf("Invalid input. Please enter a number.\n");
            isValid = IS_NOT_VALID;
            continue;
        }

        isValid = validatePatientAge(*patientAge);

        if(isValid == IS_NOT_VALID)
        {
            printf("Invalid patient age. Please try again.\n");
        }
    }
    while(isValid == IS_NOT_VALID);

    return IS_VALID;
}

/*
 * Reads and validates the patient's diagnosis from user input.
 */
static char *getPatientDiagnosis(char patientDiagnosis[])
{
    int isValid;

    do
    {
        printf("Enter Patient Diagnosis:\n");
        fgets(patientDiagnosis, MAX_DIAGNOSIS_LENGTH, stdin);
        patientDiagnosis[strcspn(patientDiagnosis, "\n")] = '\0';

        isValid = validatePatientDiagnosis(patientDiagnosis);

        if(isValid == IS_NOT_VALID)
        {
            printf("Invalid diagnosis. Please try again.\n");
        }
    }
    while(isValid == IS_NOT_VALID);

    return patientDiagnosis;
}

/*
 * Reads and validates the room number for the patient.
 */
static int getRoomNumber(int *roomNumber)
{
    int isValid;

    do
    {
        printf("Enter Patient Room:\n");
        if(scanf("%d", roomNumber) != SUCCESSFUL_READ)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            isValid = IS_NOT_VALID;
            continue;
        }
        clearInputBuffer();

        // First check if the room number is in valid range
        isValid = validateRoomNumber(*roomNumber);

        if(isValid == IS_NOT_VALID)
        {
            printf("Invalid room number. Please try again.\n");
            continue;
        }

        // Then check if the room is already occupied
        if(isRoomOccupied(*roomNumber, patients, currentPatientCapacity ) != ROOM_UNOCCUPIED)
        {
            printf("Room already occupied. Please choose another room.\n");
            isValid = IS_NOT_VALID;
        }
    }
    while(isValid == IS_NOT_VALID);

    return IS_VALID;
}

/*
 * Prompts user for a patient ID and returns their index in the system.
 */
static int getPatientIndexForDischarge(void)
{
    int patientId;
    printf("Enter ID of patient to discharge:\n");
    scanf("%d", &patientId);
    clearInputBuffer();
    return patientExists(patientId);
}

/*
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
 * Removes a patient from the system by shifting array elements.
 */
static void removePatientFromSystem(int index)
{
    for(int i = index; i < REMOVE_PATIENT_ARRAY_MAX; i++)
    {
        patients[i] = patients[i + NEXT_INDEX_OFFSET];
    }
    totalPatients--;
}

/*
 * Checks if a patient with a given ID exists and returns their index.
 */
static int patientExists(int id)
{
    for(int i = 0; i < currentPatientCapacity ; i++)
    {
        if(patients[i].patientId == id)
        {
            return i;
        }
    }
    return PATIENT_NOT_FOUND;
}



