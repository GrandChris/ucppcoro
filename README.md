

# µcppcoro
A header only library of C++ coroutine abstractions for C++20 coroutines optimized for the use on a microcontroller  

## Build Status
[![Build Actions Status](https://github.com/GrandChris/ucppcoro/workflows/Tests/badge.svg)](https://github.com/GrandChris/ucppcoro/actions)


## Usage:
The usage of C++ coroutines on an microcontroller is limited because coroutines use dynamic memory allocation to store their state. To avoid memory fragmentation, coroutines can only be 
created at initialization phase. An example is provided below.

``` C++
#include "ucppcoro/Task.h"

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
```

## How to build and run the tests
While this is a header only library with no further dependencies and therefore the source code should compile with any capable C++20 compiler, testing is only configured for GCC-10 for the moment.  
  
This repository contains a complete development environment for Docker and VSCode. You can use it with the VSCode extension
[ms-vscode-remote.remote-containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers).  
  
To run the tests, run:

```bash
cmake -B ./build -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=TRUE
cmake --build ./build
cd build
ctest
```