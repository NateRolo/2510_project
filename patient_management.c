/*
 * Author: Arsh M, Nathan O
 * Date: Feb 6, 2025
 * Purpose: This file implements functions for managing patient records in a hospital system.
 */

#include "patient_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
static int      totalPatients          = IS_EMPTY;
static int      patientIDCounter       = DEFAULT_ID;
static int      currentPatientCapacity = INITIAL_CAPACITY;

// Function prototypes for internal helper functions
static char *getPatientName(char patientName[]);
static int   getPatientAge(int *patientAge);
static char *getPatientDiagnosis(char patientDiagnosis[]);
static int   getRoomNumber(int *roomNumber);
static int   getPatientIndexForDischarge(void);
static int   confirmDischarge(int patientIndex);
static void  removePatientFromSystem(int index);
static int   patientExists(int id);
static void  writePatientToFile(Patient newPatient);
static void  updatePatientsFile(void);

/*
 * Initializes the patient management system.
 * Attempts to load patient data from patients.dat file.
 */
void initializePatientSystem(void)
{
    FILE *pPatients = fopen("patients.dat", "rb");

    if(pPatients != NULL)
    {
        fseek(pPatients, 0, SEEK_END);
        long fileSize = ftell(pPatients);
        rewind(pPatients);

        size_t count = fileSize / sizeof(Patient);

        if(count == 0)
        {
            fclose(pPatients);
            puts("\nPatients.dat was empty, initialized with default settings");
            initializePatientSystemDefault();
            return;
        }

        patients = malloc(sizeof(Patient) * count);

        if(patients == NULL)
        {
            free(patients);
            fclose(pPatients);
            exit(EXIT_FAILURE);
        }

        size_t read = fread(patients, sizeof(Patient), count, pPatients);

        if(read != count)
        {
            fclose(pPatients);
            free(patients);
            puts("\nError reading from patients.dat. Initializing with default settings.");
            initializePatientSystemDefault();
            return;
        }

        totalPatients          = read;
        currentPatientCapacity = count;

        patientIDCounter = DEFAULT_ID;
        for(size_t i = 0; i < count; i++)
        {
            if(patients[i].patientId >= patientIDCounter)
            {
                patientIDCounter = patients[i].patientId + 1;
            }
        }

        fclose(pPatients);
        puts("\nPatients successfully loaded from file.");
    }
    else
    {
        fclose(pPatients);
        puts("\nUnable to read patients.dat. Patients initialized with default settings.");
        initializePatientSystemDefault();
    }
}

/*
 * Initializes the patient management system with default settings.
 * Called when patients.dat cannot be read or is empty.
 */
void initializePatientSystemDefault(void)
{
    patients = malloc(sizeof(Patient) * INITIAL_CAPACITY);

    if(patients == NULL)
    {
        free(patients);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < INITIAL_CAPACITY; i++)
    {
        patients[i].patientId    = INVALID_ID;
        patients[i].name[0]      = '\0';
        patients[i].ageInYears   = 0;
        patients[i].diagnosis[0] = '\0';
        patients[i].roomNumber   = 0;
    }
    totalPatients          = IS_EMPTY;
    patientIDCounter       = DEFAULT_ID;
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

    writePatientToFile(newPatient);

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

    for(int i = 0; i < totalPatients; i++)
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

/*
 * Frees allocated memory for patient data.
 */
void clearMemory()
{
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
        if(isRoomOccupied(*roomNumber, patients, currentPatientCapacity) != ROOM_UNOCCUPIED)
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
 * Also handles memory reallocation when capacity can be reduced.
 */
static void removePatientFromSystem(int index)
{
    // Mark the discharged patient slot as invalid
    patients[index].patientId = INVALID_ID;

    // Compact the array by shifting valid patients
    for(int i = 0; i < totalPatients - 1; i++)
    {
        if(patients[i].patientId == INVALID_ID)
        {
            // Find next valid patient
            int j = i + 1;
            while(j < totalPatients && patients[j].patientId == INVALID_ID)
            {
                j++;
            }

            // If found a valid patient, move them to current position
            if(j < totalPatients)
            {
                patients[i]           = patients[j];
                patients[j].patientId = INVALID_ID;
            }
        }
    }
    
    totalPatients--;

    if(totalPatients > 0 && totalPatients < (currentPatientCapacity / 2) && currentPatientCapacity > 1)
    {
        int      newCapacity = currentPatientCapacity / 2;
        Patient *temp        = realloc(patients, sizeof(Patient) * newCapacity);

        if(temp != NULL)
        {
            patients               = temp;
            currentPatientCapacity = newCapacity;
        }
    }

    updatePatientsFile();
}

/**
 * Rewrites the patients.dat file with current patient data.
 * Opens file in write binary mode and writes all active patient records.
 */
static void updatePatientsFile(void)
{
    FILE *pPatients = fopen("patients.dat", "wb");

    if(pPatients == NULL)
    {
        perror("Patients.dat not found, patient not deleted from file.");
        fclose(pPatients);
    }

    for(int i = 0; i < totalPatients; i++)
    {
        fwrite(&patients[i], sizeof(Patient), 1, pPatients);
    }

    puts("patients.dat updated.");
    fclose(pPatients);
}

/*
 * Checks if a patient with a given ID exists and returns their index.
 */
static int patientExists(int id)
{
    for(int i = 0; i < currentPatientCapacity; i++)
    {
        if(patients[i].patientId == id)
        {
            return i;
        }
    }
    return PATIENT_NOT_FOUND;
}

/**
 * Appends a single patient record to the patients.dat file.
 * Opens file in append binary mode, writes patient data, and handles errors.
 */
static void writePatientToFile(Patient newPatient)
{
    FILE *pPatients = fopen("patients.dat", "ab");

    if(pPatients == NULL)
    {
        puts("\nUnable to find patients.dat. Patient not added to file.");
        return;
    }

    fwrite(&newPatient, sizeof(Patient), 1, pPatients);
    fclose(pPatients);
    puts("\nPatient successfully added to file.\n");
}
