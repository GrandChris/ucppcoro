

#include "ucppcoro/Task.h"

#include <iostream>
#include <coroutine>



using namespace std;

Task doSomething()
{
    int a = 0;

    cout << "Hello Coroutine!" << endl;

    co_await std::suspend_always(); 

    cout << "Hello Coroutine2!" << endl;

    co_return; 
}
 
 

int main()
{
     
    Task taskDoSomething = doSomething(); 

    size_t const size = taskDoSomething.size();
   

  
    // task ret = doSomething();
    // size_t const size = sizeof(doSomething); 

    cout << "Hello World!" << endl;   

    bool running = true;
    while(running) 
    {
        running = false;
        running |= taskDoSomething.resume();
    }



    return 0; 
} 