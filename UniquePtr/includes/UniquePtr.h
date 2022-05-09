#ifndef UNIQUE_PTR
#define UNIQUE_PTR

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

template<typename T, typename Deleter = DefaultDeleter<T>>
class UniquePtr
{
public:
    explicit UniquePtr(T* ptr = nullptr, Deleter deleter = DefaultDeleter<T>{}) noexcept
    : m_ptr(ptr)
    , m_deleter(deleter)
    {}
    UniquePtr(const UniquePtr& rhs) = delete;
    UniquePtr(UniquePtr&& rhs)
    : m_ptr(rhs.m_ptr)
    {
        rhs.m_ptr = nullptr;
    }
    UniquePtr& operator=(const UniquePtr& rhs) = delete;
    UniquePtr& operator=(UniquePtr&& rhs) noexcept
    {
        if (m_ptr == rhs.m_ptr) return *this;

        m_deleter(m_ptr);
        std::swap(m_ptr, rhs.m_ptr);

        return *this;
    }
    ~UniquePtr() noexcept
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
        if (!newPtr) return;

        m_deleter(m_ptr);
        std::swap(m_ptr, newPtr);
    }

private:
    T* m_ptr;
    Deleter m_deleter;
};

#endif
