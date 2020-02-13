#ifndef SESSION_H
#define SESSION_H
#include <functional>

#ifdef __cplusplus
typedef std::function<void (int)> SessionCB; // public side type
extern "C" {
#endif

struct Session_t;

// C layer
struct Session_cb_t; // opaque callback type for session

// dispatcher
inline void sessionHandlerDispatcher(Session_cb_t* cb, int v) {
    (*reinterpret_cast<SessionCB* >(cb))(v);
}

typedef void (*SessionHandlerDispatcherPtr)(Session_cb_t*, int);

int Session_create  (Session_t **handle);
int Session_create_f(Session_t **handle, SessionHandlerDispatcherPtr dispatcher, Session_cb_t* fromUser);
int Session_copy    (const Session_t *src, Session_t **dest);
int Session_destroy (Session_t *handle);
int Session_print   (const Session_t *handle);
int Session_call    (Session_t *handle);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <stdexcept>
#include <cassert>
#include <functional>

namespace HG {
class Session {
public:


private:
    Session_t* handle;
    SessionCB cb;

public:
    Session();
    explicit Session(const SessionCB& fromUser);
    Session(const Session& other); // shallow copy, just inc. ref. count
    ~Session();
    void print() const;
    void call();
};

inline Session::Session() {
    if(Session_create(&handle))
        throw std::runtime_error("Failed in ctor");
}

inline Session::~Session() {
    assert(0 == Session_destroy(handle));
}

inline Session::Session(const Session& other) {
    if(Session_copy(other.handle, &handle))
        throw std::runtime_error("Failed in copy ctor");
}

inline void Session::print() const {
    if(Session_print(handle))
        throw std::runtime_error("Failed printing");
}

inline void Session::call() {
    if(Session_call(handle))
        throw std::runtime_error("Failed calling");
}

inline Session::Session(const SessionCB& fromUser) : cb(fromUser){
    if(Session_create_f(
            &handle,
            &sessionHandlerDispatcher,
            reinterpret_cast<Session_cb_t*>(&cb)))
        throw std::runtime_error("Failed in cb ctor");
}

}
#endif

#endif //HOURGLASS_SESSION_H