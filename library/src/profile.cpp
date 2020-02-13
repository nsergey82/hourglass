#include "profile.h"
#include "profile_impl.h"
#include "hourglass.h"

#include <iostream>

int Profile_create (Profile_t **handle, const char* n, int a) {
    *handle = HgHandles::release(new HG::ProfileImpl(mystring(n), a));
    return 0;
}

int Profile_destroy(Profile_t *handle) {
    auto ptr = HgHandles::ptr(handle);
    delete ptr;
    return 0;
}

int Profile_copy(const Profile_t *src, Profile_t **dest) {
    auto ptr = HgHandles::ptr(src);
    *dest = HgHandles::release(new HG::ProfileImpl(*ptr));
    return 0;
}

int Profile_print  (const Profile_t *handle) {
    auto ptr = HgHandles::ptr(handle);
    ptr->print();
    return 0;
}

int Profile_setAge (Profile_t *handle, int age) {
    auto ptr = HgHandles::ptr(handle);
    try {
        ptr->setAge(age);
    }
    catch (...) {
        return -1;
    }
    return 0;
}

int Profile_getAge (const Profile_t *handle, int *age) {
    auto ptr = HgHandles::ptr(handle);
    *age = ptr->getAge();
    return 0;
}

int Profile_getName(const Profile_t *handle, const char **name) {
    auto ptr = HgHandles::ptr(handle);
    *name =  ptr->getName().data.c_str();
    return 0;
}

int Profile_setName(Profile_t *handle, const char *name) {
    auto ptr = HgHandles::ptr(handle);
    ptr->setName(mystring(name));
    return 0;
}
