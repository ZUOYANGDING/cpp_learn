#include "student.h"
Classroom::Classroom(int num) {
    score = num;
    for (int i=0; i<100; i++) {
        people[i] = num;
    }
}

void Classroom::add(int who, int score) {
    people[who] += score;
}

void Classroom::sub(int who, int score) {
    people[who] -= score;
}

int Classroom::getScore(int who) const {
    return people[who];
}

