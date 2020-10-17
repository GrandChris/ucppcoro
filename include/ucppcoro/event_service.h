//
// \file       event_service.h
// \author     Christian Steinbrecher
// \date       2020-10-11
// \brief      Processes all events until there are none left
//

#pragma once

struct awaitable {
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<> h){}
    void await_resume() {}
};


class EventService
{
    public:

};