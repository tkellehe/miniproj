//************************************************************************************************************
// typeof.h provides a function that returns the string of the type of the object passed in.
// NOTE: __PRETTY_FUNCTION__ is only supported in most C++ compilers in Visual C++ it is __FUNCSIG__
//       but it is not quite identical.
//************************************************************************************************************
#ifndef __TYPEOF_H__
#define __TYPEOF_H__

#include <string>

/**
 * typeof< TYPE >()
 * 
 * Takes in a type by templating it then converting that into a string.
 * 
 * @return Returns a std::string of the TYPE provided.
 */
template< typename TYPE >
std::string typeof() {
    // Uses the __PRETTY_FUNCTION__ that comes from C.
    std::string pretty_function = std::string(__PRETTY_FUNCTION__);
    // Used to transition through the pretty_function string.
    int c = 0;
    // Used to store the type as a string.
    std::string type = "";
    // Move c closer to where we need to start capturing.
    while(pretty_function[c++] != '=');
    // Skips the whitespace following the '=' character then starts capturing it.
    while(pretty_function[++c] != ';') type += pretty_function[c];
    // Returns what was captured.
    return type;
}

/**
 * typeof(TYPE type)
 * 
 * Takes in a type by extracting it from the object provided then converting that into a string.
 * 
 * @param TYPE type : The object that the type should be extracted from.
 * 
 * @return Returns a std::string of the TYPE provided.
 */
template< typename TYPE >
std::string typeof(TYPE type) {
    return typeof< TYPE >();
}


#endif; /* __TYPEOF_H__ */