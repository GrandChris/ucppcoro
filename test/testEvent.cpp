//
// \file       testEvent.h
// \author     GrandChris
// \date       2020-10-24
// \brief      Test of the class Event
//

// #include "ucppcoro/Event.h"

// #include <gtest/gtest.h>

//     class SimpleClass {
//         public:
//         int func(int const & val) {mVal = val; return mVal;};

//         int operator()(int val) {mVal = val; return mVal;};

//         int getVal() const {
//             return mVal;
//         }

//         private:
//             int mVal = 0;
//     };


// TEST(Event, simple)
// {


//     SimpleClass simpleClass;
//     Event<3, int(int)> event;
//     event.add<&SimpleClass::func>(&simpleClass);
//     event.add(&simpleClass);

//     event(4711);

//     EXPECT_EQ(simpleClass.getVal(), 4711);
// }