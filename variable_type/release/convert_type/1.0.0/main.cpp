// Test main.cpp for convert.h version 1.0.0
#include <iostream>
#include <string>

class B {
public:
    virtual char hello() {return 'B';}
};

class C {
public:
    virtual int hello() {return 67;}
};

class D {
public:
    D(int j): i(j){}
    int i;
};

class E {
public:
    E(char d): c(d){}
    char c;
};

struct parent {};
        
template< typename T >
struct child : public parent {
    child(T const& t): item(t){}
    mutable T item;
};
        
template< typename T >
T& as(parent const & p) { return static_cast< child< T > const& >(p).item; }

template< typename TO, typename FROM >
TO& convert(FROM const& from) {
    parent* p = new child< FROM >(from);
    return as< TO >(*p);
};

int main()
{
    B b;
    std::cout << convert< C, B >(b).hello() << std::endl;
    C c;
    std::cout << convert< B, C >(c).hello() << std::endl;
    E e('D');
    D d = convert< D, E >(e);
    d.i++;
    std::cout << convert< E, D >(d).c << std::endl;
}