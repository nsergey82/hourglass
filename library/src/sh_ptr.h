#ifndef SHPTR_H
#define SHPTR_H

#include <utility>
#include <cstddef>

// thread unsafe toy shared ptr with needed semantics
// proper thread-safe implementation is left as a challenge

// type erased core of shared ptr
struct ShPtrRep {
    void *ptr;
    size_t refCount;

    ShPtrRep(void* what = 0, size_t howMany=1) :
            ptr(what), refCount(howMany) {
    }

    template <typename T>
    T* asType() {
        return reinterpret_cast<T*>(ptr);
    }
    template <typename T>
    const T* asType() const {
        return reinterpret_cast<const T*>(ptr);
    }
};

template<typename T>
class ShPtr {
    ShPtrRep *cblock;

    void decref() {
        if(cblock) {
            --cblock->refCount;
            if(cblock->refCount == 0) {
                T* ptr = cblock->asType<T>();
                delete ptr;
                delete cblock;
                cblock = 0;
            }
        }
    }

public:
    ShPtr() : cblock(0) {}

    explicit ShPtr(ShPtrRep *rep) : cblock(rep) {}

    ShPtr(const ShPtr& other) {
        cblock = other.cblock;
        ++cblock->refCount;
    }

    ShPtr& operator=(const ShPtr& other) {
        decref();
        cblock = other.cblock;
        ++cblock->refCount;
    }

    ~ShPtr() {
        decref();
    }

    T &operator * () const { return *cblock->asType<T>(); }
    T *operator ->() const { return  cblock->asType<T>(); }

    size_t use_count() const { return cblock->refCount; }

    std::pair<T*, ShPtrRep*> release() {
        std::pair<T*, ShPtrRep*> result = std::make_pair(cblock->asType<T>(), cblock);
        cblock = 0;
        return result;
    }
};

template<typename T, typename... Args>
ShPtr<T> make_myshared(Args... args) {
    // Can be optimized to have just one allocation
    return ShPtr<T>(new ShPtrRep(new T(std::forward<Args>(args)...)));
}

#endif