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

Doctor weeklySchedule[7][3];
const char* daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const char* timeOfDay[] = {"Morning", "Afternoon", "Evening"};

#endif //DOCTOR_H
