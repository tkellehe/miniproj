// Test main.cpp for jar.h
// Example program
#include <iostream>
#include <string>

struct jar {};
        
template< typename Type >
struct container : public jar {
    container(Type const& t): item(t){}
    mutable Type item;
};
        
template< typename AS >
AS& as(jar const & j) { return static_cast< container< AS > const& >(j).item; }

int main()
{
    jar* j = new container< std::string >("Hello World");
    std::cout << as< std::string >(*j) << std::endl;
}