#ifndef USECASE_TYPES_H
#define USECASE_TYPES_H

#include "internal_pipeline_process_types.h"

#ifndef IFX_USECASE_API
#ifdef _WIN32
#define IFX_USECASE_API __declspec(dllexport)
#else
#define IFX_USECASE_API
#endif
#endif

struct ifx_usecase;
typedef struct ifx_usecase* ifx_usecase_handle;

/* Use-case configuration. */
typedef ifx_var_config_t ifx_usecase_config;

/* Use-case settings. */
typedef struct ifx_usecase_settings_t ifx_usecase_settings_t;
typedef ifx_usecase_settings_t ifx_usecase_settings;

#endif /* USECASE_TYPES_H */
