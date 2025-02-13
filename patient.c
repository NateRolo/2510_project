/*
 * Author: Arsh M, Nathan O
 * Date: Feb 6, 2025
 * Purpose: This file implements functions for managing patient records in a hospital system.
 */

#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "utils.h"
#include <ctype.h>

// Private constants (private to patient.c)
constexpr static int MAX_PATIENT_CAPACITY = 50;

constexpr static int MAX_ROOM_NUMBER = 50;
constexpr static int MIN_ROOM_NUMBER = 1;

constexpr static int MIN_PATIENT_NAME_LENGTH = 1;
constexpr static int MAX_PATIENT_NAME_LENGTH = 100;

constexpr static int MIN_DIAGNOSIS_LENGTH = 1;
constexpr static int MAX_DIAGNOSIS_LENGTH = 255;

constexpr static int MIN_AGE_YEARS = 0;
constexpr static int MAX_AGE_YEARS = 120;

constexpr static int PATIENT_NOT_FOUND = -1;

constexpr static int DEFAULT_ID = 1;
constexpr static int INVALID_ID = 0;

constexpr static int NULL_TERMINATOR = 0;

constexpr static int REMOVE_PATIENT_ARRAY_MAX = 49;
constexpr static int NEXT_INDEX_OFFSET = 1;

constexpr static int ROOM_UNOCCUPIED = -1;

constexpr static int NUMBER_ZERO = 0;
constexpr static int NUMBER_NINE = 9;

constexpr static int NO_LETTERS = 0;
constexpr static int HAS_LETTERS = 1;

constexpr static int IS_EMPTY = 0;

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

// Function prototypes for internal (static) functions
static char *getPatientName(char patientName[]);
static int getPatientAge(int *patientAge);
static char *getPatientDiagnosis(char patientDiagnosis[]);
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

Patient patients[MAX_PATIENT_CAPACITY];
int totalPatients = IS_EMPTY;
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

    getPatientName(patientName);
    getPatientAge(&patientAge);
    getPatientDiagnosis(patientDiagnosis);
    getRoomNumber(&roomNumber);

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
 * Reads and validates the patient's name from user input.
 */
static char *getPatientName(char patientName[])
{
    int isValid;
    
    do
    {
        printf("Enter Patient Name:\n");
        fgets(patientName, MAX_PATIENT_NAME_LENGTH, stdin);
        patientName[strcspn(patientName, "\n")] = NULL_TERMINATOR;
        
        isValid = validatePatientName(patientName);
        
        if (isValid == IS_NOT_VALID)
        {
            printf("Invalid patient name. Please try again.\n");
        }
    }
    while (isValid == IS_NOT_VALID);
    
    return patientName;
}

/*
 * Function: getPatientAge
 * -----------------------
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
        
        if (scanResult != SUCCESSFUL_READ)
        {
            printf("Invalid input. Please enter a number.\n");
            isValid = IS_NOT_VALID;
            continue;
        }
        
        isValid = validatePatientAge(*patientAge);
        
        if (isValid == IS_NOT_VALID)
        {
            printf("Invalid patient age. Please try again.\n");
        }
    }
    while (isValid == IS_NOT_VALID);
    
    return IS_VALID;
}

/*
 * Function: getPatientDiagnosis
 * -----------------------------
 * Reads and validates the patient's diagnosis from user input.
 */
static char *getPatientDiagnosis(char patientDiagnosis[])
{
    int isValid;
    
    do
    {
        printf("Enter Patient Diagnosis:\n");
        fgets(patientDiagnosis, MAX_DIAGNOSIS_LENGTH, stdin);
        patientDiagnosis[strcspn(patientDiagnosis, "\n")] = NULL_TERMINATOR;
        
        isValid = validatePatientDiagnosis(patientDiagnosis);
        
        if (isValid == IS_NOT_VALID)
        {
            printf("Invalid diagnosis. Please try again.\n");
        }
    }
    while (isValid == IS_NOT_VALID);
    
    return patientDiagnosis;
}

/*
 * Function: getRoomNumber
 * -----------------------
 * Reads and validates the room number for the patient.
 */
static int getRoomNumber(int *roomNumber)
{
    int isValid;
    
    do
    {
        printf("Enter Patient Room:\n");
        if (scanf("%d", roomNumber) != SUCCESSFUL_READ)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            isValid = IS_NOT_VALID;
            continue;
        }
        clearInputBuffer();
        
        isValid = validateRoomNumber(*roomNumber);
        
        if (isValid == IS_NOT_VALID)
        {
            printf("Invalid room number. Please try again.\n");
        }
    }
    while (isValid == IS_NOT_VALID);
    
    return IS_VALID;
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
    return ROOM_UNOCCUPIED;
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

static int validatePatientName(char patientName[])
{
    if (patientName == NULL)
    {
        return IS_NOT_VALID;
    }

    if (strlen(patientName) == IS_EMPTY ||
        strlen(patientName) > MAX_PATIENT_NAME_LENGTH)
    {
        return IS_NOT_VALID;
    }

    int hasLetter;

    hasLetter = NO_LETTERS;

    for (int i = 0; patientName[i] != '\0'; i++)
    {
        
        if (isdigit(patientName[i]))
        {
            return IS_NOT_VALID;
        }

        if (isalpha(patientName[i]))
        {
            hasLetter = HAS_LETTERS;
        }
    }

    if (hasLetter == NO_LETTERS)
    {
        return IS_NOT_VALID;
    }

    return IS_VALID;
}

static int validatePatientAge(int patientAge)
{
    if(patientAge < MIN_AGE_YEARS || 
       patientAge > MAX_AGE_YEARS)
    {
        return IS_NOT_VALID;
    }

    return IS_VALID;
}

static int validatePatientDiagnosis(char patientDiagnosis[])
{
    if(patientDiagnosis == NULL)
    {
        return IS_NOT_VALID;
    }

    if(strlen(patientDiagnosis) == IS_EMPTY ||
       strlen(patientDiagnosis) > MAX_DIAGNOSIS_LENGTH)
    {
        return IS_NOT_VALID;
    }

    int hasLetter;

    hasLetter = NO_LETTERS;

    for(int i = 0; patientDiagnosis[i] != '\0'; i++)
    {
        
        if (isdigit(patientDiagnosis[i]))
        {
            return IS_NOT_VALID;
        }

        if (isalpha(patientDiagnosis[i]))
        {
            hasLetter = HAS_LETTERS;
        }
    }

    if(hasLetter == NO_LETTERS)
    {
        return IS_NOT_VALID;
    }

    return IS_VALID;
}

static int validateRoomNumber(int roomNumber)
{
    if(roomNumber < MIN_ROOM_NUMBER || 
       roomNumber > MAX_ROOM_NUMBER)
    {
        return IS_NOT_VALID;
    }

    if(checkRoomOccupancy(roomNumber) != ROOM_UNOCCUPIED)
    {
        return IS_NOT_VALID;
    }

    return IS_VALID;
}
