/*
 * Author: Arsh M, Nathan O
 * Date: Feb 12, 2025
 * Purpose: This file contains the definition of the doctor management system.
 *          It provides functionality for managing doctor information.
 */

#ifndef DOCTOR_MANAGEMENT_H
#define DOCTOR_MANAGEMENT_H

#define NAME_LENGTH 100

// Doctor IDs
#define RAYMOND_ID 10
#define GEORGE_ID 20
#define SOFIA_ID 30

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

/*
 * Function: getDoctorWithId
 * ----------------------------
 * Retrieves a pointer to a doctor with the specified ID.
 * Returns NULL if no matching doctor is found.
 */
const Doctor *getDoctorWithId(int doctorId);

/*
 * Function: chooseDoctor
 * ----------------------------
 * Prompts for and validates a doctor ID selection.
 * Returns the selected doctor ID.
 */
int chooseDoctor(void);

/*
 * Function: initializeDoctors
 * ----------------------------
 * Initializes the doctor database with predefined doctors.
 */
void initializeDoctors(void);

#endif // DOCTOR_MANAGEMENT_H
