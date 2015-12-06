// Test main.cpp for jar.h
// Example program
#include <iostream>
#include <string>

struct jar {
    virtual jar* copy() const = 0;
};
        
template< typename Type >
struct cup : public jar {
    cup(Type const& t): content(t){}
    mutable Type content;

    virtual jar* copy() const {
        return new cup< Type >(content);
    }
};
        
template< typename AS >
AS& as(jar const & j) { return static_cast< cup< AS > const& >(j).content; }

struct jug : public jar {
    jug(): container(0){}
    
    ~jug(){ delete container; }
    
    template< typename Type >
    jug(Type const& t): container(new cup< Type >(t)){}
    
    jug(jug const& other): container(other.container ? other.container->copy() : 0){}
    
    jug(jar* j): container(j){}
    
    template< typename Type >
    jug& operator=(Type const& rhs) {
        jug j(rhs);
        jar* temp = j.container;
        j.container = container;
        container = temp;
        return *this;
    }
    
    jug& operator=(jug const& rhs) {
        jug j(rhs);
        jar* temp = j.container;
        j.container = container;
        container = temp;
        return *this;
    }
    
    virtual jar* copy() const { return new jug(container); }
    
    jar* container;
};

template< typename AS >
AS& as(jug const& j) {
    return as< AS >(*j.container);
}

template< typename OTHER >
OTHER operator+(OTHER const& other, jug const& j) {
    return other + as< OTHER >(j);
}
template< typename OTHER >
OTHER operator+(jug const& j, OTHER const& other) {
    return as< OTHER >(j) + other;
}

template< typename OTHER >
OTHER operator*(OTHER const& other, jug const& j) {
    return other * as< OTHER >(j);
}
template< typename OTHER >
OTHER operator*(jug const& j, OTHER const& other) {
    return as< OTHER >(j) * other;
}

template< typename OTHER >
OTHER operator/(OTHER const& other, jug const& j) {
    return other / as< OTHER >(j);
}
template< typename OTHER >
OTHER operator/(jug const& j, OTHER const& other) {
    return as< OTHER >(j) / other;
}

template< typename OTHER >
OTHER operator==(OTHER const& other, jug const& j) {
    return other == as< OTHER >(j);
}
template< typename OTHER >
OTHER operator==(jug const& j, OTHER const& other) {
    return as< OTHER >(j) == other;
}

int main()
{
    jar* j = new cup< std::string >("Hello World");
    std::cout << as< std::string >(*j) << std::endl;
    jug x = 1000;
    std::cout << as< int >(x) << std::endl;
    std::cout << (x + 100) << std::endl;
    // Maybe change to thing, anything, any...
}