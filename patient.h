/*
 * Author: Arsh M, Nathan O
 * Date: 2/6/2025
 * Purpose: This file represents a patient with patient id, name, age, diagonsis, and room number.
 */


#ifndef PATIENT_H
#define PATIENT_H

typedef struct
{
    int patientId;
    char name[100];
    int age;
    char diagnosis[255];
    int roomNumber;
} Patient;

#endif //PATIENT_H
