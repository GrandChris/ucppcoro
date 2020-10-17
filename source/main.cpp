

#include "ucppcoro/promise.h"
#include "ucppcoro/ucppcoro.h"

#include <iostream>
#include <coroutine>



using namespace std;

// task doSomething()
// {
//     co_return;
// }
// task taskDoSomething = doSomething();

int main()
{
    // task ret = doSomething();
    // size_t const size = sizeof(doSomething);

    cout << "Hello World!" << endl;

    return 0; 
}