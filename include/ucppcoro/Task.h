//
// \file       task.h
// \author     GrandChris
// \date       2020-10-18
// \brief      A runnable task
//


#pragma once

#include "AwaitableLambda.h"

class Promise;

#include <stddef.h>

///
/// \class      Task
/// \author     GrandChris
/// \date       2020-10-25
/// \brief      Suspendable Task running a coroutine
///
class Task {
public:

///////////////////////////////////////////////////////////////////////////////
// Type Definitions

  using promise_type = Promise;

///////////////////////////////////////////////////////////////////////////////
// Constructor

  Task(std::coroutine_handle<promise_type> handle);

///////////////////////////////////////////////////////////////////////////////
// Public Methods

  bool resume();
  size_t size() const;

private:

///////////////////////////////////////////////////////////////////////////////
// Member Variables

  std::coroutine_handle<promise_type> mHandle = nullptr;  // Holds the reference to the coroutine
};


///////////////////////////////////////////////////////////////////////////////
// Implementation

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

  if(mHandle.promise().finished() || mHandle.done()) {
    return false;
  }
  else {
    if(mHandle.promise().resumable()) {
      mHandle.resume();
    }
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