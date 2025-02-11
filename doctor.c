#include <stdio.h>
#include <string.h>
#include "doctor.h"

#define INVALID_INPUT (-1)
#define DAYS_IN_WEEK 7
#define TIMES_OF_DAY 3
#define DOCTOR_COUNT 3

typedef struct {
    int id;
    char name[100];
    int age;
} Doctor;

// Pre-defined array of doctors.
static const Doctor doctors[] = {
    {10, "Raymond Redington", 44},
    {20, "George Washington", 67},
    {30, "Sofia Gomez", 33}
};

// Schedule seperated into morning, afternoon, and evening.
static Doctor weeklyDoctorSchedule[7][3];

static const char* daysOfWeek[] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

static const char* timesOfDay[] = {
    "Morning",
    "Afternoon",
    "Evening"
};

// Private function prototypes (not in doctor.h)
static int chooseDoctor();
static int chooseDay();
static int chooseTime();

static int doctorExists(int);
static int dayExists(int);
static int timeExists(int);

static Doctor* getDoctorWithId(int);
static void clearInputBuffer();

void assignDoctor() {
    char proceed = 'y';

    const int doctorIndex = chooseDoctor();
    const int dayIndex = chooseDay();
    const int timeIndex = chooseTime();
    const Doctor* doctor = getDoctorWithId(doctorIndex);

    printf("Assigning Dr.%s for %s %s.\n", doctor->name,
                                                 daysOfWeek[dayIndex],
                                                 timesOfDay[timeIndex]);

    if (weeklyDoctorSchedule[dayIndex][timeIndex].id != 0) {
        printf("Another Doctor Already Assigned. Would You Like To Proceed? (y / n)\n");

        do {
            scanf(" %c", &proceed);
            clearInputBuffer();
        } while (proceed != 'y' && proceed != 'n');
    }

    if (proceed == 'y') {
        weeklyDoctorSchedule[dayIndex][timeIndex] = *doctor;
    }
}

void printFullSchedule() {
    for (int dayIndex = 0; dayIndex < DAYS_IN_WEEK; dayIndex++) {
        printf("---%s---\n", daysOfWeek[dayIndex]);
        printf("%-20sAssigned Doctor\n", "Time Of Day");

        for (int timeIndex = 0; timeIndex < TIMES_OF_DAY; timeIndex++) {
            printf("%-20s", timesOfDay[timeIndex]);
            if (strlen(weeklyDoctorSchedule[dayIndex][timeIndex].name) == 0) {
                printf("Unassigned!\n");
            } else {
                printf("%s\n", weeklyDoctorSchedule[dayIndex][timeIndex].name);
            }
        }
    }
}

static int chooseDoctor() {
    int doctorId;

    do {
        printf("Enter Doctor Id: ");

        if (scanf("%d", &doctorId) != 1) {
            printf("Invalid Input.\n");
            clearInputBuffer();
            doctorId = INVALID_INPUT;
        } else {
            doctorId = doctorExists(doctorId);
        }

    } while (doctorId == INVALID_INPUT);

    return doctorId;
}

static int doctorExists(const int doctorId)
{
    for (int i = 0; i < DOCTOR_COUNT; i++) {
        const Doctor doctor = doctors[i];

        if (doctor.id == doctorId) {
            return doctorId;
        }
    }

    return INVALID_INPUT;
}

static int chooseDay()
{
    int dayIndex;

    do {
        printf("Choose A Day:\n"
               "0: Monday\n"
               "1: Tuesday\n"
               "2: Wednesday\n"
               "3: Thursday\n"
               "4: Friday\n"
               "5: Saturday\n"
               "6: Sunday\n");

        if (scanf(" %d", &dayIndex) != 1) {
            printf("Invalid Input.\n");
            clearInputBuffer();
            dayIndex = INVALID_INPUT;
        } else {
            dayIndex = dayExists(dayIndex);
        }
    } while (dayIndex == INVALID_INPUT);

    return dayIndex;
}

static int dayExists(const int dayIndex) {
    if (0 <= dayIndex && dayIndex < DAYS_IN_WEEK) {
        return dayIndex;
    }

    printf("Invalid Day.\n");
    return INVALID_INPUT;
}

static int chooseTime()
{
    int timeIndex;

    do {
        printf("Choose A Time Of Day:\n"
               "0: Morning\n"
               "1: Afternoon\n"
               "2: Evening\n");

        if (scanf("%d", &timeIndex) != 1) {
            printf("Invalid Input.\n");
            clearInputBuffer();
            timeIndex = INVALID_INPUT;
        } else {
            timeIndex = timeExists(timeIndex);
        }
    } while (timeIndex == INVALID_INPUT);

    return timeIndex;
}

static int timeExists(const int timeIndex) {
    if (0 <= timeIndex && timeIndex < TIMES_OF_DAY) {
        return timeIndex;
    }

    printf("Invalid Time.\n");
    return INVALID_INPUT;
}

static Doctor* getDoctorWithId(const int doctorId) {
    for (int i = 0; i < DOCTOR_COUNT; i++) {
        if (doctors[i].id == doctorId) {
            return &doctors[i];
        }
    }

    return nullptr;
}

static void clearInputBuffer() {
    while (getchar() != '\n');
}
