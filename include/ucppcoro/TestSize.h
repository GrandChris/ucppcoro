//
// \file       TestSize.h
// \author     GrandChris
// \date       2020-10-26
// \brief      Asserts the size of a coroutine
//

#pragma once

#include "type_traits_function_pointer.h"

#include <concepts>
#include <cassert>


template<typename T>
concept FuncPtr = is_function_ptr_v<T>;


///
/// \brief      Checks if the coroutine can be successfully allocated
/// \author     GrandChris
/// \date       2020-10-26
/// \param      coroutine   A pointer to a function returning a "Task<>"
///
template<FuncPtr T>
inline size_t testSize(T coroutine) 
{
    using TTask = return_type<T>::type;
    using Args = argument_type<T>::tuple_noref;
    Args args;

    TTask task = std::apply(coroutine, args);

    if(task.size() > TTask::max_size) 
    {   // allocation failed
        [[maybe_unused]] size_t const size = task.size();
        assert(false); 
        return task.size();
    }
    else 
    {   // allocation was successful
        task.destroy();
        return task.size();
    } 
}