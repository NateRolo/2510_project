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
static struct Node *patientHead      = NULL;
static int          totalPatients    = IS_EMPTY;
static int          patientIDCounter = DEFAULT_ID;

// Function prototypes for internal helper functions
static char        *getPatientName(char patientName[]);
static int          getPatientAge(int *patientAge);
static char        *getPatientDiagnosis(char patientDiagnosis[]);
static int          getRoomNumber(int *roomNumber);
static Patient     *getPatientToDischarge(void);
static int          confirmDischarge(Patient *patient);
static void         removePatientFromSystem(Patient *patient);
static Patient     *getPatientFromList(int id);
static void         writePatientToFile(Patient newPatient);
static void         updatePatientsFile(void);
static struct Node *insertPatientAtEndOfList(struct Node *head, Patient data);
static int          isRoomOccupiedInList(int roomNumber, struct Node *head);
void                printList(struct Node *head);

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

        // read from file and populate to linked list
        Patient tempPatient;
        while(fread(&tempPatient, sizeof(Patient), 1, pPatients) == 1)
        {
            patientHead = insertPatientAtEndOfList(patientHead, tempPatient);
            totalPatients++;
        }

        patientIDCounter = count + 1;
          
        fclose(pPatients);


        puts("\nPatients successfully loaded from file.");

        printList(patientHead);
    }
    else
    {
        puts("\nUnable to read patients.dat. Patients initialized with default settings.");
        initializePatientSystemDefault();
    }
}

void printList(struct Node *head)
{
    struct Node *current = head;
    while(current)
    {
        printf("%d\n%s\n", current->data.patientId, current->data.name);
        current = current->nextNode;
    }
}

/*
 * Initializes the patient management system with default settings.
 * Called when patients.dat cannot be read or is empty.
 */
void initializePatientSystemDefault(void)
{
    patientHead      = NULL;
    totalPatients    = IS_EMPTY;
    patientIDCounter = DEFAULT_ID;
    puts("Patient system initialized with default settings using linked list.");
}


/*
 * Adds a new patient record to the system after validating input fields.
 */
void addPatientRecord(void)
{
    char patientName[MAX_PATIENT_NAME_LENGTH];
    int  patientAge;
    char patientDiagnosis[MAX_DIAGNOSIS_LENGTH];
    int  roomNumber;

    getPatientName(patientName);
    getPatientAge(&patientAge);
    getPatientDiagnosis(patientDiagnosis);
    getRoomNumber(&roomNumber);

    // Create and store new patient record
    Patient newPatient = createPatient(patientName, patientAge, patientDiagnosis, roomNumber, patientIDCounter);
    patientHead        = insertPatientAtEndOfList(patientHead, newPatient);
    totalPatients++;
    patientIDCounter++;

    writePatientToFile(newPatient);

    printf("--- Patient Added ---\n");
    printPatient(newPatient);
}

static struct Node *insertPatientAtEndOfList(struct Node *head, Patient data)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        free(newNode);
        return NULL;
    }

    newNode->data     = data;
    newNode->nextNode = NULL;

    if(head == NULL)
    {
        puts("No previous patients, patient added at start of list");
        return newNode;
    }

    struct Node *current = head;
    while(current->nextNode != NULL)
    {
        current = current->nextNode;
    }
    current->nextNode = newNode;

    puts("Patient inserted at end of list.");
    return head;
}

/*
 * Displays all patient records stored in the system.
 */
void viewPatientRecords(void)
{
    if(patientHead == NULL)
    {
        puts("No patients admitted!");
        return;
    }

    struct Node *current = patientHead;
    while(current->nextNode != NULL)
    {
        printPatient(current->data);
        current = current->nextNode;
    }
}

/*
 * Searches for a patient by ID and displays their details if found.
 */
void searchPatientById(void)
{
    int id, index;

    if(patientHead == NULL)
    {
        puts("No patients admitted!");
        return;
    }

    printf("Enter A Patient Id: ");
    scanf("%d", &id);
    clearInputBuffer();

    struct Node *current = patientHead;
    while(current->nextNode != NULL)
    {
        if(current->data.patientId == id)
        {
            printPatient(current->data);
            return;
        }
        current = current->nextNode;
    }

    puts("Patient doesn't exist!");
}

/*
 * Removes a patient from the system if they exist and discharge is confirmed.
 */
void dischargePatient(void)
{
    if(patientHead == NULL)
    {
        puts("No patients to discharge!");
        return; // Add return here
    }

    Patient *patientToDischarge = getPatientToDischarge();

    if(patientToDischarge == NULL)
    {
        puts("Patient not found!");
        return;
    }

    if(confirmDischarge(patientToDischarge))
    {
        removePatientFromSystem(patientToDischarge);
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
    struct Node *current = patientHead;
    while(current != NULL)
    {
        struct Node *next = current->nextNode;
        free(current);
        current = next;
    }
    patientHead = NULL;
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

        // Check if the room is already occupied by traversing the linked list.
        if(isRoomOccupiedInList(*roomNumber, patientHead) != ROOM_UNOCCUPIED)
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
static Patient *getPatientToDischarge(void)
{
    int patientId;
    printf("Enter ID of patient to discharge:\n");
    scanf("%d", &patientId);
    clearInputBuffer();
    return getPatientFromList(patientId);
}

/*
 * Asks the user to confirm the discharge of a patient.
 */
static int confirmDischarge(Patient *patient)
{
    char confirm;
    printf("Patient ID: %d\n", patient->patientId);
    printf("Patient Name: %s\n", patient->name);
    printf("Are you sure you want to discharge this patient? (y/n)\n");
    scanf("%c", &confirm);
    clearInputBuffer();
    return confirm == 'y';
}

/*
 * Removes a patient from the system by unlinking the corresponding node from the linked list.
 */
static void removePatientFromSystem(Patient *patient)
{
    if(patientHead == NULL || patient == NULL)
    {
        return;
    }

    struct Node *current  = patientHead;
    struct Node *prevNode = NULL;

    if(current != NULL && current->data.patientId == patient->patientId)
    {
        patientHead = current->nextNode;
        free(current);
        totalPatients--;
        updatePatientsFile();
        return;
    }

    // Search for the patient to remove
    while(current != NULL && current->data.patientId != patient->patientId)
    {
        prevNode = current;
        current  = current->nextNode;
    }

    // If patient was not found
    if(current == NULL)
    {
        return;
    }

    // Unlink the node and free memory
    prevNode->nextNode = current->nextNode;
    free(current);
    totalPatients--;

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
        return;
    }

    struct Node *current = patientHead;
    while(current != NULL)
    {
        if(fwrite(&(current->data), sizeof(Patient), 1, pPatients) != 1)
        {
            perror("Error writing patient to file");
            fclose(pPatients);
            return;
        }
        current = current->nextNode;
    }

    puts("patients.dat updated.");
    fclose(pPatients);
}

/*
 * Prompts user for a patient ID and returns a pointer to the patient record in the linked list.
 */

static Patient *getPatientFromList(int id)
{
    if(patientHead == NULL)
    {
        return NULL;
    }

    struct Node *current = patientHead;
    while(current != NULL)
    {
        if(current->data.patientId == id)
        {
            return &(current->data);
        }
        current = current->nextNode;
    }
    return NULL;
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

/*
 * Checks if a room is currently occupied.
 */
static int isRoomOccupiedInList(int roomNumber, struct Node *head)
{
    struct Node *current = head;
    while(current != NULL)
    {
        if(current->data.roomNumber == roomNumber)
            return 1;
        current = current->nextNode;
    }
    return ROOM_UNOCCUPIED;
}
