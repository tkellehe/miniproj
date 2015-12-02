// Test main.cpp for convert.h
// Example program
#include <iostream>
#include <string>

class B {
public:
    virtual char hello() {return 'B';}
};

class C {
public:
    virtual int hello() {return 65;}
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

template< typename TO, typename FROM >
TO& convert(FROM const& from) {
    struct parent {};

    struct child : public parent {
        child(FROM const& t): item(t){}
        mutable FROM item;
    };

    struct sibling : public parent {
        sibling(TO const& t): item(t){}
        mutable TO item;
    };

    parent* p = new child(from);
    return static_cast< sibling const& >(*p).item;
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