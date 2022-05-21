#include <gtest/gtest.h>

#include "Variant.h"

TEST(VariantTest, getMethod)
{
    Variant<int, float, bool, char, double> v(5);

    EXPECT_NO_THROW(v.Get<int>());
    EXPECT_EQ(5, v.Get<int>());

    EXPECT_THROW(v.Get<float>(), std::exception);
    EXPECT_THROW(v.Get<bool>(), std::exception);
    EXPECT_THROW(v.Get<char>(), std::exception);
    EXPECT_THROW(v.Get<double>(), std::exception);
}

class A
{
public:
    ~A() { std::cout << "A" << std::endl; }
};

TEST(VariantTest, destructor)
{
    Variant<A, int> v(A{});
    EXPECT_NO_THROW(v.Get<A>());
    EXPECT_THROW(v.Get<int>(), std::exception);
}

TEST(VariantTest, emplace)
{
    Variant<int, float, bool, char, double> v(5);
    EXPECT_NO_THROW(v.Get<int>());
    EXPECT_EQ(5, v.Get<int>());
    EXPECT_THROW(v.Get<float>(), std::exception);
    EXPECT_THROW(v.Get<bool>(), std::exception);
    EXPECT_THROW(v.Get<char>(), std::exception);
    EXPECT_THROW(v.Get<double>(), std::exception);

    v.Emplace<bool>(true);
    EXPECT_NO_THROW(v.Get<bool>());
    EXPECT_TRUE(v.Get<bool>());
    EXPECT_THROW(v.Get<float>(), std::exception);
    EXPECT_THROW(v.Get<int>(), std::exception);
    EXPECT_THROW(v.Get<char>(), std::exception);
    EXPECT_THROW(v.Get<double>(), std::exception);
}

TEST(VariantTest, holdsAlternative)
{
    Variant<int, float, bool, char, double> v(5);
    EXPECT_TRUE(v.HoldsAlternative<int>());
    EXPECT_FALSE(v.HoldsAlternative<float>());
    EXPECT_FALSE(v.HoldsAlternative<bool>());
    EXPECT_FALSE(v.HoldsAlternative<char>());
    EXPECT_FALSE(v.HoldsAlternative<double>());
}
