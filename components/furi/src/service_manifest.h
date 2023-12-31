#pragma once

#include <stdio.h>
#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ServiceOnStart)(Context* context);
typedef void (*ServiceOnStop)(Context* context);

typedef struct {
    /**
     * The identifier by which the app is launched by the system and other apps.
     */
    const char* _Nonnull id;

    /**
     * Non-blocking method to call when service is started.
     */
    const ServiceOnStart _Nullable on_start;

    /**
     * Non-blocking method to call when service is stopped.
     */
    const ServiceOnStop _Nullable on_stop;

} ServiceManifest;

#ifdef __cplusplus
}
#endif
