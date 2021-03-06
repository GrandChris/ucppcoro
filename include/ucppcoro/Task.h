//
// \file       task.h
// \author     GrandChris
// \date       2020-10-18
// \brief      A runnable task
//


#pragma once

#include "AwaitableLambda.h"

#include <array>
#include <cstddef>

template<size_t SIZE>
class Promise;



///
/// \class      Task
/// \author     GrandChris
/// \date       2020-10-25
/// \brief      Suspendable Task running a coroutine
///
template<size_t SIZE>
class Task {
public:

///////////////////////////////////////////////////////////////////////////////
// Type Definitions

  using promise_type = Promise<SIZE>;
  static size_t const max_size = SIZE;

///////////////////////////////////////////////////////////////////////////////
// Constructor

  Task() = default;

  Task(size_t const allocSize);

  Task(std::array<std::byte, SIZE> & memory, size_t const allocSize);

///////////////////////////////////////////////////////////////////////////////
// Public Methods

  bool resume();
  size_t size() const;
  void destroy();

private:

///////////////////////////////////////////////////////////////////////////////
// Member Variables
  
  std::coroutine_handle<promise_type> mHandle = nullptr;  // Holds the reference to the coroutine
  size_t const mAllocSize = 0;                            // Allocated size of the coroutine
  std::array<std::byte, SIZE> mMemory = {};               // Memory to store the coroutine
};


///////////////////////////////////////////////////////////////////////////////
// Implementation

#include "Promise.h"

///
/// \brief      Constructor on failed allocation
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline Task<SIZE>::Task(size_t const allocSize) 
  : mAllocSize(allocSize)
{

}

///
/// \brief      Constructor on successful allocation
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline Task<SIZE>::Task(std::array<std::byte, SIZE> & memory, size_t const allocSize) 
: mAllocSize(allocSize),
  mMemory(memory) // copy memory of the allocated coroutine into the local object
{
  mHandle = std::coroutine_handle<Promise<SIZE>>::from_address(mMemory.data());

  memory.fill(std::byte()); // clear old memory, just to be sure
}

///
/// \brief      Resumes execution
/// \author     GrandChris
/// \date       2020-10-19
/// \return     true if there is still work to do, false otherwise
///
template<size_t SIZE>
inline bool Task<SIZE>::resume() 
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
template<size_t SIZE>
inline size_t Task<SIZE>::size() const {
  return mAllocSize;
}


///
/// \brief      Deletes the dynamic state of the coroutine
/// \author     GrandChris
/// \date       2020-10-25
///
template<size_t SIZE>
inline void Task<SIZE>::destroy() 
{
  // mHandle.destroy(); // Does not work with placement new 
  mHandle = nullptr;
}