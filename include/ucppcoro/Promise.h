//
// \file       promise.h
// \author     GrandChris
// \date       2020-10-11
// \brief      A promise for a coroutine
//

#pragma once

#include <stddef.h>

///
/// \class      Promise
/// \author     GrandChris
/// \date       2020-10-25
/// \brief      Promise of a coroutine (for class Task)
///
template<size_t SIZE>
class Promise {
public:

///////////////////////////////////////////////////////////////////////////////
// Constructors

  Promise();

///////////////////////////////////////////////////////////////////////////////
// Public Methods

  Task<SIZE> get_return_object();

  std::suspend_always initial_suspend();
  std::suspend_never final_suspend();

  template<std::invocable T>
  AwaitableLambda<T> await_transform(T functor);

  void return_void();
  void unhandled_exception();

  bool finished() const;
  bool resumable();

  ///////////////////////////////////////////////////////////////////////////////
  // Static functions

  void* operator new( size_t count) noexcept; 
  void operator delete(void * mem) noexcept;

  static Task<SIZE> get_return_object_on_allocation_failure();

private:

///////////////////////////////////////////////////////////////////////////////
// Member Variables

  bool mFinished = false;             // Indicates when the coroutine has finished execution
  Delegate<bool()> mIsReady;          // Function indicating if the coroutine can be resumed

///////////////////////////////////////////////////////////////////////////////
// Static Variables

  static inline std::array<std::byte, SIZE> memory = {}; // Place for operator new to store temporarily the coroutine data
  static inline size_t lastSize = 0;  // Place for operator new to store temporarily the allocated size
};


///////////////////////////////////////////////////////////////////////////////
// Implementation

// #include <iostream>

///
/// \brief      Constructor
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline Promise<SIZE>::Promise() {
  auto lbd = [](){return true;};
  mIsReady.set(&lbd);
}

///
/// \brief      Construct a Task
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline Task<SIZE> Promise<SIZE>::get_return_object() { 
  return Task<SIZE>(memory, lastSize); 
}

///
/// \brief      Construct a Task on allocation failure
/// \author     GrandChris
/// \date       2020-10-26
///
template<size_t SIZE>
Task<SIZE> Promise<SIZE>::get_return_object_on_allocation_failure() {
  return Task<SIZE>(lastSize);
}

///
/// \brief      Action on Promise creation
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline std::suspend_always Promise<SIZE>::initial_suspend() { 
  // std::cout << "initial_suspend" << std::endl;
  return {}; 
}

///
/// \brief      Action on Promise destruction
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline std::suspend_never Promise<SIZE>::final_suspend() { 
  mFinished = true;
  // std::cout << "final_suspend" << std::endl;
  return {}; 
}

///
/// \brief      Saves a reference to the awaitable object
/// \author     GrandChris
/// \date       2020-10-25
/// \param      functor Lambda function returning "true" when ready
///
template<size_t SIZE>
template<std::invocable T>
AwaitableLambda<T> Promise<SIZE>::await_transform(T functor)
{
  AwaitableLambda awaitable(std::move(functor));
  awaitable.registerDelegate(&mIsReady);

  return awaitable;
}

///
/// \brief      co_retunr has been called
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline void Promise<SIZE>::return_void() {
  mFinished = true;
}

///
/// \brief      An exception has been thrown
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline void Promise<SIZE>::unhandled_exception() {
  // it is intended to be used with exceptions disabled
}

///
/// \brief      Returns if co_return has bee called
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline bool Promise<SIZE>::finished() const {
  return mFinished;
}

///
/// \brief      Checks if the coroutine is waiting for a event
/// \author     GrandChris
/// \date       2020-10-25
///
template<size_t SIZE>
bool Promise<SIZE>::resumable() {
  return mIsReady();
}

///
/// \brief      Allocates the memory for the coroutine
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline void* Promise<SIZE>::operator new( size_t count) noexcept 
{
  lastSize = count;

  if(count <= SIZE) {
    return new(memory.data()) std::byte[count];
  }
  else {
    return nullptr;
  }
}

///
/// \brief      Frees the memory of the coroutine
/// \author     GrandChris
/// \date       2020-10-19
///
template<size_t SIZE>
inline void Promise<SIZE>::operator delete(void * mem) noexcept
{
  // memory is kept in a member variable of class "Task<>"
  // it will be deleted when the Task object goes out of scope

  // nothing to do here
}