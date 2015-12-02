#ifndef __JAR_H__
#define __JAR_H__

struct jar {};
        
template< typename Type >
struct container : public jar {
    container(Type const& t): item(t){}
    mutable Type item;
};
        
template< typename AS >
AS& as(jar const & j) { return static_cast< container< AS > const& >(j).item; }

#endif /* __JAR_H__ */