#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "utils.h"

Patient patients[MAX_PATIENT_CAPACITY];
int totalPatients = 0;
int patientIDCounter = 1;

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
    clearInputBuffer();

    if(validatePatientName(patientName) == IS_INVALID)
    {
        return;
    }

    // get patient age
    printf("Enter patient age:\n");
    scanf("%d", &patientAge);
    clearInputBuffer();

    if(validatePatientAge(patientAge) == IS_INVALID)
    {
        return;
    }

    // get patient diagnosis
    printf("Enter patient diagnosis:\n");
    fgets(patientDiagnosis, MAX_DIAGNOSIS_LENGTH, stdin);
    patientDiagnosis[strcspn(patientDiagnosis, "\n")] = '\0';

    if(validatePatientDiagnosis(patientDiagnosis) == IS_INVALID)
    {
        return;
    }

    // get patient room number
    printf("Enter patient room:\n");
    scanf("%d", &roomNumber);
    clearInputBuffer();

    if(validateRoomNumber(roomNumber) == IS_INVALID)
    {
        return;
    }

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
    clearInputBuffer();
    index = patientExists(id);

    if (index == PATIENT_NOT_FOUND)
    {
        printf("Patient Does Not Exist!\n");
    } 
    else
    {
        printf("Patient ID: %d\n", patients[index].patientId);
        printf("Patient Name: %s\n", patients[index].name);
        printf("Age: %d\n", patients[index].age);
        printf("Diagnosis: %s\n", patients[index].diagnosis);
        printf("Room Number: %d\n", patients[index].roomNumber);
        printf("---------------------------------------\n");
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
    return PATIENT_NOT_FOUND;
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

int validatePatientName(char patientName[])
{
    if(strlen(patientName) < MIN_PATIENT_NAME_LENGTH || 
       strlen(patientName) > MAX_PATIENT_NAME_LENGTH)
    {
        printf("Patient name must be between %d and %d characters long.\n", 
               MIN_PATIENT_NAME_LENGTH, MAX_PATIENT_NAME_LENGTH);
        return IS_INVALID;
    }
    return IS_VALID;
}

int validatePatientAge(int patientAge)
{
    if (patientAge < MIN_AGE_YEARS || 
        patientAge > MAX_AGE_YEARS)
    {
        printf("Invalid age! Please enter a number between %d and %d.\n", 
               MIN_AGE_YEARS, MAX_AGE_YEARS);
        return IS_INVALID;  
    }
    return IS_VALID;
}

int validatePatientDiagnosis(char patientDiagnosis[])
{
    if(strlen(patientDiagnosis) < MIN_DIAGNOSIS_LENGTH || 
       strlen(patientDiagnosis) > MAX_DIAGNOSIS_LENGTH)
    {
        printf("Patient diagnosis must be between %d and %d characters long.\n", 
               MIN_DIAGNOSIS_LENGTH, MAX_DIAGNOSIS_LENGTH);
        return IS_INVALID;
    }
    return IS_VALID;
}

int validateRoomNumber(int roomNumber)
{
    if (roomNumber < MIN_ROOM_NUMBER || 
        roomNumber > MAX_ROOM_NUMBER)
    {
        printf("Invalid Room Number: Must be between %d and %d.\n", 
               MIN_ROOM_NUMBER, MAX_ROOM_NUMBER);
        return IS_INVALID;
    }
    return IS_VALID;
}
