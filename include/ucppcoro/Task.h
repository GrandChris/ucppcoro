//
// \file       task.h
// \author     GrandChris
// \date       2020-10-18
// \brief      A runnable task
//


#pragma once

#if !defined(__cpp_impl_coroutine)
    #define __cpp_impl_coroutine 1  // just for intellisense to work properly
#endif

#include <coroutine>
#include <stddef.h>
#include <iostream>

struct awaitable {
  bool await_ready() {
    return false; 
  }
  void await_suspend(std::coroutine_handle<> h) {

  }
  void await_resume() {}
};



class Task {
public:

  ///////////////////////////// Promise ///////////////////////////////

  class promise_type {
  public:
    promise_type();

    Task get_return_object();

    std::suspend_always initial_suspend();
    std::suspend_never final_suspend();

    void return_void();
    void unhandled_exception();

    bool finished() const;
    size_t size() const;

    void* operator new( size_t count); 

  private:
    bool mFinished = false;
    size_t const mSize;
    inline static size_t lastSize = 0;
  };

  ///////////////////////////// Public Methods ///////////////////////////////

  Task(std::coroutine_handle<promise_type> handle);

  bool resume();
  size_t size() const;

private:
  std::coroutine_handle<promise_type> mHandle = nullptr;
};



// #######+++++++ Implementation +++++++#######

#include "Promise.h"

///
/// \brief      Constructor
/// \author     GrandChris
/// \date       2020-10-19
///
inline Task::Task(std::coroutine_handle<promise_type> handle) 
  : mHandle(handle)
  {
  }

///
/// \brief      Resumes execution
/// \author     GrandChris
/// \date       2020-10-19
/// \return     true if there is still work to do, false otherwise
///
inline bool Task::resume() 
{
  if(mHandle == nullptr) {
    return false;
  }

  if(mHandle.promise().finished()) {
    return false;
  }
  else {
    mHandle.resume();
    mHandle.promise().
    return true;
  }
}
 
///
/// \brief      Returns the allocated size of the coroutine
/// \author     GrandChris
/// \date       2020-10-19
///
inline size_t Task::size() const {
  if(mHandle == nullptr) {
    return 0;
  }
  
  return mHandle.promise().size();
}