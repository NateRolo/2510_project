/*
 * Author: Arsh M, Nathan O
 * Date: Feb 12, 2025
 * Purpose: This file contains the implementation of the doctor scheduling system.
 *          It provides functionality for assigning doctors to specific time slots
 *          and displaying the complete weekly schedule.
 */

#include "doctor.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"

// Private constants (private to doctor.c)
static constexpr int INVALID_INPUT = -1;
static constexpr int DAYS_IN_WEEK = 7;
static constexpr int TIMES_OF_DAY = 3;
static constexpr int DOCTOR_COUNT = 3;
static constexpr int NAME_LENGTH = 100;
static constexpr int UNASSIGNED_ID = 0;
static constexpr int MIN_INDEX = 0;

static constexpr int NO_DOCTOR = 0;
static constexpr int RAYMOND_ID = 10;
static constexpr int GEORGE_ID = 20;
static constexpr int SOFIA_ID = 30;
static constexpr int RAYMOND_AGE = 44;
static constexpr int GEORGE_AGE = 67;
static constexpr int SOFIA_AGE = 33;

/*
 * Structure representing a doctor in the system.
 * Contains basic identifying information and personal details.
 */
typedef struct
{
    int  id;                     
    char name[NAME_LENGTH];      
    int  age;                    
} Doctor;

/* Pre-defined array of available doctors in the system */
static const Doctor doctors[] = { { RAYMOND_ID, "Raymond Redington", RAYMOND_AGE },
                                  { GEORGE_ID, "George Washington", GEORGE_AGE },
                                  { SOFIA_ID, "Sofia Gomez", SOFIA_AGE } };

/* Weekly schedule matrix organized by day and time slot */
static Doctor weeklyDoctorSchedule[DAYS_IN_WEEK][TIMES_OF_DAY];

/* Array of day names for display purposes */
static const char *daysOfWeek[] = { "Monday",
                                   "Tuesday",
                                   "Wednesday",
                                   "Thursday",
                                   "Friday",
                                   "Saturday",
                                   "Sunday" };

/* Array of time slot names for display purposes */
static const char *timesOfDay[] = { "Morning",
                                   "Afternoon",
                                   "Evening" };

/* Function prototypes for internal helper functions */
static int chooseDoctor(void);
static int chooseDay(void);
static int chooseTime(void);

static int doctorExists(int);
static int dayExists(int);
static int timeExists(int);

static const Doctor *getDoctorWithId(int);

/*
 * Handles the process of assigning a doctor to a specific time slot.
 * Prompts for doctor, day, and time selection. Handles conflicts with
 * existing assignments by asking for confirmation before overwriting.
 */
void assignDoctor()
{
    char proceed = YES;

    const int     doctorIndex = chooseDoctor();
    const int     dayIndex    = chooseDay();
    const int     timeIndex   = chooseTime();
    const Doctor *doctor      = getDoctorWithId(doctorIndex);

    printf("Assigning Dr.%s for %s %s.\n", 
            doctor->name, 
            daysOfWeek[dayIndex], 
            timesOfDay[timeIndex]);

    if(weeklyDoctorSchedule[dayIndex][timeIndex].id != UNASSIGNED_ID)
    {
        printf("Another Doctor Already Assigned. Would You Like To Proceed? (y / n)\n");

        do
        {
            scanf(" %c", &proceed);
            clearInputBuffer();
        }
        while(proceed != YES && proceed != NO);
    }

    if(proceed == YES)
    {
        weeklyDoctorSchedule[dayIndex][timeIndex] = *doctor;
    }
}

/*
 * Displays the complete weekly schedule showing all assignments.
 * Lists each day and time slot with either the assigned doctor's name
 * or indicates if the slot is unassigned.
 */
void printFullSchedule()
{
    for(int dayIndex = 0; dayIndex < DAYS_IN_WEEK; dayIndex++)
    {
        printf("---%s---\n", daysOfWeek[dayIndex]);
        printf("%-20sAssigned Doctor\n", "Time Of Day");

        for(int timeIndex = 0; timeIndex < TIMES_OF_DAY; timeIndex++)
        {
            printf("%-20s", timesOfDay[timeIndex]);
            if(strlen(weeklyDoctorSchedule[dayIndex][timeIndex].name) == NO_DOCTOR)
            {
                printf("Unassigned!\n");
            }
            else
            {
                printf("%s\n", weeklyDoctorSchedule[dayIndex][timeIndex].name);
            }
        }
    }
}

/* 
 * Prompts for and validates a doctor ID selection.
 * Continues prompting until a valid doctor ID is entered.
 */
static int chooseDoctor()
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

/*
 * Validates if a given doctor ID exists in the system.
 * Returns the ID if valid, INVALID_INPUT otherwise.
 */
static int doctorExists(const int doctorId)
{
    for(int i = 0; i < DOCTOR_COUNT; i++)
    {
        const Doctor doctor = doctors[i];

        if(doctor.id == doctorId)
        {
            return doctorId;
        }
    }

    return INVALID_INPUT;
}

/*
 * Prompts for and validates a day selection.
 * Displays numbered options and continues until valid input is received.
 */
static int chooseDay()
{
    int dayIndex;

    do
    {
        printf("Choose A Day:\n"
               "0: Monday\n"
               "1: Tuesday\n"
               "2: Wednesday\n"
               "3: Thursday\n"
               "4: Friday\n"
               "5: Saturday\n"
               "6: Sunday\n");

        if(scanf(" %d", &dayIndex) != SUCCESSFUL_READ)
        {
            printf("Invalid Input.\n");
            clearInputBuffer();
            dayIndex = INVALID_INPUT;
        }
        else
        {
            dayIndex = dayExists(dayIndex);
        }
    }
    while(dayIndex == INVALID_INPUT);

    return dayIndex;
}

/*
 * Validates if a given day index is within valid range.
 * Returns the index if valid, INVALID_INPUT otherwise.
 */
static int dayExists(const int dayIndex)
{
    if(MIN_INDEX <= dayIndex && 
       dayIndex < DAYS_IN_WEEK)
    {
        return dayIndex;
    }

    printf("Invalid Day.\n");
    return INVALID_INPUT;
}

/*
 * Prompts for and validates a time slot selection.
 * Displays numbered options and continues until valid input is received.
 */
static int chooseTime()
{
    int timeIndex;

    do
    {
        printf("Choose A Time Of Day:\n"
               "0: Morning\n"
               "1: Afternoon\n"
               "2: Evening\n");

        if(scanf("%d", &timeIndex) != SUCCESSFUL_READ)
        {
            printf("Invalid Input.\n");
            clearInputBuffer();
            timeIndex = INVALID_INPUT;
        }
        else
        {
            timeIndex = timeExists(timeIndex);
        }
    }
    while(timeIndex == INVALID_INPUT);

    return timeIndex;
}

/*
 * Validates if a given time slot index is within valid range.
 * Returns the index if valid, INVALID_INPUT otherwise.
 */
static int timeExists(const int timeIndex)
{
    if(MIN_INDEX <= timeIndex && 
       timeIndex < TIMES_OF_DAY)
    {
        return timeIndex;
    }

    printf("Invalid Time.\n");
    return INVALID_INPUT;
}

/*
 * Retrieves a pointer to a doctor with the specified ID.
 * Returns NULL if no matching doctor is found.
 */
static const Doctor *getDoctorWithId(const int doctorId)
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
