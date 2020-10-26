//
// \file       main.cpp
// \author     GrandChris
// \date       2020-10-14
// \brief      Example project
//

#include "ucppcoro/Task.h"
#include "ucppcoro/TestSize.h"

#include <chrono>
#include <iostream>

using namespace std;

// Desktop implementations for hardware abstraction

class Led {
public:
    Led() = default;

    Led(std::string const & name) : mName(name) {}

    void on() {
        cout << mName << ": " << 1 << endl;
    }

    void off() {
        cout << mName << ": " << 0 << endl;
    }

private:
    std::string mName;
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


Task<128> blinky(Led & led) 
{
    while(true) {
        led.on();
        co_await delay(1000);
        led.off();
        co_await delay(500); 

        co_return;       
    }
}
auto const blinky_size = testSize(blinky);


int main()
{    
    char * bla = new char;

    Led led1("led1");
    Led led2("led2");
    Led led3("led3");

    Task task1 = blinky(led1); 
    Task task2 = blinky(led2); 
    Task task3 = blinky(led3); 

    [[maybe_unused]] volatile int i = 0;

    bool running = true;
    while(running) 
    {
        running = false;
        running |= task1.resume();
        running |= task2.resume();
        running |= task3.resume();
    }

    return 0; 
} 