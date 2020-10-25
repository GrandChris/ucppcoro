//
// \file       testDelegate.h
// \author     GrandChris
// \date       2020-10-24
// \brief      Test of the class Delegate
//

#include "ucppcoro/Delegate.h"

#include <gtest/gtest.h>


TEST(Delegate, MemberFunction)
{
    class ReadyClass {
        public:
        int ready() {return 4711;};
    };

    ReadyClass readyClass;
    Delegate<int()> delegate;
    delegate.set<ReadyClass, &ReadyClass::ready>(&readyClass);

    EXPECT_EQ(delegate(), 4711);
}

TEST(Delegate, Functor)
{
    class ReadyClass {
        public:
        int operator()() {return 4711;};
    };

    ReadyClass readyClass;
    Delegate<int()> delegate;
    delegate.set(&readyClass);

    EXPECT_EQ(delegate(), 4711);
}

TEST(Delegate, Lambda)
{
    auto lbd = [](){return 4711;};

    Delegate<int()> delegate;
    delegate.set(&lbd);

    EXPECT_EQ(delegate(), 4711);
}