#include <gtest/gtest.h>

#include <array>

#include "Wrapper.hpp"

class A
{
public:
    A(int id, const std::string &name) : m_id(id), m_name(name)
    {
    }
    std::string to_string() const
    {
        return {m_name + std::to_string(m_id)};
    }

private:
    int m_id;
    std::string m_name;
};

class B
{
public:
    B(int id, const std::string &name) : m_id(id), m_name(name)
    {
    }
    std::string to_string() const
    {
        return {m_name + std::to_string(m_id)};
    }

private:
    int m_id;
    std::string m_name;
};

TEST(WrapperTest, typeErasure)
{
    std::array<Wrapper, 2> arr{A{100, "test"}, B{100, "test"}};

    for (const auto &element : arr)
    {
        EXPECT_EQ(element.to_string(), "test100");
    }
}
