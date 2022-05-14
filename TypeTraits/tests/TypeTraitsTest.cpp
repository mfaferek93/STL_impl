#include <gtest/gtest.h>

#include "IsSame.h"
#include "RemoveCV.h"
#include <RemoveRef.h>

TEST(IsSameTest, simpleCompare)
{
    EXPECT_TRUE(bool(IsSame<int, int>()));
    EXPECT_FALSE(bool(IsSame<float, int>()));

    EXPECT_TRUE(bool(IsSame<int, int>::value));
    EXPECT_FALSE(bool(IsSame<float, int>::value));
}

TEST(RemoveConstTest, withIsSame)
{
    EXPECT_FALSE(bool(IsSame<const int, int>()));
    EXPECT_TRUE(bool(IsSame<RemoveConst_t<const int>, int>()));
}

TEST(RemoveVolatileTest, withIsSame)
{
    EXPECT_FALSE(bool(IsSame<volatile int, int>()));
    EXPECT_TRUE(bool(IsSame<RemoveVolatile_t<volatile int>, int>()));
}

TEST(RemoveCVTest, withIsSame)
{
    EXPECT_FALSE(bool(IsSame<const volatile int, int>()));
    EXPECT_TRUE(bool(IsSame<RemoveCV_t<const volatile int>, int>()));
}

TEST(RemoveRefTest, withIsSame)
{
    EXPECT_FALSE(bool(IsSame<int&, int>()));
    EXPECT_TRUE(bool(IsSame<RemoveRef_t<int&>, int>()));

    EXPECT_FALSE(bool(IsSame<int&&, int>()));
    EXPECT_TRUE(bool(IsSame<RemoveRef_t<int&&>, int>()));
}
