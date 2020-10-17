//
// \file       promise.h
// \author     GrandChris
// \date       2020-10-11
// \brief      A promise for a coroutine
//


#pragma once

#if !defined(__cpp_impl_coroutine)
    #define __cpp_impl_coroutine 1  // just for intellisense to work properly
#endif

#include <coroutine>


struct task{
  struct promise_type {
    task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() { return {}; }
    void return_void() {}
    void unhandled_exception() {}

    void* operator new( std::size_t count ) {return new char[count];};
    
  };
};
 