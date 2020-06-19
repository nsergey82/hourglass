#ifndef HOURGLASS_H
#define HOURGLASS_H

#include "sh_ptr.h"

struct HgHandles {

struct Raw {};
struct RefCount {};

template<typename Opaque, typename Impl, typename Tag>
struct TypeConverterMeta {
    typedef Opaque opaque;
    typedef Impl impl;
    typedef Tag tag;
};

template<typename Opaque>
struct ToImpl;

template<typename Opaque>
struct FromImpl;

template<typename T>
struct ConstPreserve {
    typedef typename ToImpl<T>::tag tag;
    typedef typename ToImpl<T>::impl impl;
    static impl* rep(T* ptr) {
        ShPtrRep *rep = reinterpret_cast<ShPtrRep *>(ptr);
        return rep->asType<impl>();
    }
};

template<typename T>
struct ConstPreserve<const T> {
    typedef typename ToImpl<T>::tag tag;
    typedef const typename ToImpl<T>::impl impl;
    static impl* rep(const T* ptr) {
        const ShPtrRep *rep = reinterpret_cast<const ShPtrRep *>(ptr);
        return rep->asType<impl>();
    }
};

template<typename Opaque>
static typename ConstPreserve<Opaque>::impl *ptr(Opaque *p, Raw) {
    return reinterpret_cast<typename ConstPreserve<Opaque>::impl *>(p);
}

template<typename Opaque>
static typename ConstPreserve<Opaque>::impl *ptr(Opaque *p, RefCount) {
    return ConstPreserve<Opaque>::rep(p);
}

template<typename Opaque>
static ShPtrRep *repr(Opaque *p, RefCount) {
    ShPtrRep* rep = reinterpret_cast<ShPtrRep*>(p);
    return rep;
}


template<typename Opaque>
static ShPtrRep *clone(Opaque *p, RefCount) {
    static_assert(
            !std::is_const<Opaque>::value,
            "Will not be able to bump ref. count of const");
    auto rep = repr(p, RefCount());
    ++rep->refCount;
    return rep;
}


template<typename Opaque>
static ShPtrRep *clone(Opaque *p) {
    return clone(p, typename ConstPreserve<Opaque>::tag());
}


template<typename Opaque>
static typename ConstPreserve<Opaque>::impl *ptr(Opaque *p) {
    return ptr(p, typename ConstPreserve<Opaque>::tag());
}

template<typename Impl>
static typename FromImpl<Impl>::opaque *release(Impl *p) {
    return reinterpret_cast<typename FromImpl<Impl>::opaque *>(p);
}

template<typename Impl>
static typename FromImpl<Impl>::opaque *release(ShPtr<Impl> p) {
    return reinterpret_cast<typename FromImpl<Impl>::opaque *>(p.release().second);
}

};

#endif