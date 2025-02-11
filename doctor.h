//
// Created by arshd on 2/10/2025.
//

#ifndef DOCTOR_H
#define DOCTOR_H

typedef struct
{
    int doctorId;
    char name[100];
    int age;
} Doctor;

Doctor doctors[] = {
    {10, "Raymond Redington", 44},
    {20, "George Washington", 67},
    {30, "Sofia Gomez", 33}
};

#endif //DOCTOR_H
