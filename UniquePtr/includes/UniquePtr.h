#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template<typename T>
class UniquePtr
{
public:
    UniquePtr(T* ptr = nullptr)
    : m_ptr(ptr)
    {}
    UniquePtr(const UniquePtr& rhs) = delete;
    UniquePtr(UniquePtr&& rhs)
    : m_ptr(rhs.m_ptr)
    {
        rhs.m_ptr = nullptr;
    }

    UniquePtr& operator=(const UniquePtr& rhs) = delete;
    UniquePtr& operator=(UniquePtr&& rhs)
    {
        if (m_ptr == rhs.m_ptr) return *this;

        delete m_ptr;
        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;

        return *this;
    }

    ~UniquePtr()
    {
        delete m_ptr;
    }

    T& operator*() const
    {
        return *m_ptr;
    }
    T* get() const
    {
        return m_ptr;
    }

private:
    T* m_ptr;
};

#endif