#include "dispatch.h"

#include "session.h"
#include "profile.h"

unsigned g_DispatchSize = sizeof(Dispatch_t);
Dispatch_t g_DispatchEntries = {
        &Session_create,
        &Profile_create
};