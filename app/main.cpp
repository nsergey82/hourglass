#include "profile.h"
#include "session.h"
#include "session_b.h"
#include "id.h"
#include <iostream>


int main(int, char**) {
    HG::Profile profile("Alice", 11);
    profile.print();
    profile.setAge(12);
    HG::Profile copy(profile);
    copy.print();


    HG::Id id;
    id.applyLogic();

    // this is your std::function<void (int)>
    auto cb =
            [](int a){ std::cout << "Library gave " << a << " to callback\n"; };

    HG::Session session(cb);
    HG::Session sessionAlias(session);
    session.print(std::cout);
    sessionAlias.call();

    // `sessionAlias.call()` conceptually the same as:
    Session_cb_t *cbptr = reinterpret_cast<Session_cb_t*>(&cb);
    SessionHandlerCallerPtr  caller = &HG::dispatchAny<decltype(cb)>;
    caller(cbptr, 42);

    HG::SessionB sessionB;
    HG::SessionB sessionBAlias(sessionB);

    std::cout << "======\n";

}
