//************************************************************************************************************
// convert.h provides a function called "convert" that allows for ease of
// forcing one type into another without really thinking twice about anything.
//************************************************************************************************************
#ifndef __CONVERT_H__
#define __CONVERT_H__

namespace CONVERT {
	// Parent struct used to create a basic object that does not care about type.
	struct parent {};
    
    // Child struct where the type is specified when stored and can be redefined when cast from a parent.
	template< typename T >
	struct child : public parent {
	    child(T const& t): item(t){}
	    mutable T item;
	};
	
	// The function that casts a parent into a child and extracts the object contained.
	// The object within is now the type of T.
	template< typename T >
	T& as(parent const & p) { return static_cast< child< T > const& >(p).item; }

	/**
     * Takes the TO type and changes it to the FROM type utilizing parent, child, and as.
     * 
     * @param FROM from : A type of object that can fit within a TO type.
     * 
     * @return Returns the object now referenced as a TO type.
	 */
	template< typename TO, typename FROM >
	TO& convert(FROM const& from) {
	    parent* p = new child< FROM >(from);
	    return as< TO >(*p);
	};
}

#endif; /* __CONVERT_H__ */