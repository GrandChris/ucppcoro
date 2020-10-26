//
// \file       type_traits_function_pointer.h
// \author     GrandChris
// \date       2020-10-26
// \brief      type traits for function pointers
//

#pragma once

#include <type_traits>
#include <tuple>

///
/// \class      return_type
/// \author     GrandChris
/// \date       2020-10-26
/// \brief      Deduces the return type of a function pointer at compile time. 
///
template <typename T>
struct return_type;

template <typename R, typename... Args>
struct return_type<R (*)(Args...)>
{
    using type = R;
};

///
/// \class      argument_type
/// \author     GrandChris
/// \date       2020-10-26
/// \brief      Deduces the argument types of a function pointer at compile time. 
///
template <typename T>
struct argument_type;

template <typename R, typename... Args>
struct argument_type<R (*)(Args...)>
{
    static size_t const size = sizeof...(Args);

    template<size_t i>
    using type = std::tuple_element<i, std::tuple<Args...>>::type;

    template<size_t i>
    using type_noref = std::remove_reference<type<i>>::type;

    template<template<typename...> typename T>
    using apply = T<Args...>;

    using tuple = std::tuple<Args...>;
    using tuple_noref = std::tuple<std::remove_reference_t<Args>...>;
};

///
/// \class      is_function_ptr
/// \author     GrandChris
/// \date       2020-10-26
/// \brief      Determines if the template is a function pointer 
///
template<typename T>
struct is_function_ptr {
    static constexpr bool value = false;
};

template <typename R, typename... Args>
struct is_function_ptr<R (*)(Args...)> {
    static constexpr bool value = true;
};

template<typename T>
inline constexpr bool is_function_ptr_v = is_function_ptr<T>::value;