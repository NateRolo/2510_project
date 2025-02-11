/*
 * Author: Arsh M, Nathan O
 * Date: 2/6/2025
 * Purpose: This file represents a patient with patient id, name, age, diagonsis, and room number.
 */

#ifndef HOSPITAL_PATIENT_H
#define HOSPTAL_PATIENT_H

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

#define IS_NOT_VALID 0
#define IS_VALID 1

#define PATIENT_NOT_FOUND -1

#define IS_EMPTY 0

#define DEFAULT_ID 1

// patient struct
typedef struct
{
    int patientId;
    char name[MAX_PATIENT_NAME_LENGTH];
    int age;
    char diagnosis[MAX_DIAGNOSIS_LENGTH];
    int roomNumber;
} Patient;

// Patient management functions
void addPatientRecord();
void viewPatientRecords();
void searchPatientById();
void dischargePatient();


#endif //PATIENT_H
