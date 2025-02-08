/*
 * Author: Arsh M, Nathan O
 * Date: Jan 30, 2025
 * Purpose: Main driver of hospital system project.
 */

#include <stdio.h>
#include <string.h>
#include "patient.h"

// constants for menu
#define ENTER_PATIENT_RECORD 1
#define SEARCH_PATIENT_BY_ID 2
#define VIEW_ALL_PATIENTS 3
#define DISCHARGE_PATIENT 4
#define MANAGE_DOCTOR_SCHEDULE 5
#define EXIT_PROGRAM 6
#define INVALID_USER_INPUT (-1)

#define MAX_PATIENT_CAPACITY 50

#define MIN_PATIENT_NAME_LENGTH 1
#define MAX_PATIENT_NAME_LENGTH 100

#define MIN_DIAGNOSIS_LENGTH 1
#define MAX_DIAGNOSIS_LENGTH 255

#define MIN_ROOM_NUMBER 1
#define MAX_ROOM_NUMBER 50

#define MIN_AGE_YEARS 0
#define MAX_AGE_YEARS 120

// function prototypes
void menu();
void clearInputBuffer();

// hospital patients
Patient patients[MAX_PATIENT_CAPACITY];

int totalPatients = 0;
int patientIDCounter = 1;


int main(void)
{
    menu();
    return 0;
}

// add patient record function
void addPatientRecord()
{
    if(totalPatients >= MAX_PATIENT_CAPACITY)
    {
        printf("Max patient capacity reached!");
        return;
    }

    char patientName[MAX_PATIENT_NAME_LENGTH];
    int patientAge;
    char patientDiagnosis[MAX_DIAGNOSIS_LENGTH];
    int roomNumber;

    // get patient name
    printf("Enter patient name:\n");
    fgets(patientName, MAX_PATIENT_NAME_LENGTH, stdin);
    patientName[strcspn(patientName, "\n")] = 0;

    if(strlen(patientName) < MIN_PATIENT_NAME_LENGTH || 
       strlen(patientName) > MAX_PATIENT_NAME_LENGTH)
    {
        printf("Patient name must be between %d and %d characters long.\n", 
               MIN_PATIENT_NAME_LENGTH, MAX_PATIENT_NAME_LENGTH);
        return;
    }

    // get patient age
    printf("Enter patient age:\n");
    scanf("%d", &patientAge);
    
    if (patientAge < MIN_AGE_YEARS || 
        patientAge > MAX_AGE_YEARS)
    {
        printf("Invalid age! Please enter a number between %d and %d.\n", 
               MIN_AGE_YEARS, MAX_AGE_YEARS);
        return;
    }
    clearInputBuffer();

    printf("Enter patient diagnosis:\n");
    fgets(patientDiagnosis, MAX_DIAGNOSIS_LENGTH, stdin);
    patientDiagnosis[strcspn(patientDiagnosis, "\n")] = 0;

    if(strlen(patientDiagnosis) < MIN_DIAGNOSIS_LENGTH || 
       strlen(patientDiagnosis) > MAX_DIAGNOSIS_LENGTH)
    {
        printf("Patient diagnosis must be between %d and %d characters long.\n", 
               MIN_DIAGNOSIS_LENGTH, MAX_DIAGNOSIS_LENGTH);
        return;
    }

    // get patient room number
    printf("Enter patient room:\n");
    scanf("%d", &roomNumber);

    if (roomNumber < MIN_ROOM_NUMBER || 
        roomNumber > MAX_ROOM_NUMBER)
    {
        printf("Invalid Room Number: Must be between %d and %d.\n", 
               MIN_ROOM_NUMBER, MAX_ROOM_NUMBER);
        return;
    }
    clearInputBuffer();

    // create new patient
    Patient newPatient;

    // set patient id
    newPatient.patientId = patientIDCounter;

    // set patient name
    strcpy(newPatient.name, patientName);

    // set patient age
    newPatient.age = patientAge;

    // set patient diagnosis
    strcpy(newPatient.diagnosis, patientDiagnosis);

    // set patient room number
    newPatient.roomNumber = roomNumber;

    // add patient to array
    patients[totalPatients] = newPatient;

    // increment total patients and patient id counter
    totalPatients++;
    patientIDCounter++;

    // print success message
    printf("Patient added!\n");

}

void viewPatientRecords()
{
    if (totalPatients == 0)
    {
        printf("No Patients Admitted...");
        return;
    }

    printf("--- Patient Record ---\n");
    for(int i = 0; i < MAX_PATIENT_CAPACITY; i++)
    {
        if (patients[i].patientId != 0)
        {
            printf("Patient ID: %d\n", patients[i].patientId);
            printf("Patient Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Diagnosis: %s\n", patients[i].diagnosis);
            printf("Room Number: %d\n", patients[i].roomNumber);
            printf("---------------------------------------");
        }
    }
}

int patientExists(int id)
{
    for (int i = 0; i < MAX_PATIENT_CAPACITY; i++)
    {
        if (patients[i].patientId == id)
        {
            return i;
        }
    }

    return -1;
}

void searchPatientById()
{
    int id, index;

    printf("Enter A Patient Id: ");
    scanf("%d", &id);

    index = patientExists(id);

    if (index != -1)
    {
        printf("Patient ID: %d\n", patients[index].patientId);
        printf("Patient Name: %s\n", patients[index].name);
        printf("Age: %d\n", patients[index].age);
        printf("Diagnosis: %s\n", patients[index].diagnosis);
        printf("Room Number: %d\n", patients[index].roomNumber);
        printf("---------------------------------------");
    } else
    {
        printf("Patient Does Not Exist!");
    }
}



void menu()
{
    int userInput;

    do
    {
        userInput = INVALID_USER_INPUT;

        printf("Welcome to the [blank] Hospital Patient Management System.\n"
               "Enter one of the following options:\n"
               "1: Enter Patient Record.\n"
               "2: Search Patient by ID.\n"
               "3: View All Patients.\n"
               "4: Discharge Patient.\n"
               "5: Manage Doctor Schedule:\n"
               "6: Exit.\n");

        if (scanf("%d", &userInput) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch(userInput)
        {
            case ENTER_PATIENT_RECORD:
                // enter patient record function
                getchar();
                addPatientRecord();
            break;
            case SEARCH_PATIENT_BY_ID:
                // search patients function
                    getchar();
                    searchPatientById();
            break;
            case VIEW_ALL_PATIENTS:
                getchar();
                viewPatientRecords();

            break;
            case DISCHARGE_PATIENT:
                // discharge patient function
                    puts("discharge patients.\n");
            break;
            case MANAGE_DOCTOR_SCHEDULE:
                // manage doctor sched function
                    puts("manage doctor sched.\n");
            break;
            case EXIT_PROGRAM:
                puts("Exiting program, have a nice day!");
            return;
            default:
                printf("Not a valid input, please enter "
                       "one of the options above.\n");
            userInput = INVALID_USER_INPUT;
        }

    } while (userInput != EXIT_PROGRAM);
}

void clearInputBuffer()
{
    while(getchar() != '\n');
}