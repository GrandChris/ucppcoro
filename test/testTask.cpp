//
// \file       testTask.h
// \author     GrandChris
// \date       2020-10-24
// \brief      Test of the class Task
//

#include "ucppcoro/Task.h"
#include "ucppcoro/TestSize.h"

#include <gtest/gtest.h>


TEST(Task, Lambda)
{
    struct Test {
         static Task<200> routine(int & a, int & b) {
            b = 1;

            co_await [&a](){
                return a == 10;
            };

            b = 2;
        }
    };

    testSize(Test::routine);

    int a = 0;
    int b = 0;

    Task<200> task = Test::routine(a, b);
    [[maybe_unused]] size_t const size = task.size();

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 0);

    EXPECT_EQ(task.resume(), true);

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 1);

    EXPECT_EQ(task.resume(), true);

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 1);

    a = 10;
    EXPECT_EQ(task.resume(), true);

    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 2);

    EXPECT_EQ(task.resume(), false);
}


TEST(Task, Lambda2)
{
    struct Test {
         static Task<200> routine(int & a, int & b) {
            b = 1;

            auto lbd = [&a](){
                return a == 10;
            };
             
            co_await lbd;

            b = 2;
        }
    };

    testSize(Test::routine);

    int a = 0;
    int b = 0;

    Task<200> task = Test::routine(a, b);
    [[maybe_unused]] size_t const size = task.size();

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 0);

    EXPECT_EQ(task.resume(), true);

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 1);

    EXPECT_EQ(task.resume(), true);

    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 1);

    a = 10;
    EXPECT_EQ(task.resume(), true);

    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 2);

    EXPECT_EQ(task.resume(), false);
}