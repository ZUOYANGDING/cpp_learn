#pragma once
class Classroom{
    private:
        int people[100];
        int score;
    public:
        Classroom(int num);
        void add(int who, int score);
        void sub(int who, int score);
        int getScore(int who) const;
};