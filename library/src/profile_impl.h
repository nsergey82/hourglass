#ifndef HOURGLASS_PROFILE_IMPL_H
#define HOURGLASS_PROFILE_IMPL_H

#include <iostream>
#include <stdexcept>

#include "mystring.h"
#include "hourglass.h"

struct Profile_t;

namespace HG {


class ProfileImpl {
private:
    mystring name;
    int age;
public:
    ProfileImpl(const mystring &n = mystring("N"), int a = 22) :
            name(n), age(a) {
        std::cout << "ctor: " << name.data << " @" << this << '\n';
    }

    ~ProfileImpl() { std::cout << "dtor: " << name.data << " @" << this << '\n'; }

    int getAge() const { return age; }

    const mystring &getName() const { return name; }

    void setAge(int a) {
        if (a <= 0) {
            throw std::invalid_argument("negative age");
        }
        age = a;
    }

    void setName(const mystring &n) { name = n; }

    void print() const {
        std::cout << name.data << ' ' << age << " @" << this << '\n';
    }
};

}

template<>
struct HgHandles::ToImpl<Profile_t>
: public HgHandles::TypeConverterMeta<Profile_t, HG::ProfileImpl, HgHandles::Raw> {
};

template<>
struct HgHandles::FromImpl<HG::ProfileImpl>
        : public HgHandles::TypeConverterMeta<Profile_t, HG::ProfileImpl, HgHandles::Raw> {
};

#endif //HOURGLASS_PROFILE_IMPL_H
