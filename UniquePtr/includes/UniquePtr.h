#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <utility> // exchange

template<typename T>
class UniquePtr
{
public:
    explicit UniquePtr(T* ptr = nullptr) noexcept
    : m_ptr(ptr)
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

        delete m_ptr;
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;

        return *this;
    }
    ~UniquePtr() noexcept
    {
        delete m_ptr;
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

        delete m_ptr;
        m_ptr = newPtr;
        newPtr = nullptr;
    }

private:
    T* m_ptr;
};

#endif
