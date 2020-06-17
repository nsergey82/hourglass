#ifndef PROFILE_H
#define PROFILE_H

#ifdef __cplusplus  
extern "C" { 
#endif 

struct Profile_t;

// C layer
  int Profile_create (Profile_t **handle, const char* n, int a);
  int Profile_copy   (const Profile_t *src, Profile_t **dest);
  int Profile_destroy(Profile_t *handle);
  int Profile_getAge (const Profile_t *handle, int *age);
  int Profile_getName(const Profile_t *handle, const char **name);
  int Profile_setAge (Profile_t *handle, int age);
  int Profile_setName(Profile_t *handle, const char *name);
  int Profile_print  (const Profile_t *handle);
#ifdef __cplusplus  
} 
#endif

#include "dispatch.h"

#ifdef __cplusplus  
#include <stdexcept>
#include <cassert>

namespace HG {
class Profile {
private:
  Profile_t* handle;

public:
  Profile(const std::string& n = "N", int a = 22);
  Profile(const Profile& other); // deep copy
  ~Profile();

  int getAge() const;
  std::string getName() const;
  void setAge(int a);
  void setName(const std::string& n);
  void print() const;
};

inline Profile::Profile(const std::string& n, int a) {
  if(HG_CALL_PROFILE_CREATE(&handle, n.c_str(), a))
        throw std::runtime_error("Failed in ctor");
}

inline Profile::~Profile() {
    int rc = Profile_destroy(handle);
    assert(0 == rc);
}

inline Profile::Profile(const Profile& other) {
  if(Profile_copy(other.handle, &handle))
    throw std::runtime_error("Failed in copy ctor");
}

inline void Profile::setAge(int a) {
  if(Profile_setAge(handle, a))
    throw std::runtime_error("Failed setting age");  
}

inline int Profile::getAge() const {
    int age;
    if(Profile_getAge(handle, &age))
        throw std::runtime_error("Failed getting age");
    return age;
}

inline std::string Profile::getName() const {
    const char* name;
    if(Profile_getName(handle, &name))
        throw std::runtime_error("Failed getting name");
    return std::string(name);
}

inline void Profile::setName(const std::string& name) {
    if(Profile_setName(handle, name.c_str()))
        throw std::runtime_error("Failed setting name");
}


inline void Profile::print() const {
  if(Profile_print(handle))
    throw std::runtime_error("Failed printing");
} 
}
#endif 
#endif
