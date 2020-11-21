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
    class SimpleClass {
        public:
        int func(int val) {return val;};
    };

    SimpleClass simpleClass;
    Delegate<int(int)> delegate;
    delegate.set<&SimpleClass::func>(&simpleClass);

    EXPECT_EQ(delegate(4711), 4711);
}

TEST(Delegate, MemberFunctionRef)
{
    class SimpleClass {
        public:
        int func(int const & val) {return val;};
    };

    SimpleClass simpleClass;
    Delegate<int(int const &)> delegate;
    delegate.set<&SimpleClass::func>(&simpleClass);
    
    auto res = delegate(4711);
    EXPECT_EQ(res, 4711);
}

TEST(Delegate, MemberFunctionVoid)
{
    class SimpleClass {
        public:
        void func(int const & val) {};
    };

    SimpleClass simpleClass;
    Delegate<void(int const &)> delegate;
    delegate.set<&SimpleClass::func>(&simpleClass);
    
    delegate(4711);
    // EXPECT_EQ(res, 4711);
}

TEST(Delegate, Functor)
{
    class SimpleClass {
        public:
        int operator()(int val) {return val;};
    };

    SimpleClass simpleClass;
    Delegate<int(int)> delegate;
    delegate.set(&simpleClass);

    EXPECT_EQ(delegate(4711), 4711);
}

TEST(Delegate, FunctorRef)
{
    class SimpleClass {
        public:
        int operator()(int const & val) {return val;};
    };

    SimpleClass simpleClass;
    Delegate<int(int const&)> delegate;
    delegate.set(&simpleClass);

    EXPECT_EQ(delegate(4711), 4711);
}

TEST(Delegate, Lambda)
{
    auto lbd = [](int val){return val;};

    Delegate<int(int)> delegate;
    delegate.set(&lbd);

    EXPECT_EQ(delegate(4711), 4711);
}


int func(int val) {
    return val;
}

TEST(Delegate, FunctionPointer)
{
    Delegate<int(int)> delegate;
    delegate.set<&func>();

    EXPECT_EQ(delegate(4711), 4711);
}

int funcRef(int const & val) {
    return val;
}

TEST(Delegate, FunctionPointerRef)
{
    Delegate<int(int const &)> delegate;
    delegate.set<&funcRef>();

    EXPECT_EQ(delegate(4711), 4711);
}