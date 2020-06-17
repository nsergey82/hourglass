#ifndef HOURGLASS_DISPATCH_H
#define HOURGLASS_DISPATCH_H


#ifdef __cplusplus
extern "C" {
#endif

// forward declare:
struct Session_t;
struct Profile_t;

// #if defined(_WIN32) || defined(__WIN32__)
#define HG_EXPORT /* your platform export here */

typedef struct Dispatch {
    int (*Session_create)(Session_t**);
    int (*Profile_create)(Profile_t**, const char*, int);
} Dispatch_t;

HG_EXPORT extern unsigned   g_DispatchSize;
HG_EXPORT extern Dispatch_t g_DispatchEntries;


#ifdef __cplusplus
}

#define HG_CALL_SESSION_CREATE(a1) g_DispatchEntries.Session_create(a1)
#define HG_CALL_PROFILE_CREATE(a1, a2, a3) g_DispatchEntries.Profile_create(a1, a2, a3)

#endif

#endif //HOURGLASS_DISPATCH_H
