

# µcppcoro
A header only library of C++ coroutine abstractions for C++20 coroutines optimized for the use on a microcontroller.

## Build Status
[![Build Actions Status](https://github.com/GrandChris/ucppcoro/workflows/Tests/badge.svg)](https://github.com/GrandChris/ucppcoro/actions)

## About
The library uses some inspiration from [cppcoro](https://github.com/lewissbaker/cppcoro), everything is however implemented in its own way.   
  
Included Types are:
+ Task\<size\>

## Usage:
C++ coroutines use dynamic memory allocation to store their state. To avoid memory fragmentation placement new is used to store the state in 
the holding object ("Task<>"). Sadly there is no way to get the size of the coroutine at compile time.  
To circumvent the problem a predefined size for allocation storage is given to the class Task<>. If there is not enough space available to allocate the 
coroutine, the coroutine will simply not run. To make sure, all coroutines are able to run, every coroutine should be tested with the "testSize(...)"
function, which uses a runtime "assert" on the allocated size.  
For an example, see below:

``` C++
#include "ucppcoro/Task.h"
#include "ucppcoro/TestSize.h"

// Return a lambda function. When the lambda returns "true", the coroutine resumes
auto delay(size_t const ms) 
{
    uint64_t const time = getTimeMs() + ms;
    return [time] { return getTimeMs() >= time; };
}

// Deceleration of a coroutine
Task<128> blinky(Led & led) 
{
    while(true) {
        led.on();
        co_await delay(1000);
        led.off();
        co_await delay(500);        
    }
}

// Temporarily create the coroutine and "assert" the allocated size 
auto const blinky_size = testSize(blinky);


int main()
{    
    Led led1("led1");
    Led led2("led2");
    Led led3("led3");

    // Only creates the coroutines, does not run them yet
    Task task1 = blinky(led1); 
    Task task2 = blinky(led2); 
    Task task3 = blinky(led3); 

    // Run all the coroutines
    while(true) 
    {
        task1.resume();
        task2.resume();
        task3.resume();
    }

    return 0; 
} 
```

## Tests:
This is a header only library with no further dependencies. However for the Unit Tests, the Google Testing Framework is used. It is downloaded at configuration time through "vcpkg" [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg) . Also libraries for Sanitizers [https://github.com/google/sanitizers](https://github.com/google/sanitizers) are used to avoid memory leeks and undefined behavior.  
The tests run with GCC-10 on Ubuntu. Testing with other compilers may be added in the future.  

This repository uses [ms-vscode-remote.remote-containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) to create the same build environment as on the "GitHub Actions" build pipeline. See ".devcontainer/Dockerfile" for details. The development environment
should be runnable on any system with "VSCode" and "Docker" installed. 
  
To build and run the tests, run:

```bash
cmake -B ./build -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=TRUE
cmake --build ./build
cd build
ctest
```