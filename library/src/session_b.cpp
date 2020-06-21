#include <sstream>
#include <memory>

#include "sh_ptr.h"

#include "session_impl.h"
#include "session_b.h"
#include "hourglass.h"

typedef std::shared_ptr<HG::SessionImpl> Impl;

int SessionB_create(SessionB_t **handle) {
    std::shared_ptr<HG::SessionImpl>* sptrptr
        = new std::shared_ptr<HG::SessionImpl>(
                std::make_shared<HG::SessionImpl>());
    *handle = reinterpret_cast<SessionB_t*>(sptrptr);
    return 0;
}

int SessionB_destroy(SessionB_t *handle) {
    std::cout << "Calling destroy for session-b @" << handle << '\n';
    delete reinterpret_cast<std::shared_ptr<HG::SessionImpl>*>(handle);
    return 0;
}

int SessionB_copy(const SessionB_t *src, SessionB_t **dest) {
    Impl* srcptr = const_cast<Impl*>(reinterpret_cast<const Impl*>(src));
    Impl* newptr = new Impl(*srcptr); // another owner of src allocated on heap
    *dest = reinterpret_cast<SessionB_t *>(newptr);
    return 0;
}
