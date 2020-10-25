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
class Promise {
public:

///////////////////////////////////////////////////////////////////////////////
// Constructors

  Promise();

///////////////////////////////////////////////////////////////////////////////
// Public Methods

  Task get_return_object();

  std::suspend_always initial_suspend();
  std::suspend_never final_suspend();

  template<std::invocable T>
  AwaitableLambda<T> await_transform(T functor);

  void return_void();
  void unhandled_exception();

  bool finished() const;
  bool resumable() const;
  size_t size() const;

  void* operator new( size_t count); 

private:

///////////////////////////////////////////////////////////////////////////////
// Member Variables

  bool mFinished = false;             // Indicates when the corouine has finished execution
  size_t const mSize;                 // Allocated size of the coroutine (only for debugging/information purposes)
  Delegate<bool()> mIsReady;          // Function indicating if the coroutine can be resumed

///////////////////////////////////////////////////////////////////////////////
// Static Variables

  inline static size_t lastSize = 0;  // Place for operator new to store temporarily the allocated size
};


///////////////////////////////////////////////////////////////////////////////
// Implementation

///
/// \brief      Constructor
/// \author     GrandChris
/// \date       2020-10-19
///
inline Promise::Promise() : mSize(lastSize) {
  auto lbd = [](){return true;};
  mIsReady.set(&lbd);
}

///
/// \brief      Construct a Task
/// \author     GrandChris
/// \date       2020-10-19
///
inline Task Promise::get_return_object() { 
  return Task(std::coroutine_handle<Promise>::from_promise(*this)); 
}

///
/// \brief      Action on Promise creation
/// \author     GrandChris
/// \date       2020-10-19
///
inline std::suspend_always Promise::initial_suspend() { 
  // std::cout << "initial_suspend" << std::endl;
  return {}; 
}

///
/// \brief      Action on Promise destruction
/// \author     GrandChris
/// \date       2020-10-19
///
inline std::suspend_never Promise::final_suspend() { 
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
template<std::invocable T>
AwaitableLambda<T> Promise::await_transform(T functor)
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
inline void Promise::return_void() {

}

///
/// \brief      An exeption has been thrown
/// \author     GrandChris
/// \date       2020-10-19
///
inline void Promise::unhandled_exception() {

}

///
/// \brief      Returns if co_return has bee called
/// \author     GrandChris
/// \date       2020-10-19
///
inline bool Promise::finished() const {
  return mFinished;
}

///
/// \brief      Checks if the coroutine is waiting for a event
/// \author     GrandChris
/// \date       2020-10-25
///
bool Promise::resumable() const {
  return mIsReady();
}

///
/// \brief      Returns the allocated size of the coroutine
/// \author     GrandChris
/// \date       2020-10-19
///
inline size_t Promise::size() const {
  return mSize;
}

///
/// \brief      Allocates the memory for the coroutine
/// \author     GrandChris
/// \date       2020-10-19
///
inline void* Promise::operator new( size_t count) {
  lastSize = count;
  return new char[count];
}