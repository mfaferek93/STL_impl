#include <memory>
#include <string>
#include <utility>

class BaseType
{
public:
    virtual ~BaseType() = default;
    virtual std::string to_string() const = 0;
};

template <typename T>
class TypeErasedImpl : public BaseType
{
public:
    TypeErasedImpl(T value) : m_value(std::move(value))
    {
    }

    std::string to_string() const override
    {
        return m_value.to_string();
    }

private:
    T m_value;
};

class Wrapper
{
public:
    template <typename T>
    Wrapper(T value) : m_value(std::make_unique<TypeErasedImpl<T>>(std::move(value))) {}

    std::string to_string() const
    {
        return m_value->to_string();
    }

private:
    std::unique_ptr<BaseType> m_value;
};