#include "usecase.h"

#include <errno.h>
#include <string.h>

#include "usecase_events.h"
#include "pipeline_wrapper.h"

void ifx_usecase_events_update(const ifx_result_t* output);

struct ifx_usecase
{
    ifx_usecase_config vcfg;
};

int ifx_usecase_get_default_configuration(ifx_usecase_config* cfg)
{
    if (!cfg)
    {
        return -EINVAL;
    }

    pipeline_get_default_config(cfg);

    return 0;
}

static struct ifx_usecase g_current_usecase = { 0 };

int ifx_usecase_get_version(const char** sem_ver, const char** name, const char** settings, const char** build)
{
    if (!sem_ver || !name || !settings || !build)
    {
        return -EINVAL;
    }

    *sem_ver = IFX_USECASE_ALGO_BUILD_VERSION;
    *name = IFX_USECASE_ALGO_NAME;
    *settings = IFX_USECASE_ALGO_BUILD_SETTINGS;
    *build = IFX_USECASE_ALGO_BUILD_HASH "+" IFX_USECASE_ALGO_BUILD_SETTINGS;

    return 0;
}

ifx_usecase_handle ifx_usecase_init(const ifx_usecase_config* cfg)
{
    memset(&g_current_usecase, 0, sizeof(g_current_usecase));
    if (cfg)
    {
        g_current_usecase.vcfg = *cfg;
    }
    else
    {
        pipeline_get_default_config(&g_current_usecase.vcfg);
    }

    pipeline_init(&g_current_usecase.vcfg);

    return &g_current_usecase;
}

int ifx_usecase_deinit(ifx_usecase_handle* handle)
{
    if (!handle)
    {
        return -EINVAL;
    }

    *handle = NULL;

    return 0;
}

int ifx_usecase_get_configuration(ifx_usecase_handle handle, ifx_usecase_config* cfg)
{
    if (!handle || !cfg)
    {
        return -EINVAL;
    }

    *cfg = handle->vcfg;
    return 0;
}

int ifx_usecase_set_configuration(ifx_usecase_handle handle, const ifx_usecase_config* cfg)
{
    if (!handle || !cfg)
    {
        return -EINVAL;
    }

    handle->vcfg = *cfg;
    pipeline_init(&handle->vcfg);

    return 0;
}

int ifx_usecase_get_default_settings(ifx_usecase_settings* settings)
{
    if (!settings)
    {
        return -EINVAL;
    }

    ifx_usecase_config vcfg;
    pipeline_get_default_config(&vcfg);
    *settings = ifx_usecase_settings_get_settings(&vcfg);

    return 0;
}

int ifx_usecase_get_settings(ifx_usecase_handle handle,
                             ifx_usecase_settings* settings)
{
    if (!handle || !settings)
    {
        return -EINVAL;
    }

    *settings = ifx_usecase_settings_get_settings(&handle->vcfg);

    return 0;
}

static int map_settings_error(ifx_usecase_settings_error_t rc)
{
    int result = -EINVAL;

    switch (rc)
    {
    case IFX_USECASE_SETTINGS_OK:
        result = 0;
        break;
    case IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE:
        result = -ERANGE;
        break;
    case IFX_USECASE_SETTINGS_ERROR_INVALID_VALUE:
        result = -EINVAL;
        break;
    case IFX_USECASE_SETTINGS_ERROR_NULL_POINTER:
        result = -EINVAL;
        break;
    default:
        result = -EINVAL;
        break;
    }

    return result;
}

int ifx_usecase_set_settings(ifx_usecase_handle handle,
                             const ifx_usecase_settings* settings)
{
    if (!handle || !settings)
    {
        return -EINVAL;
    }

    ifx_usecase_settings_error_t rc = ifx_usecase_settings_set_settings(&handle->vcfg, settings);
    if (rc != IFX_USECASE_SETTINGS_OK)
    {
        return map_settings_error(rc);
    }

    pipeline_init(&handle->vcfg);

    return 0;
}

int ifx_usecase_process(ifx_usecase_handle handle,
                        bool reset,
                        const uint16_t* frame,
                        ifx_event_flags* event_flags)
{
    if (!handle || !frame)
    {
        return -EINVAL;
    }

    (void)reset;

    ifx_result_t output;
    pipeline_process(frame, &output);
    ifx_usecase_events_update(&output);
    *event_flags = IFX_EVENT_FLAG_TRACKING | IFX_EVENT_FLAG_DETECTIONS;

    return 0;
}
