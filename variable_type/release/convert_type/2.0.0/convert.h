//************************************************************************************************************
// convert.h provides a function called "convert" that allows for ease of
// forcing one type into another without really thinking twice about anything.
//************************************************************************************************************
#ifndef __CONVERT_H__
#define __CONVERT_H__

/**
 * Takes the TO type and changes it to the FROM type utilizing parent, child, and as.
 * 
 * @param FROM from : A type of object that can fit within a TO type.
 * 
 * @return Returns the object now referenced as a TO type.
 */
template< typename TO, typename FROM >
TO& convert(FROM const& from) {
    // Acts as a medium for the conversion between child to sibling.
    struct parent {};

    // Stores the FROM type to be converted to a TO type.
    struct child : public parent {
        child(FROM const& t): item(t){}
        mutable FROM item;
    };

    // Used to force the FROM type to a TO type.
    struct sibling : public parent {
        sibling(TO const& t): item(t){}
        mutable TO item;
    };

    // Creating a child with the from data then placing it into a parent such that cannot determine type.
    parent* p = new child(from);
    // By casting child into a sibling the type of the data stored gets changed to TO.
    return static_cast< sibling const& >(*p).item;
};

#endif; /* __CONVERT_H__ */