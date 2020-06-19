#include "profile.h"
#include "session.h"
#include "id.h"
#include <iostream>


int main(int, char**) {
    HG::Profile profile("Alice", 11);
    profile.print();
    profile.setAge(12);
    HG::Profile copy(profile);
    copy.print();

    std::function<void (int)>cb =
            [](int a){ std::cout << "Library gave " << a << " to callback\n"; };


    HG::Session session(cb);
    HG::Session sessionAlias(session);
    session.print(std::cout);
    sessionAlias.call();

    HG::Id id;
    id.applyLogic();

    std::cout << "======\n";
}
