#include <gtest/gtest.h>

#include "UniquePtr.h"

#include <utility>

TEST(UniquePtrTest, Constructors)
{
    UniquePtr<int> ptr1;
    EXPECT_EQ(nullptr, ptr1.get());

    UniquePtr<int> ptr2(new int(2));
    EXPECT_EQ(2, *ptr2);

    UniquePtr<int> ptr3(std::move(ptr2));
    EXPECT_EQ(2, *ptr3);
    EXPECT_EQ(nullptr, ptr2.get());
}

TEST(UniquePtrTest, MoveAssignmentOperator)
{
    UniquePtr<int> ptr1(new int(1));
    EXPECT_NE(nullptr, ptr1.get());

    UniquePtr<int> ptr2(new int(2));
    ptr2 = std::move(ptr1);
    EXPECT_EQ(1, *ptr2);
    EXPECT_EQ(nullptr, ptr1.get());
}