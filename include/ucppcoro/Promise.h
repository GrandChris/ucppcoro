//
// \file       promise.h
// \author     GrandChris
// \date       2020-10-11
// \brief      A promise for a coroutine
//


#pragma once

#include "Task.h"

///
/// \brief      Constructor
/// \author     GrandChris
/// \date       2020-10-19
///
inline Task::promise_type::promise_type() : mSize(lastSize) {

}

///
/// \brief      Construct a Task
/// \author     GrandChris
/// \date       2020-10-19
///
inline Task Task::promise_type::get_return_object() { 
  return Task(std::coroutine_handle<promise_type>::from_promise(*this)); 
}

///
/// \brief      Action on Promise creation
/// \author     GrandChris
/// \date       2020-10-19
///
inline std::suspend_always Task::promise_type::initial_suspend() { 
  std::cout << "initial_suspend" << std::endl;
  return {}; 
}

///
/// \brief      Action on Promise destruction
/// \author     GrandChris
/// \date       2020-10-19
///
inline std::suspend_never Task::promise_type::final_suspend() { 
  mFinished = true;
  std::cout << "final_suspend" << std::endl;
  return {}; 
}

///
/// \brief      co_retunr has been called
/// \author     GrandChris
/// \date       2020-10-19
///
inline void Task::promise_type::return_void() {

}

///
/// \brief      An exeption has been thrown
/// \author     GrandChris
/// \date       2020-10-19
///
inline void Task::promise_type::unhandled_exception() {

}

///
/// \brief      Returns if co_return has bee called
/// \author     GrandChris
/// \date       2020-10-19
///
inline bool Task::promise_type::finished() const {
  return mFinished;
}

///
/// \brief      Returns the allocated size of the coroutine
/// \author     GrandChris
/// \date       2020-10-19
///
inline size_t Task::promise_type::size() const {
  return mSize;
}

///
/// \brief      Allocates the memory for the coroutine
/// \author     GrandChris
/// \date       2020-10-19
///
inline void* Task::promise_type::operator new( size_t count) {
  lastSize = count;
  return new char[count];
}