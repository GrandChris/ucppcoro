//
// \file       AwaitableLambda.h
// \author     GrandChris
// \date       2020-10-24
// \brief      An awaitable object
//

#pragma once

#include "Delegate.h"

#if !defined(__cpp_impl_coroutine)
    #define __cpp_impl_coroutine 1  // just for intellisense to work properly
#endif

#include <coroutine>
#include <concepts>

///
/// \class      AwaitableLambda.h
/// \author     GrandChris
/// \date       2020-10-14
/// \brief      Stores a lambda and calls it on "await_ready"
/// \param      T   Lambda function (or function object)
///
template<std::invocable T>
class AwaitableLambda {
public:

///////////////////////////////////////////////////////////////////////////////
// Constructors

    AwaitableLambda(T && lambda);

    AwaitableLambda(AwaitableLambda<T> && other);

///////////////////////////////////////////////////////////////////////////////
// Public Methods

    void registerDelegate(Delegate<bool()> * delegate);

    bool await_ready();

    void await_suspend(std::coroutine_handle<> h){}

    void await_resume() {}

private:

///////////////////////////////////////////////////////////////////////////////
// Member Variables

    T mLambda;  // holding a lambda function

    Delegate<bool()> * mAwaitReadyReference = nullptr; // pointer to a delegate holding a reference to the await_ready function
};



///////////////////////////////////////////////////////////////////////////////
// Implementation

///
/// \brief      Constructor
/// \author     GrandChris
/// \date       2020-10-25
/// \param      lambda   Lambda function returning true when ready
///
template <std::invocable T>
inline AwaitableLambda<T>::AwaitableLambda(T &&lambda)
    : mLambda(std::move(lambda))
{
    
}

///
/// \brief      Move Constructor
/// \author     GrandChris
/// \date       2020-10-25
/// \param      other   Other object 
/// \defails    Fun fact: The move constructor is never called (not even on -O0) because of "copy elision"
///             But the function is required for the compiler to create the right behaviour
///
template<std::invocable T>
inline AwaitableLambda<T>::AwaitableLambda(AwaitableLambda<T> && other) :
    mLambda(std::move(other.mLambda)),
    mAwaitReadyReference(std::move(other.mAwaitReadyReference))
{
    // also move the reference of the delegate to the new object
    if(mAwaitReadyReference != nullptr) {
        mAwaitReadyReference->set<AwaitableLambda<T>, &AwaitableLambda<T>::await_ready>(this);
    }
}

///
/// \brief      Registers a reference to the await_ready function
/// \author     GrandChris
/// \date       2020-10-25
/// \param      delegate   Pointer to a delegate to write a reference to the await_ready function
/// \defails    This function is required for the class "Task" to ask if the task is ready to resume
///
template<std::invocable T>
inline void AwaitableLambda<T>::registerDelegate(Delegate<bool()> * delegate) {
    mAwaitReadyReference = delegate;

    if(mAwaitReadyReference != nullptr) {
        mAwaitReadyReference->set<AwaitableLambda<T>, &AwaitableLambda<T>::await_ready>(this);
    }
}

///
/// \brief      Returns true if the condition is met to resume
/// \author     GrandChris
/// \date       2020-10-25
/// \return     True if it ready, false otherwise
///
template<std::invocable T>
inline bool AwaitableLambda<T>::await_ready() { 

    return mLambda(); 
}

