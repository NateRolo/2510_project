#include <stdio.h>
#include <string.h>
#include "doctor.h"

typedef struct {
    int doctorId;
    char name[100];
    int age;
} Doctor;

static Doctor doctors[] = {
    {10, "Raymond Redington", 44},
    {20, "George Washington", 67},
    {30, "Sofia Gomez", 33}
};

static Doctor weeklySchedule[7][3]; // Now static, private to doctor.c

static const char* daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
static const char* timeOfDay[] = {"Morning", "Afternoon", "Evening"};

// Private function prototypes (not in doctor.h)
static char* getDayOfWeek(int);
static char* getTimeOfDay(int);
static int doctorExists(int);
static int dayExists(int);
static int timeOfDayExists(int);
static void clearInputBuffer();

void assignDoctor() {
    int doctorId = -1, day = -1, time = -1;
    char proceed = 'y';

    do {
        printf("Choose A Doctor:\n"
               "0: Raymond Redington\n"
               "1: George Washington\n"
               "2: Sofia Gomez\n");

        if (scanf("%d", &doctorId) != 1) {
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

        if (scanf("%d", &day) != 1) {
            printf("Please enter a number.\n");
            clearInputBuffer();
        } else {
            day = dayExists(day);
        }
    } while (day == -1);

    do {
        printf("Choose A Time Of Day:\n"
               "0: Morning\n"
               "1: Afternoon\n"
               "2: Evening\n");

        if (scanf("%d", &time) != 1) {
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
            scanf(" %c", &proceed); // Space before %c fixes buffer issues
            clearInputBuffer();
        } while (proceed != 'y' && proceed != 'n');
    }

    if (proceed == 'y') {
        weeklySchedule[day][time] = doctors[doctorId];
    }
}

void printFullSchedule() {
    for (int i = 0; i < 7; i++) {
        printf("---%s---\n", getDayOfWeek(i));
        printf("%-20sAssigned Doctor\n", "Time Of Day");

        for (int j = 0; j < 3; j++) {
            printf("%-20s", getTimeOfDay(j));
            if (strlen(weeklySchedule[i][j].name) == 0) {
                printf("Unassigned!\n");
            } else {
                printf("%s\n", weeklySchedule[i][j].name);
            }
        }
    }
}

// Private Helper Functions
static char* getDayOfWeek(int index) {
    return (char*)daysOfWeek[index];
}

static char* getTimeOfDay(int index) {
    return (char*)timeOfDay[index];
}

static int doctorExists(int idIndex) {
    if (idIndex >= 0 && idIndex < 3) {
        return idIndex;
    }
    printf("Doctor Doesn't Exist.\n");
    return -1;
}

static int dayExists(int dayIndex) {
    if (dayIndex >= 0 && dayIndex < 7) {
        return dayIndex;
    }
    printf("Day Doesn't Exist.\n");
    return -1;
}

static int timeOfDayExists(int timeIndex) {
    if (timeIndex >= 0 && timeIndex < 3) {
        return timeIndex;
    }
    printf("Time Of Day Doesn't Exist.\n");
    return -1;
}

static void clearInputBuffer() {
    while (getchar() != '\n');
}
