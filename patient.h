/*
 * Author: Nathan Oloresisimo
 * Date: 2/6/2025
 * Purpose:
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
};

#endif //PATIENT_H
