//
// \file       main.cpp
// \author     GrandChris
// \date       2020-10-14
// \brief      Space to try out things
//

#include "ucppcoro/Task.h"

#include <iostream>



class Functor3 {
public:
    bool operator()() {return true;}
};


using namespace std;

Task doSomething()
{
    int a = 0;

    cout << "Hello Coroutine!" << endl;

    // auto awaitable1 = std::suspend_always(); 
    //  co_await awaitable1; 

    cout << "Hello Coroutine2!" << endl;

    [[maybe_unused]] auto lbd = [a](){return a == 0;};
    // AwaitableExpression awaitable(lbd);

    // co_await awaitable;

    // co_await lbd;
     co_await [a](){
         return a == 0;
    };

    // co_await AwaitableExpression([](){return false;});

    Functor3 functor;
    co_await functor;

    co_return; 
}
 
 class Functor {
     public:
     bool operator()() {return true;}

     bool ready();
 };


  class Functor2 {
     public:

     bool ready() {return false;};

     void bla(int k) {

     }
 };


typedef void (*invoke_fn_t)(char*);

int main()
{
    // Functor2 functor;

    // Delegate<bool()> delegate;

    // delegate.set<Functor2, &Functor2::ready>(&functor);

    // bool val = delegate();

    // Delegate<void(int)> delegate2;

    // delegate2.set<Functor2, &Functor2::bla>(&functor);


    // Functor functor;

    // void * object = &functor;
    // bool (Functor2::*isReady)();
    // isReady = (bool (Functor2::*)())(&Functor::ready);

    // auto f = reinterpret_cast<invoke_fn_t>(functor);

     
    Task taskDoSomething = doSomething(); 

    [[maybe_unused]] size_t const size = taskDoSomething.size();
   

  
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