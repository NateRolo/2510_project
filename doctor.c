#include <stdio.h>
#include <string.h>
#include "doctor.h"

void clearInputBuffer();
char* getDayOfWeek(int);
char* getTimeOfDay(int);
int doctorExists(int);
int dayExists(int);
int timeOfDayExists(int);


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

    if (weeklySchedule[day][time].doctorId != 0) {
        printf("Doctor Already Assigned. Would you like to proceed? (y / n)\n");
        do {
            scanf("%c", &proceed);
            clearInputBuffer();
        } while (proceed != 'y' &&
            proceed != 'n');
    }

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

void clearInputBuffer()
{
    while(getchar() != '\n');
}
