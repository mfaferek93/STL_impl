#ifndef REMOVE_CV
#define REMOVE_CV

template<typename T>
struct RemoveConst
{
    typedef T type;
};

template<typename T>
struct RemoveConst<const T>
{
    typedef T type;
};

template<typename T>
using RemoveConst_t = typename RemoveConst<T>::type;

template<typename T>
struct RemoveVolatile
{
    typedef T type;
};

template<typename T>
struct RemoveVolatile<volatile T>
{
    typedef T type;
};

template<typename T>
using RemoveVolatile_t = typename RemoveVolatile<T>::type;

template<typename T>
struct RemoveCV
{
    typedef RemoveVolatile_t<RemoveConst_t<T>> type;
};

template<typename T>
using RemoveCV_t = typename RemoveCV<T>::type;

#endif
