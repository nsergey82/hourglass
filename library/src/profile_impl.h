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
    ProfileImpl(const mystring &n = mystring("N"), int a = 22);
    ~ProfileImpl();

    int getAge() const;
    const mystring & getName() const;

    void setAge(int a);
    void setName(const mystring &n);

    void print() const;
};

    ProfileImpl::ProfileImpl(const mystring &n, int a) :
            name(n), age(a) {
        std::cout << "ctor: " << name.data << " @" << this << '\n';
    }

    ProfileImpl::~ProfileImpl() { std::cout << "dtor: " << name.data << " @" << this << '\n'; }

    int ProfileImpl::getAge() const { return age; }

    const mystring& ProfileImpl::getName() const { return name; }

    void ProfileImpl::setAge(int a) {
        if (a <= 0) {
            throw std::invalid_argument("negative age");
        }
        age = a;
    }

    void ProfileImpl::setName(const mystring &n) { name = n; }

    void ProfileImpl::print() const {
        std::cout << name.data << ' ' << age << " @" << this << '\n';
    }
};


template<>
struct HgHandles::ToImpl<Profile_t>
: public HgHandles::TypeConverterMeta<Profile_t, HG::ProfileImpl, HgHandles::Raw> {
};

template<>
struct HgHandles::FromImpl<HG::ProfileImpl>
        : public HgHandles::TypeConverterMeta<Profile_t, HG::ProfileImpl, HgHandles::Raw> {
};

#endif //HOURGLASS_PROFILE_IMPL_H
