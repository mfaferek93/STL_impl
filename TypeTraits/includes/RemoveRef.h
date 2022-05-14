#ifndef REMOVE_REF
#define REMOVE_REF

template<typename T>
struct RemoveRef
{
    typedef T type;
};

template<typename T>
struct RemoveRef<T&>
{
    typedef T type;
};

template<typename T>
struct RemoveRef<T&&>
{
    typedef T type;
};

template<typename T>
using RemoveRef_t = typename RemoveRef<T>::type;

#endif
