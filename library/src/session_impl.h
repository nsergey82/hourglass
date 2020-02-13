#ifndef HOURGLASS_SESSION_IMPL_H
#define HOURGLASS_SESSION_IMPL_H

#include <iostream>
#include <stdexcept>
#include "hourglass.h"
#include "session.h"

struct Session_t;

namespace HG {
class SessionImpl {
private:
    static int s_id;
    int id;

    SessionHandlerDispatcherPtr sdispatcher;
    Session_cb_t* callback;
public:
    SessionImpl() : id(++s_id) {
        std::cout << "ctor: session " << id << " @" << this << '\n';
    }

    SessionImpl(SessionHandlerDispatcherPtr dispatcher, Session_cb_t* fromUser)
        : sdispatcher(dispatcher), callback(fromUser){
        std::cout << "ctor: session with cb " << id << " @" << this << '\n';
    }

    ~SessionImpl() { std::cout << "dtor: session " << id << " @" << this << '\n'; }

    void print() const {
        std::cout << "Session " << getId() << " @" << this << '\n';
    }

    void call() {
        sdispatcher(callback, 42); // call through the hourglass
    }

    int getId() const { return id; }
};

}

template<>
struct HgHandles::ToImpl<Session_t>
: public HgHandles::TypeConverterMeta<Session_t, HG::SessionImpl, HgHandles::RefCount> {
};

template<>
struct HgHandles::FromImpl<HG::SessionImpl>
: public HgHandles::TypeConverterMeta<Session_t, HG::SessionImpl, HgHandles::RefCount> {
};

#endif //HOURGLASS_Session_IMPL_H

