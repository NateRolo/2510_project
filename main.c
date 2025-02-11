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

#define MAX_ROOM_NUMBER 50
#define MIN_ROOM_NUMBER 1

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

void addPatientRecord()
{
    if(totalPatients >= MAX_PATIENT_CAPACITY)
    {
        printf("Max patient capacity reached!\n");
        return;
    }

    int patientID;
    char patientName[100];
    int patientAge;
    char patientDiagnosis[255];
    int roomNumber;

    printf("Enter patient name:\n");
    fgets(patientName, 100, stdin);
    patientName[strcspn(patientName, "\n")] = 0;

    if(strlen(patientName) == 0)
    {
        printf("Patient name cannot be blank!\n");
        return;
    }

    printf("Enter patient age:\n");
    scanf("%d", &patientAge);
    if (patientAge <= 0)
    {
        printf("Invalid age! Please enter a positive number.\n");
        return;
    }
    clearInputBuffer();


    printf("Enter patient diagnosis:\n");
    fgets(patientDiagnosis, 255, stdin);
    patientDiagnosis[strcspn(patientDiagnosis, "\n")] = 0;

    if(strlen(patientDiagnosis) == 0)
    {
        printf("Patient name cannot be blank!\n");
        return;
    }

    printf("Enter patient room:\n");
    scanf("%d", &roomNumber);

    if (roomNumber < MIN_ROOM_NUMBER || roomNumber > MAX_ROOM_NUMBER)
    {
        printf("Invalid Room Number: Negative\n");
        return;
    }
    clearInputBuffer();

    Patient patient1;

    patient1.patientId = patientIDCounter;
    strcpy(patient1.name, patientName);
    patient1.age = patientAge;
    strcpy(patient1.diagnosis, patientDiagnosis);
    patient1.roomNumber = roomNumber;

    patients[totalPatients] = patient1;
    totalPatients++;
    patientIDCounter++;
    printf("Patient added!");

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
        printf("---------------------------------------\n");
    } else
    {
        printf("Patient Does Not Exist!\n");
    }
}

void dischargePatient()
{
    if(totalPatients == 0)
    {
        printf("No patients to discharge!\n");
    }

    int index;
    int patientId;

    printf("Enter ID of patient to discharge:\n");
    scanf("%d", &patientId);
    clearInputBuffer();

    index = patientExists(patientId);

    if(index != -1)
    {
        for(int i = index; i < MAX_PATIENT_CAPACITY - 1; i++)
        {
            patients[i] = patients[i + 1];
        }
        totalPatients--;
        printf("Patient has been discharged!\n");
    }
    else
    {
        printf("Patient is not in system.\n");
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
                clearInputBuffer();
                dischargePatient();
            break;
            case MANAGE_DOCTOR_SCHEDULE:
                // manage doctor sched function
                    puts("manage doctor sched.\n");
            break;
            case EXIT_PROGRAM:
                puts("Exiting program, have a nice day!\n");
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