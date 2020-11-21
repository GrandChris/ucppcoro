//
// \file       Event.h
// \author     GrandChris
// \date       2020-11-21
// \brief      Class for storing function pointers
//

// #pragma once

// #include "ucppcoro/Delegate.h"

// #include <cstddef>


// template<size_t N, typename T>
// class Event;


// ///
// /// \class      Event.h
// /// \author     GrandChris
// /// \date       2020-10-14
// /// \brief      Stores functions
// /// \param      N      Maximum number of functions
// /// \param      Args   Arguments
// ///
// template<size_t N, typename R, typename ...Args>
// class Event<N, R(Args...)> {
// public:
    
// ///////////////////////////////////////////////////////////////////////////////
// // Public Methods

//     void operator()(Args... args) const;

//     template <auto Method, typename T>
//     bool add(T* objectPtr);

//     template <typename T>
//     bool add(T* objectPtr);

//     // template <auto Function>
//     // bool add();

// private:

// ///////////////////////////////////////////////////////////////////////////////
// // Type Definitions

//     using DelegateType = Delegate<R(Args...)>;

// ///////////////////////////////////////////////////////////////////////////////
// // Member Variables

//     size_t mSize = 0;
//     std::array<DelegateType, N> mFunctions = {};
// };

// ///////////////////////////////////////////////////////////////////////////////
// // Implementation

// template<size_t N, typename R, typename ...Args>
// inline void Event<N, R(Args...)>::operator()(Args... args) const 
// {
//     for(size_t i = 0; i < mSize; ++i) {
//         mFunctions[i](args...);
//     }
// }

// template<size_t N, typename R, typename ...Args>
// template <auto Method, typename T>
// inline bool Event<N, R(Args...)>::add(T* objectPtr) 
// {
//     if(mSize < mFunctions.size() && objectPtr != nullptr) {
//         auto delegate = mFunctions[mSize++];

//         auto func = Delegate<R(Args...)>::setMethod<Method, T>;

//         // delegate.setMethod<Method, T>(objectPtr);
//         // mFunctions[mSize++].set<Method>(objectPtr);
//         return true;
//     }
//     else {
//         return false;
//     }
// }

// template<size_t N, typename R, typename ...Args>
// template <typename T>
// inline bool Event<N, R(Args...)>::add(T* objectPtr) 
// {
//     if(mSize < mFunctions.size() && objectPtr != nullptr) {
//         mFunctions[mSize++].set(objectPtr);
//         return true;
//     }
//     else {
//         return false;
//     }
// }

// // template<size_t N, typename R, typename ...Args>
// // template <auto Function>
// // inline bool Event<N, R(Args...)>::add() 
// // {
// //     if(mSize < mFunctions.size()) {
// //         mFunctions[mSize++].set<Function>();
// //         return true;
// //     }
// //     else {
// //         return false;
// //     }
// // }