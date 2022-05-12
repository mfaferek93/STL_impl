#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <cstddef> // nullptr_t
#include <utility> // exchange, swap

template <typename T>
class DefaultDeleter
{
public:
    void operator()(T*& res)
    {
        delete res;
        res = nullptr;
    }
};

template <typename T>
class DefaultDeleter<T[]>
{
public:
    void operator()(T*& res)
    {
        delete[] res;
        res = nullptr;
    }
};

template<typename T, typename Deleter = DefaultDeleter<T>>
class BaseUniquePtr
{
public:
    explicit BaseUniquePtr(T* ptr, Deleter deleter) noexcept
    : m_ptr(ptr)
    , m_deleter(deleter)
    {}
    BaseUniquePtr(const BaseUniquePtr& rhs) = delete;
    BaseUniquePtr(BaseUniquePtr&& rhs)
    : m_ptr(rhs.m_ptr)
    {
        rhs.m_ptr = nullptr;
    }
    BaseUniquePtr& operator=(const BaseUniquePtr& rhs) = delete;
    virtual ~BaseUniquePtr() noexcept
    {
        m_deleter(m_ptr);
    }

    T* operator->() const noexcept
    {
        return m_ptr;
    }
    T& operator*() const noexcept
    {
        return *m_ptr;
    }
    explicit operator bool() const noexcept
    {
        return m_ptr;
    }

    T* get() const noexcept
    {
        return m_ptr;
    }
    T* release() noexcept
    {
        return std::exchange(m_ptr, nullptr);
    }

    void reset(T* newPtr = nullptr) noexcept
    {
        m_deleter(m_ptr);
        std::swap(m_ptr, newPtr);
    }

protected:
    T* m_ptr;
    Deleter m_deleter;
};

template<typename T, typename Deleter = DefaultDeleter<T>>
class UniquePtr : public BaseUniquePtr<T, Deleter>
{
public:
    explicit UniquePtr(T* ptr = nullptr, Deleter deleter = DefaultDeleter<T>{}) noexcept
    : BaseUniquePtr<T, Deleter>(ptr, deleter)
    {}
    UniquePtr(UniquePtr&& rhs)
    : BaseUniquePtr<T, Deleter>(std::move(rhs))
    {
    }
    UniquePtr& operator=(UniquePtr&& rhs) noexcept
    {
        if (this->m_ptr == rhs.m_ptr) return *this;

        this->m_deleter(this->m_ptr);
        std::swap(this->m_ptr, rhs.m_ptr);

        return *this;
    }
};

template<typename T1, typename T2, typename D1, typename D2>
bool operator==(const UniquePtr<T1, D1>& lhsPtr, const UniquePtr<T2, D2>& rhsPtr)
{
    if (!lhsPtr && !rhsPtr) return true;
    else if(!lhsPtr || !rhsPtr) return false;

    return ((*lhsPtr) == (*rhsPtr));
}

template<typename T1, typename D1>
bool operator==(const UniquePtr<T1, D1>& lhsPtr, std::nullptr_t)
{
    return !lhsPtr;
}

template<typename T1, typename D1>
bool operator==(std::nullptr_t, const UniquePtr<T1, D1>& rhsPtr)
{
    return !rhsPtr;
}

template<typename T1, typename T2>
bool operator!=(const T1& lhsPtr, const T2& rhsPtr)
{
    return !operator==(lhsPtr, rhsPtr);
}

template<typename T, typename Deleter>
class UniquePtr<T[], Deleter> : public BaseUniquePtr<T, Deleter>
{
    public:
    explicit UniquePtr(T* ptr = nullptr, Deleter deleter = DefaultDeleter<T[]>{}) noexcept
    : BaseUniquePtr<T, Deleter>(ptr, deleter)
    {
    }
    UniquePtr(UniquePtr&& rhs)
    : BaseUniquePtr<T, Deleter>(std::move(rhs))
    {
    }
    UniquePtr& operator=(UniquePtr&& rhs) noexcept
    {
        if (this->m_ptr == rhs.m_ptr) return *this;

        this->m_deleter(this->m_ptr);
        std::swap(this->m_ptr, rhs.m_ptr);

        return *this;
    }
};

template<typename T1, typename T2, typename D1, typename D2>
bool operator==(const UniquePtr<T1[], D1>& lhsPtr, const UniquePtr<T2[], D2>& rhsPtr) = delete;

template<typename T1, typename D1>
bool operator==(const UniquePtr<T1[], D1>& lhsPtr, std::nullptr_t)
{
    return !lhsPtr;
}

template<typename T1, typename D1>
bool operator==(std::nullptr_t, const UniquePtr<T1[], D1>& rhsPtr)
{
    return !rhsPtr;
}

#endif
