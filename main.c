/*
 * Author: Arsh M, Nathan O
 * Date: Jan 30, 2025
 * Purpose: Main driver of the hospital system project.
 *          This file provides a menu-driven interface for managing patient records.
 */

#include <stdio.h>
#include <string.h>
#include "patient.h"
#include "utils.h"
#include "doctor.h"

// Constants representing menu options
#define ENTER_PATIENT_RECORD 1
#define SEARCH_PATIENT_BY_ID 2
#define VIEW_ALL_PATIENTS 3
#define DISCHARGE_PATIENT 4
#define MANAGE_DOCTOR_SCHEDULE 5
#define EXIT_PROGRAM 6

#define DEFAULT_VALUE (-1)  
#define VALID_INPUT 1       

// Function prototype for the main menu
void menu();

/*
 * Function: main
 * --------------
 * Entry point of the hospital management system.
 * Calls the menu function to interact with the user.
 */
int main(void)
{
    menu();
    return 0;
}

/*
 * Function: menu
 * --------------
 * Displays a menu with options for managing patient records.
 * Repeats until the user chooses to exit the program.
 */
void menu()
{
    int userInput;

    do
    {
        userInput = DEFAULT_VALUE;  

        // Display menu options
        printf("\nWelcome to the BCIT Hospital Patient Management System.\n"
               "Enter one of the following options:\n"
               "1: Enter Patient Record.\n"
               "2: Search Patient by ID.\n"
               "3: View All Patients.\n"
               "4: Discharge Patient.\n"
               "5: Manage Doctor Schedule.\n"
               "6: Exit.\n");

        // Read user input and validate
        if (scanf("%d", &userInput) != VALID_INPUT)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer(); 
            continue;
        }

        // Process user selection
        switch (userInput)
        {
        case ENTER_PATIENT_RECORD:
            clearInputBuffer();
            addPatientRecord();
            break;
        case SEARCH_PATIENT_BY_ID:
            clearInputBuffer();
            searchPatientById();
            break;
        case VIEW_ALL_PATIENTS:
            clearInputBuffer();
            viewPatientRecords();
            break;
        case DISCHARGE_PATIENT:
            clearInputBuffer();
            dischargePatient();
            break;
        case MANAGE_DOCTOR_SCHEDULE:
            puts("Manage doctor schedule feature coming soon.\n");
            break;
        case EXIT_PROGRAM:
            puts("Exiting program, have a nice day!\n");
            return;
        default:
            printf("Invalid option. Please enter a number between 1 and 6.\n");
        }

        switch(userInput)
        {
            case 1:
                clearInputBuffer();
                assignDoctor();
                break;
            case 2:
                clearInputBuffer();
                printFullSchedule();
                break;
            case 3:
                puts("Exiting program, have a nice day!\n");
                return;
            default:
                printf("Not a valid input, please enter "
                       "one of the options above.\n");
                userInput = INVALID_USER_INPUT;
        }
    } while (userInput != EXIT_PROGRAM);
}
