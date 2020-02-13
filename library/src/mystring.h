#ifndef HOURGLASS_MYSTRING_H
#define HOURGLASS_MYSTRING_H

#include <string>

struct mystring {
    std::string data;

    mystring(){}
    explicit mystring(const char* v) : data(v) {}

};


#endif //HOURGLASS_MYSTRING_H
