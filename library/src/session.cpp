#include "sh_ptr.h"

#include "session_impl.h"
#include "session.h"
#include "hourglass.h"

int HG::SessionImpl::s_id(0);

int Session_create (Session_t **handle) {
    *handle = HgHandles::release(make_myshared<HG::SessionImpl>());
    return 0;
}

int Session_create_f(Session_t **handle, SessionHandlerDispatcherPtr dispatcher, Session_cb_t* fromUser)
{
    *handle = HgHandles::release(make_myshared<HG::SessionImpl>(dispatcher, fromUser));
    return 0;
}

int Session_destroy(Session_t *handle) {
    std::cout << "Calling destroy for session @"  << handle << '\n';
    auto rep = HgHandles::repr(handle, HgHandles::RefCount());
    ShPtr<HG::SessionImpl> shptr(rep);
    return 0;
}

int Session_copy(const Session_t *src, Session_t **dest) {
    *dest = reinterpret_cast<Session_t*>(HgHandles::clone(const_cast<Session_t*>(src)));
    return 0;
}

int Session_call(Session_t *handle){
    HgHandles::ptr(handle)->call();
    return 0;
}