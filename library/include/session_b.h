#ifndef SESSION_B_H
#define SESSION__BH
#include <ostream>
#include <functional>

#ifdef __cplusplus

extern "C" {
#endif

struct SessionB_t;

int SessionB_create  (SessionB_t **handle);
int SessionB_copy    (const SessionB_t *src, SessionB_t **dest);
int SessionB_destroy (SessionB_t *handle);
#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

#include <stdexcept>
#include <cassert>
#include <functional>

namespace HG {
class SessionB {
public:


private:
    SessionB_t* handle;

public:
    SessionB();
    SessionB(const SessionB& other); // shallow copy, just increment ref. count
    ~SessionB();
};

inline SessionB::SessionB() {
    // instead of using direct call we go through dispatch table
    if(SessionB_create((SessionB_t**)&handle))
        throw std::runtime_error("Failed in ctor");
}

inline SessionB::~SessionB() {
    assert(0 == SessionB_destroy(handle));
}

inline SessionB::SessionB(const SessionB& other) {
    if(SessionB_copy(other.handle, &handle))
        throw std::runtime_error("Failed in copy ctor");
}

}
#endif

#endif //HOURGLASS_SESSION_H
