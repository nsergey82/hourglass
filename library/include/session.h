#ifndef SESSION_H
#define SESSION_H
#include <ostream>
#include <functional>

#ifdef __cplusplus

// public side C++ callback type
typedef std::function<void (int)> SessionCB;

extern "C" {
#endif

struct Session_t;
// Properly name all types that travel through hourglass, don't just void*
struct Session_cb_t; // opaque callback type for session
struct stream_t; // opaque type for streams

// public side C callback, takes an int and propagates it to user callback
typedef void (*SessionHandlerCallerPtr)(Session_cb_t*, int);
// public side C callback to stream data via type erased stream
typedef int (*streamcb)(const char *data, int length, stream_t *stream);

// this will call the correct callback
void sessionDispatch(Session_cb_t* cb, int v);


int Session_create  (Session_t **handle);
int Session_create_f(Session_t **handle,
                     SessionHandlerCallerPtr caller,
                     Session_cb_t* fromUser);
int Session_copy    (const Session_t *src, Session_t **dest);
int Session_destroy (Session_t *handle);
int Session_print   (const Session_t *handle, streamcb cb, stream_t* stream);
int Session_call    (Session_t *handle);
#ifdef __cplusplus
}
#endif

#include "dispatch.h"

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
    Session(const Session& other); // shallow copy, just increment ref. count
    ~Session();
    void print(std::ostream& out) const;
    void call();
};

inline Session::Session() {
    // instead of using direct call we go through dispatch table
    if(HG_CALL_SESSION_CREATE((Session_t**)&handle))
        throw std::runtime_error("Failed in ctor");
}

inline Session::~Session() {
    assert(0 == Session_destroy(handle));
}

inline Session::Session(const Session& other) {
    if(Session_copy(other.handle, &handle))
        throw std::runtime_error("Failed in copy ctor");
}

inline void Session::call() {
    if(Session_call(handle))
        throw std::runtime_error("Failed calling");
}


// Generic stream writer: write to type erased stream out
template<typename Stream>
int streamOut(const char *data, int length, stream_t* stream) {
    reinterpret_cast<Stream*>(stream)->write(data, length);
    return 0;
}

inline Session::Session(const SessionCB& fromUser) : cb(fromUser){
    if(Session_create_f(
            &handle,
            &sessionDispatch,
            reinterpret_cast<Session_cb_t*>(&cb)))
        throw std::runtime_error("Failed in cb ctor");
}

inline void Session::print(std::ostream& out) const {
    Session_print(handle, streamOut<std::ostream>, (stream_t*)&out);
}

}
#endif

#endif //HOURGLASS_SESSION_H
