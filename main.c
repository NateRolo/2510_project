/*
 * Author: Arsh M, Nathan O
 * Date: Jan 30, 2025
 * Purpose: Main driver of the hospital system project.
 *          This file provides a menu-driven interface for managing patient records.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "patient_management.h"
#include "utils.h"
#include "doctor_schedule.h"
#include "doctor_data.h"
#include "patient_data.h"

// Constants representing menu options
#define ENTER_PATIENT_RECORD 1
#define SEARCH_PATIENT_BY_ID 2
#define VIEW_ALL_PATIENTS 3
#define DISCHARGE_PATIENT 4
#define MANAGE_DOCTOR_SCHEDULE 5
#define PATIENT_ADMIT_REPORT 6
#define PATIENT_DISCHARGE_REPORT 7
#define DOC_SCHE_REPORT 8
#define ROOM_USAGE_REPORT 9
#define EXIT_PROGRAM 10

#define DEFAULT_VALUE (-1)  
#define VALID_INPUT 1       

// Function prototype for the main menu
void menu();
void doctorMenu();
int getPatientReportChoice();

/*
 * Function: main
 * --------------
 * Entry point of the hospital management system.
 * Calls the menu function to interact with the user.
 */
int main(void)
{
    // Initialize systems
    initializePatientSystem();
    initializeDoctors();
    initializeSchedule();

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
               "6: Patient Admission Report Menu\n"
               "7: Patient Discharge Report Menu\n"
               "8: Doctor Schedule Report\n"
               "9: Room Usage Report\n"
               "10: Exit.\n");

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
            clearInputBuffer();
            doctorMenu();
            break;
        case PATIENT_ADMIT_REPORT:
            clearInputBuffer();
            displayPatientReport(getPatientReportChoice());
            break;
        case PATIENT_DISCHARGE_REPORT:
            clearInputBuffer();
            displayDischargedPatientReport(getPatientReportChoice());
            break;
        case DOC_SCHE_REPORT:
            clearInputBuffer();
            printDoctorUtilizationReport();
            break;
        case ROOM_USAGE_REPORT:
            clearInputBuffer();
            displayRoomUsageReport();
            break;
        case EXIT_PROGRAM:
            puts("Exiting program, have a nice day!\n");
            clearMemory();
            return;
        default:
            printf("Invalid option. Please enter a number between 1 and 6.\n");
        }
    } while (userInput != EXIT_PROGRAM);
}

/*
 * Function: doctorMenu
 * --------------
 * Displays a menu with options for managing doctor schedules.
 * Repeats until the user chooses to exit the program.
 */
void doctorMenu()
{
    int userInput;

    do
    {
        userInput = DEFAULT_VALUE;

        printf("\nDoctor Menu\n"
               "1: Assign Doctor\n"
               "2: Print Full Schedule\n"
               "3: Exit\n");

        if(scanf("%d", &userInput) != VALID_INPUT)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
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
                puts("Exiting doctor menu...\n");
                return;
            default:
                printf("Not a valid input, please enter "
                       "one of the options above.\n");
                userInput = DEFAULT_VALUE;
        }
    } while (userInput != EXIT_PROGRAM);
}

int getPatientReportChoice()
{
    int choice;

    do {
        printf("Select timeframe:\n");
        printf("1. Daily\n");
        printf("2. Weekly\n");
        printf("3. Monthly\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            clearInputBuffer();  // Clear invalid input
            choice = 0;  // Reset choice to force re-entry
        }
    } while (choice < 1 || choice > 3);

    printf("\n");

    return choice;
}
