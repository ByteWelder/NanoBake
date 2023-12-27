#pragma once

#include "nb_hardware.h"
#include "nb_app.h"
#include "nb_config.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef void* FuriThreadId;
typedef struct nb_lvgl nb_lvgl_t;

__attribute__((unused)) extern void nanobake_start(nb_config_t _Nonnull * config);

extern FuriThreadId nanobake_get_app_thread_id(size_t index);
extern size_t nanobake_get_app_thread_count();

#ifdef __cplusplus
}
#endif