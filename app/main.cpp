#include "profile.h"
#include "session.h"
#include "id.h"
#include <iostream>


int main(int, char**) {
    HG::Profile profile("Test", 10);
    profile.print();
    profile.setAge(20);
    HG::Profile copy(profile);
    copy.print();

    std::function<void (int)>cb =
            [](int a){ std::cout << "Library gave " << a << " to callback\n"; };


    HG::Session session(cb);
    HG::Session sessionAlias(session);
    sessionAlias.call();

    HG::Id id;
    id.applyLogic();
}
