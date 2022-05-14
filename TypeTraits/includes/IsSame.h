#ifndef IS_SAME
#define IS_SAME

template<typename T, typename U>
struct IsSame
{
    const static bool value = false;
    operator bool() {return value;}
};

template<typename T>
struct IsSame<T, T>
{
    const static bool value = true;
    operator bool() {return value;}
};

#endif
