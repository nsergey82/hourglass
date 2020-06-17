#ifndef HOURGLASS_ID_H
#define HOURGLASS_ID_H

#ifdef __cplusplus
extern "C" {
#endif

int Id_create(int *v1, int *v2);
int Id_applyLogic(int *v1, int *v2);

#ifdef __cplusplus
}
#endif

#include "dispatch.h"

#ifdef __cplusplus
#include <stdexcept>

namespace HG {
struct Id {
    int value1;
    int value2;

    Id();
    void applyLogic();
};

inline Id::Id() {
    if(Id_create(&value1, &value2))
        throw std::runtime_error("Failed in ctor");
}

inline void Id::applyLogic() {
    if(Id_applyLogic(&value1, &value2))
        throw std::runtime_error("Failed in applyLogic");
}

}
#endif


#endif //HOURGLASS_ID_H
