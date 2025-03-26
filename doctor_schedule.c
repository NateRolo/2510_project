/*
 * Author: Arsh M, Nathan O
 * Date: Feb 12, 2025
 * Purpose: This file contains the implementation of the doctor scheduling system.
 */

#include "doctor_schedule.h"
#include <stdio.h>
#include <string.h>
#include "doctor_data.h"
#include "utils.h"

#define DAYS_IN_WEEK 7
#define TIMES_OF_DAY 3

#define NO_DOCTOR 0

// Private constants
static const int INVALID_INPUT = -1;
static const int UNASSIGNED_ID = 0;
static const int MIN_INDEX     = 0;

/* Weekly schedule matrix organized by day and time slot */
static Doctor weeklyDoctorSchedule[DAYS_IN_WEEK][TIMES_OF_DAY];

/* Array of day names for display purposes */
static const char *daysOfWeek[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

/* Array of time slot names for display purposes */
static const char *timesOfDay[] = { "Morning", "Afternoon", "Evening" };

/* Function prototypes for internal helper functions */
static int chooseDay(void);
static int chooseTime(void);
static int dayExists(int);
static int timeExists(int);
static void writeScheduleToFile(void);
static void updateScheduleFile(void);

/*
 * Initializes the weekly schedule from file or with default values
 */
void initializeSchedule(void)
{
    FILE *pSchedule = fopen("schedule.dat", "rb");

    if(pSchedule != NULL)
    {
        size_t read = fread(weeklyDoctorSchedule, sizeof(Doctor), 
                           DAYS_IN_WEEK * TIMES_OF_DAY, pSchedule);

        if(read != DAYS_IN_WEEK * TIMES_OF_DAY)
        {
            fclose(pSchedule);
            puts("\nError reading from schedule.dat. Initializing with default settings.");
            initializeScheduleDefault();
            return;
        }

        fclose(pSchedule);
        puts("\nSchedule successfully loaded from file.");
    }
    else
    {
        puts("\nUnable to read schedule.dat. Schedule initialized with default settings.");
        initializeScheduleDefault();
    }
}

/*
 * Initializes the schedule with empty slots
 */
void initializeScheduleDefault(void)
{
    for(int day = 0; day < DAYS_IN_WEEK; day++)
    {
        for(int time = 0; time < TIMES_OF_DAY; time++)
        {
            weeklyDoctorSchedule[day][time] = (Doctor) { UNASSIGNED_ID, "", 0 };
        }
    }
    
    // Create initial schedule file
    writeScheduleToFile();
}

/*
 * Updates the schedule file with current assignments
 */
static void writeScheduleToFile(void)
{
    FILE *pSchedule = fopen("schedule.dat", "wb");
    
    if(pSchedule == NULL)
    {
        puts("\nUnable to create schedule.dat.");
        return;
    }

    size_t written = fwrite(weeklyDoctorSchedule, sizeof(Doctor), 
                           DAYS_IN_WEEK * TIMES_OF_DAY, pSchedule);
    
    if(written == DAYS_IN_WEEK * TIMES_OF_DAY)
    {
        puts("\nSchedule successfully saved to file.");
    }
    else
    {
        puts("\nError saving schedule to file.");
    }
    
    fclose(pSchedule);
}

/*
 * Handles the process of assigning a doctor to a specific time slot.
 * Prompts for doctor, day, and time selection. Handles conflicts with
 * existing assignments by asking for confirmation before overwriting.
 */
void assignDoctor(void)
{
    char proceed = YES;

    const int     doctorId  = chooseDoctor();
    const int     dayIndex  = chooseDay();
    const int     timeIndex = chooseTime();
    const Doctor *doctor    = getDoctorWithId(doctorId);

    printf("Assigning Dr.%s for %s %s.\n", doctor->name, daysOfWeek[dayIndex], timesOfDay[timeIndex]);

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
        writeScheduleToFile();  // Update file after assignment
    }
}

/*
 * Displays the complete weekly schedule showing all assignments.
 * Lists each day and time slot with either the assigned doctor's name
 * or indicates if the slot is unassigned.
 */
void printFullSchedule(void)
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
 * Prompts for and validates a day selection.
 * Displays numbered options and continues until valid input is received.
 */
static int chooseDay(void)
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
    if(MIN_INDEX <= dayIndex && dayIndex < DAYS_IN_WEEK)
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
static int chooseTime(void)
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
    if(MIN_INDEX <= timeIndex && timeIndex < TIMES_OF_DAY)
    {
        return timeIndex;
    }

    printf("Invalid Time.\n");
    return INVALID_INPUT;
}
