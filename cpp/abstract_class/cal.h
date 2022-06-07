#pragma once
#include "base.h"

class Cal: public Base {
    private:
        int param;
    public:
        Cal();
        Cal(int a);
        // Base class's destructor is virtural, Cal should use virtual destructor
        virtual ~Cal();
        int getParam() const;
        void setParam(int a);
        void add(int a);
        void sub(int a);
        void print() const;
};