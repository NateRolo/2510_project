/*
 * Author: Arsh M, Nathan O
 * Date: Jan 30, 2025
 * Purpose: Main driver of hospital system project.
 */

#include <stdio.h>
#include <string.h>
#include "patient.h"

// constants for menu
#define ENTER_PATIENT_RECORD 1
#define SEARCH_PATIENT_BY_ID 2
#define VIEW_ALL_PATIENTS 3
#define DISCHARGE_PATIENT 4
#define MANAGE_DOCTOR_SCHEDULE 5
#define EXIT_PROGRAM 6

#define INVALID_USER_INPUT (-1)

// function prototypes
void menu();


int main(void)
{
    menu();
    return 0;
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
                // manage doctor sched function
                    puts("manage doctor sched.\n");
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


