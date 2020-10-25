//
// \file       Delegate.h
// \author     GrandChris
// \date       2020-10-14
// \brief      Function pointer to a member function
//

#pragma once

#include <concepts>

template<typename T>
class Delegate;

///
/// \class      Delegate.h
/// \author     GrandChris
/// \date       2020-10-14
/// \brief      Stores any member function
/// \param      R(Args)   function signature
/// \details     https://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates
///
template <typename R, typename... Args>
class Delegate<R(Args...)>
{
public:

///////////////////////////////////////////////////////////////////////////////
// Type Definitions

    using MethodPtr = R (*)(void * objectPtr, Args&&... args);  // Function signature
    
///////////////////////////////////////////////////////////////////////////////
// Public Methods

    R operator()(Args&&... args) const;

    template <typename T, R (T::*TMethod)(Args... args)>
    void set(T* objectPtr);

    template <std::invocable T>
    void set(T* objectPtr);

private:

///////////////////////////////////////////////////////////////////////////////
// Member Variables

    void * mObject = nullptr;       // Pointer to the object
    MethodPtr mMethod = nullptr;    // Pointer to the function of the object

///////////////////////////////////////////////////////////////////////////////
// Static Functions

    template <class T, R (T::*TMethod)(Args... args)>
    static R callMethod(void* objectPtr, Args&&... args);

    template <class T>
    static R callFunctor(void* objectPtr, Args&&... args);
};


///////////////////////////////////////////////////////////////////////////////
// Implementation

#include <utility>

///
/// \brief      Calls the stored function
/// \author     GrandChris
/// \date       2020-10-14
/// \param      args   function arguments
/// \return     R      function return type
///
template <typename R, typename... Args>
inline R Delegate<R(Args...)>::operator()(Args&&... args) const
{
    if(mObject != nullptr && mMethod != nullptr) {
        return (*mMethod)(mObject, std::forward<Args>(args)...);
    }  
    else {
        return {};
    }
}

///
/// \brief      Sets a member function
/// \author     GrandChris
/// \date       2020-10-14
/// \param      T          Clas type
/// \param      TMethod    Class Method
/// \param      objectPtr  Pointer to an object of this class
///
template <typename R, typename... Args>
template <typename T, R (T::*TMethod)(Args... args)>
inline void Delegate<R(Args...)>::set(T* objectPtr) 
{
    mObject = objectPtr;
    mMethod = &callMethod<T, TMethod>;
}

///
/// \brief      Sets a function object
/// \author     GrandChris
/// \date       2020-10-14
/// \param      T          Clas type
/// \param      TMethod    Class Method
/// \param      objectPtr  Pointer to an object of this class
///
template <typename R, typename... Args>
template <std::invocable T>
inline void Delegate<R(Args...)>::set(T* objectPtr) 
{
    mObject = objectPtr;
    mMethod = &callFunctor<T>;
}

///
/// \brief      Call a member function like a function pointer
/// \author     GrandChris
/// \date       2020-10-14
/// \param      T          Clas type
/// \param      TMethod    Class Method
/// \param      objectPtr  Pointer to an object of this class
/// \param      args       Arguments of the member function
///
template <typename R, typename... Args>
template <typename T, R (T::*TMethod)(Args... args)>
inline R Delegate<R(Args...)>::callMethod(void* objectPtr, Args&&... args)
{
    T* p = static_cast<T*>(objectPtr);
    return (p->*TMethod)(std::forward<Args>(args)...);
}

///
/// \brief      Call a member function like a function pointer
/// \author     GrandChris
/// \date       2020-10-14
/// \param      T          Clas type
/// \param      TMethod    Class Method
/// \param      objectPtr  Pointer to an object of this class
/// \param      args       Arguments of the member function
///
template <typename R, typename... Args>
template <typename T>
inline  R Delegate<R(Args...)>::callFunctor(void* objectPtr, Args&&... args) 
{
    T* p = static_cast<T*>(objectPtr);
    return (*p)(std::forward<Args>(args)...);
}