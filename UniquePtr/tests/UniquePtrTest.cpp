#include <gtest/gtest.h>

#include "UniquePtr.h"

#include <functional> // function
#include <utility> // move

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

TEST(UniquePtrTest, boolOperator)
{
    UniquePtr<int> ptr1(new int(1));
    EXPECT_TRUE(ptr1);
    UniquePtr<int> ptr2(nullptr);
    EXPECT_FALSE(ptr2);
}

TEST(UniquePtrTest, release)
{
    UniquePtr<int> ptr1(new int(1));
    EXPECT_EQ(1, *ptr1);
    auto rawPtr = ptr1.release();
    EXPECT_EQ(1, *rawPtr);
    EXPECT_FALSE(ptr1);
}

TEST(UniquePtrTest, reset)
{
    UniquePtr<int> ptr1(new int(1));
    EXPECT_EQ(1, *ptr1);

    ptr1.reset(new int(2));
    EXPECT_EQ(2, *ptr1);

    ptr1.reset();
    EXPECT_EQ(2, *ptr1);
}

class TestDefaultDeleter
{
public:
    void operator()(int*& res)
    {
        delete res;
        res = nullptr;
        ++m_callsCounter;
    }

    static int m_callsCounter;
};

int TestDefaultDeleter::m_callsCounter = 0;
TEST(UniquePtrTest, customDeleter)
{
    // function class operator as deleter
    EXPECT_EQ(0, TestDefaultDeleter::m_callsCounter);
    UniquePtr<int, TestDefaultDeleter> ptr1(new int(1), TestDefaultDeleter{});
    ptr1.~UniquePtr();
    EXPECT_FALSE(ptr1);
    EXPECT_EQ(1, TestDefaultDeleter::m_callsCounter);

    // lambda function as deleter
    int lambdaCallsCounter = 0;
    auto lambdaDeleter = [&lambdaCallsCounter](int*& ptr)
    {
        delete ptr;
        ptr = nullptr;
        ++lambdaCallsCounter;
    };
    UniquePtr<int, decltype(lambdaDeleter)> ptr2(new int(2), lambdaDeleter);
    ptr2.~UniquePtr();
    EXPECT_EQ(1, lambdaCallsCounter);

    // std::function as deleter
    std::function<void(int*&)> funcDeleter = lambdaDeleter;
    UniquePtr<int, decltype(funcDeleter)> ptr3(new int(2), funcDeleter);
    ptr3.~UniquePtr();
    EXPECT_EQ(2, lambdaCallsCounter);
}
