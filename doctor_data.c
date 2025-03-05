/*
 * Author: Arsh M, Nathan O
 * Date: Feb 12, 2025
 * Purpose: This file contains the implementation of the doctor management system.
 */

#include <stdio.h>
#include <string.h>
#include "doctor_data.h"
#include "utils.h"

// Doctor ages
#define RAYMOND_AGE 44
#define GEORGE_AGE 67
#define SOFIA_AGE 33

#define DOCTOR_COUNT 3

// Private constants
static const int INVALID_INPUT = -1;
static const int MIN_INDEX     = 0;

/* Pre-defined array of available doctors in the system */
static Doctor doctors[DOCTOR_COUNT];

/*
 * Initializes the doctor database with predefined doctors.
 */
void initializeDoctors(void)
{
    doctors[0] = (Doctor) { RAYMOND_ID, "Raymond Redington", RAYMOND_AGE };
    doctors[1] = (Doctor) { GEORGE_ID, "George Washington", GEORGE_AGE };
    doctors[2] = (Doctor) { SOFIA_ID, "Sofia Gomez", SOFIA_AGE };
}

/*
 * Validates if a given doctor ID exists in the system.
 * Returns the ID if valid, INVALID_INPUT otherwise.
 */
static int doctorExists(const int doctorId)
{
    for(int i = 0; i < DOCTOR_COUNT; i++)
    {
        if(doctors[i].id == doctorId)
        {
            return doctorId;
        }
    }

    return INVALID_INPUT;
}

/*
 * Retrieves a pointer to a doctor with the specified ID.
 * Returns NULL if no matching doctor is found.
 */
const Doctor *getDoctorWithId(const int doctorId)
{
    for(int i = 0; i < DOCTOR_COUNT; i++)
    {
        if(doctors[i].id == doctorId)
        {
            return &doctors[i];
        }
    }
    return NULL;
}

/*
 * Prompts for and validates a doctor ID selection.
 * Continues prompting until a valid doctor ID is entered.
 */
int chooseDoctor(void)
{
    int doctorId;

    do
    {
        printf("Enter Doctor Id: ");

        if(scanf("%d", &doctorId) != SUCCESSFUL_READ)
        {
            printf("Invalid Input.\n");
            clearInputBuffer();
            doctorId = INVALID_INPUT;
        }
        else
        {
            doctorId = doctorExists(doctorId);
        }
    }
    while(doctorId == INVALID_INPUT);

    return doctorId;
}
