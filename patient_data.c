/*
 * Author: Arsh M, Nathan O
 * Date: Feb 6, 2025
 * Purpose: This file implements functions for creating, validating, and displaying patient data.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "patient_data.h"
#include "utils.h"

// Private constants
#define IS_EMPTY 0

static const int MAX_ROOM_NUMBER = 50;
static const int MIN_ROOM_NUMBER = 1;

static const int MIN_PATIENT_NAME_LENGTH = 1;
static const int MIN_DIAGNOSIS_LENGTH = 1;

static const int MIN_AGE_YEARS = 0;
static const int MAX_AGE_YEARS = 120;

static const int NULL_TERMINATOR = 0;
static const int NO_LETTERS = 0;
static const int HAS_LETTERS = 1;

/*
 * Creates a new patient record with the given details.
 */
Patient createPatient(const char patientName[],
                      int patientAge,
                      const char patientDiagnosis[],
                      int roomNumber,
                      int patientId)
{
    Patient newPatient;
    newPatient.patientId = patientId;
    strcpy(newPatient.name, patientName);
    newPatient.ageInYears = patientAge;
    strcpy(newPatient.diagnosis, patientDiagnosis);
    newPatient.roomNumber = roomNumber;
    return newPatient;
}

/*
 * Validates if a patient name is acceptable.
 */
int validatePatientName(char patientName[])
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


    int hasLetter = NO_LETTERS;

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

/*
 * Validates if a patient age is within acceptable range.
 */
int validatePatientAge(int patientAge)
{
    if (patientAge < MIN_AGE_YEARS || 
        patientAge > MAX_AGE_YEARS)
    {
        return IS_NOT_VALID;
    }

    return IS_VALID;
}

/*
 * Validates if a patient diagnosis is acceptable.
 */
int validatePatientDiagnosis(char patientDiagnosis[])
{
    if (patientDiagnosis == NULL)
    {
        return IS_NOT_VALID;
    }

    if (strlen(patientDiagnosis) == IS_EMPTY ||
        strlen(patientDiagnosis) > MAX_DIAGNOSIS_LENGTH)
    {
        return IS_NOT_VALID;
    }

    int hasLetter = NO_LETTERS;

    for (int i = 0; patientDiagnosis[i] != '\0'; i++)
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

    if (hasLetter == NO_LETTERS)
    {
        return IS_NOT_VALID;
    }

    return IS_VALID;
}

/*
 * Validates if a room number is within acceptable range.
 * Note: This function only checks the range, not occupancy.
 */
int validateRoomNumber(int roomNumber)
{
    if (roomNumber < MIN_ROOM_NUMBER || 
        roomNumber > MAX_ROOM_NUMBER)
    {
        return IS_NOT_VALID;
    }

    return IS_VALID;
}

/*
 * Displays detailed information about a patient.
 */
void printPatient(const Patient patient)
{
    printf("---------------------------------------\n");
    printf("Patient ID: %d\n", patient.patientId);
    printf("Patient Name: %s\n", patient.name);
    printf("Age: %d\n", patient.ageInYears);
    printf("Diagnosis: %s\n", patient.diagnosis);
    printf("Room Number: %d\n", patient.roomNumber);
    printf("---------------------------------------\n");
}

