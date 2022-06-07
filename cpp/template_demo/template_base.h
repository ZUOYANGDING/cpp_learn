#pragma once

template<class T> class A{
    private:
        T a;
        T b;
    public:
        A(T, T);
        ~A();
        void swap();
        void print() const;
};
