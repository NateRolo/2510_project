/*
 * Author: Arsh M, Nathan O
 * Date: Jan 30, 2025
 * Purpose: Main driver of hospital system project.
 */

#include <stdio.h>
#define INPUT_BUFFER 0
#define ENTER_PATIENT_RECORD 1
#define SEARCH_PATIENT_BY_ID 2
#define VIEW_ALL_PATIENTS 3
#define DISCHARGE_PATIENT 4
#define MANAGE_DOCTOR_SCHEDULE 5
#define EXIT_PROGRAM 6


int main(void)
{
    int userInput;

    do
    {
        userInput = INPUT_BUFFER;

        printf("Welcome to the [blank] Hospital Patient Management System.\n"
               "Enter one of the following options:\n"
               "1: Enter Patient Record.\n"
               "2: View All Patients.\n"
               "3: Search Patient by ID.\n"
               "4: Discharge Patient.\n"
               "5: Manage Doctor Schedule:\n"
               "6: Exit.");

        userInput = getchar();

        switch(userInput)
        {
            case ENTER_PATIENT_RECORD:
            case SEARCH_PATIENT_BY_ID:
            case VIEW_ALL_PATIENTS:
            case DISCHARGE_PATIENT:
            case MANAGE_DOCTOR_SCHEDULE:
            case EXIT_PROGRAM:
            default:
        }



    }
    while ()

    return 0;
}