#ifndef VARIANT
#define VARIANT

#include <cstddef>   // size_t
#include <exception> // exception
#include <typeindex> // type_index

template <size_t val1, size_t... values>
struct MaxSize;

template <size_t val1, size_t val2, size_t... values>
struct MaxSize<val1, val2, values...>
{
    static const size_t value = val1 > val2 ? MaxSize<val1, values...>::value
                                            : MaxSize<val2, values...>::value;
};

template <size_t val>
struct MaxSize<val>
{
    static const size_t value = val;
};

template <typename... Ts>
struct Deleter;

template <typename T, typename... Ts>
struct Deleter<T, Ts...>
{
    static void Destroy(std::type_index id, char *data)
    {
        if (id == typeid(T))
        {
            reinterpret_cast<T *>(data)->~T();
        }
        else
        {
            Deleter<Ts...>::Destroy(id, data);
        }
    }
};

template <>
struct Deleter<>
{
    static void Destroy(std::type_index id, char *data) {}
};

template <typename... Ts>
class Variant
{
private:
    static const size_t m_maxSize = MaxSize<sizeof(Ts)...>::value;

public:
    template <typename T>
    Variant(const T &val)
        : m_typeId(typeid(T))
    {
        new (&m_data) T(val);
    }

    template <typename T>
    T &Get()
    {
        if (m_typeId == typeid(T))
        {
            return *reinterpret_cast<T *>(m_data);
        }
        else
        {
            throw std::exception();
        }
    }

    template <typename T, typename... Args>
    T &Emplace(Args &&...args)
    {
        Deleter<Ts...>::Destroy(m_typeId, m_data);
        new (&m_data) T(std::forward<Args>(args)...);
        m_typeId = typeid(T);
        return *reinterpret_cast<T *>(m_data);
    }

    template <typename T>
    bool HoldsAlternative()
    {
        return (m_typeId == typeid(T));
    }

    ~Variant()
    {
        Deleter<Ts...>::Destroy(m_typeId, m_data);
    }

private:
    std::type_index m_typeId;
    char m_data[m_maxSize];
};

#endif
