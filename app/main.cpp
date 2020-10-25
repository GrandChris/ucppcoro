//
// \file       main.cpp
// \author     GrandChris
// \date       2020-10-14
// \brief      Example project
//

#include "ucppcoro/Task.h"

#include <chrono>
#include <iostream>

using namespace std;

// Desktop implementations for hardware abstraction

class Led {
public:
    void on() {
        cout << 1 << endl;
    }

    void off() {
        cout << 0 << endl;
    }
};

uint64_t getTimeMs() {
    auto t = std::chrono::high_resolution_clock::now();
    auto t_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(t);
    auto ms = t_ms.time_since_epoch().count();

    return ms;
}


// Microcontroller like implementation


auto delay(size_t const ms) 
{
    uint64_t const time = getTimeMs() + ms;
    return [time] { return getTimeMs() >= time; };
}


Task blinky(Led & led) 
{
    while(true) {
        led.on();
        co_await delay(1000);
        led.off();
        co_await delay(500);
    }
}


int main()
{     
    Led led1;
    Led led2;

    Task task1 = blinky(led1); 
    Task task2 = blinky(led2); 

    while(true) 
    {
        task1.resume();
        task2.resume();
    }

    return 0; 
} 