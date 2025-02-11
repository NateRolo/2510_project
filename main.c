/*
 * Author: Arsh M, Nathan O
 * Date: Jan 30, 2025
 * Purpose: Main driver of hospital system project.
 */

#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "doctor.h"

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
void addPatientRecord();
void viewPatientRecords();
void searchPatientById();
void doctorMenu();
void assignDoctor();
char* getDayOfWeek(int);
char* getTimeOfDay(int);
void printFullSchedule();
int doctorExists(int idIndex);
int dayExists(int dayIndex);
int timeOfDayExists(int timeIndex);

int patientExists(int id);
int checkRoomOccupancy(int roomNumber);

// hospital patients
Patient patients[MAX_PATIENT_CAPACITY];
int patientRooms[MAX_PATIENT_CAPACITY];

Doctor weeklySchedule[7][3];
const char* daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const char* timeOfDay[] = {"Morning", "Afternoon", "Evening"};

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
        printf("Max patient capacity reached!\n");
        return;
    }

    char patientName[MAX_PATIENT_NAME_LENGTH];
    int patientAge;
    char patientDiagnosis[MAX_DIAGNOSIS_LENGTH];
    int roomNumber;

    // get patient name
    printf("Enter patient name:\n");
    fgets(patientName, MAX_PATIENT_NAME_LENGTH, stdin);
    patientName[strcspn(patientName, "\n")] = '\0';

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
    patientDiagnosis[strcspn(patientDiagnosis, "\n")] = '\0';

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
    clearInputBuffer();

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

    printf("Patient added successfully!\n");
    printf("Patient ID: %d\n", newPatient.patientId);
    printf("Patient Name: %s\n", newPatient.name);
    printf("Patient Age: %d\n", newPatient.age);
    printf("Patient Diagnosis: %s\n", newPatient.diagnosis);
    printf("Patient Room Number: %d\n", newPatient.roomNumber);
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
        char confirm;

        printf("Patient ID: %d\n", patients[index].patientId);
        printf("Patient Name: %s\n", patients[index].name);
        printf("Are you sure you want to discharge this patient? (y/n)\n");
        scanf("%c", &confirm);
        clearInputBuffer();

        if(confirm == 'y')
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
            printf("Patient discharge cancelled.\n");
        }
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

        printf("\nWelcome to the [blank] Hospital Patient Management System.\n"
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
                doctorMenu();
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

void doctorMenu()
{
    int userInput;

    do
    {
        userInput = INVALID_USER_INPUT;

        printf("\nDoctor Management System.\n"
               "Enter one of the following options:\n"
               "1: Assign Doctor to Shift.\n"
               "2: Display Full Weekly Schedule.\n"
               "3: Exit.\n");

        if (scanf("%d", &userInput) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch(userInput)
        {
            case 1:
                clearInputBuffer();
                assignDoctor();
                break;
            case 2:
                clearInputBuffer();
                printFullSchedule();
                break;
            case 3:
                puts("Exiting program, have a nice day!\n");
                return;
            default:
                printf("Not a valid input, please enter "
                       "one of the options above.\n");
                userInput = INVALID_USER_INPUT;
        }
    } while (userInput != EXIT_PROGRAM);
}

void assignDoctor()
{
    int doctorId = -1;
    int day = -1;
    int time = -1;
    char proceed = 'y';

    do {
        printf("Choose A Doctor:\n"
               "0: Raymond Redington\n"
               "1: George Washington\n"
               "2: Sofia Gomez\n");

        if (scanf("%d", &doctorId) != 1)
        {
            printf("Please enter a number.\n");
            clearInputBuffer();
        } else {
            doctorId = doctorExists(doctorId);
        }

    } while (doctorId == -1);

    do {
        printf("Choose A Day:\n"
               "0: Monday\n"
               "1: Tuesday\n"
               "2: Wednesday\n"
               "3: Thursday\n"
               "4: Friday\n"
               "5: Saturday\n"
               "6: Sunday\n");

        if (scanf("%d", &day) != 1)
        {
            printf("Please enter a number.\n");
            clearInputBuffer();
        } else {
            day = dayExists(day);
        }

    } while (day == -1);

    do {
        printf("Choose A Day:\n"
               "0: Morning\n"
               "1: Afternoon\n"
               "2: Evening\n");

        if (scanf("%d", &time) != 1)
        {
            printf("Please enter a number.\n");
            clearInputBuffer();
        } else {
            time = timeOfDayExists(time);
        }

    } while (time == -1);

    printf("Assigning Dr.%s for %s %s.\n", doctors[doctorId].name, getDayOfWeek(day), getTimeOfDay(time));

    if (proceed == 'y') {
        weeklySchedule[day][time] = doctors[doctorId];
    }
}

void printFullSchedule()
{
    for (int i = 0; i < 7; i++) {
        char* day = getDayOfWeek(i);
        printf("---%s---\n", day);
        printf("%-20sAssigned Doctor\n", "Time Of Day"); // Adjust header for 20 spaces
        for (int j = 0; j < 3; j++) {
            char* time = getTimeOfDay(j);
            printf("%-20s", time); // Ensure time takes up 20 spaces
            if (strlen(weeklySchedule[i][j].name) == 0) {
                printf("Unassigned!\n"); // Rest of the string will fit here
            } else {
                printf("%s\n", weeklySchedule[i][j].name);
            }
        }
    }
}

char* getDayOfWeek(int index)
{
    return daysOfWeek[index];
}

char* getTimeOfDay(int index)
{
    return timeOfDay[index];
}

void clearInputBuffer()
{
    while(getchar() != '\n');
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

int doctorExists(int idIndex)
{
    if (idIndex >= 0 &&
        idIndex < 3) {
        return idIndex;
    }

    printf("Doctor Doesn't Exist.\n");
    return -1;
}

int dayExists(int dayIndex)
{
    if (dayIndex >= 0 &&
        dayIndex < 7) {
        return dayIndex;
    }

    printf("Day Doesn't Exist.\n");
    return -1;
}

int timeOfDayExists(int timeIndex)
{
    if (timeIndex >= 0 &&
        timeIndex < 3) {
        return timeIndex;
    }

    printf("Time Of Day Doesn't Exist.\n");
    return -1;
}

int checkRoomOccupancy(int roomNumber)
{
    for(int i = 0; i < MAX_ROOM_NUMBER + 1; i++)
    {
        if(patients[i].roomNumber == roomNumber)
        {
            return i;
        }
    }
    return -1;
}