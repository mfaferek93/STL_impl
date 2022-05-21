#include <gtest/gtest.h>

#include "Variant.h"

TEST(VariantTest, getMethod)
{
    Variant<int, float, bool, char, double> v(5);

    EXPECT_NO_THROW(v.get<int>());
    EXPECT_EQ(5, v.get<int>());

    EXPECT_THROW(v.get<float>(), std::exception);
    EXPECT_THROW(v.get<bool>(), std::exception);
    EXPECT_THROW(v.get<char>(), std::exception);
    EXPECT_THROW(v.get<double>(), std::exception);
}

class A
{
public:
    ~A() { std::cout << "A" << std::endl; }
};

TEST(VariantTest, destructor)
{
    Variant<A, int> v(A{});
    EXPECT_NO_THROW(v.get<A>());
    EXPECT_THROW(v.get<int>(), std::exception);
}

TEST(VariantTest, emplace)
{
    Variant<int, float, bool, char, double> v(5);
    EXPECT_NO_THROW(v.get<int>());
    EXPECT_EQ(5, v.get<int>());
    EXPECT_THROW(v.get<float>(), std::exception);
    EXPECT_THROW(v.get<bool>(), std::exception);
    EXPECT_THROW(v.get<char>(), std::exception);
    EXPECT_THROW(v.get<double>(), std::exception);

    v.emplace<bool>(true);
    EXPECT_NO_THROW(v.get<bool>());
    EXPECT_TRUE(v.get<bool>());
    EXPECT_THROW(v.get<float>(), std::exception);
    EXPECT_THROW(v.get<int>(), std::exception);
    EXPECT_THROW(v.get<char>(), std::exception);
    EXPECT_THROW(v.get<double>(), std::exception);
}
