#ifndef USECASE_H
#define USECASE_H

#include <stdbool.h>
#include <stdint.h>
#include "usecase_types.h"
#include "usecase_settings.h"
#include "usecase_settings_serialize.h"
#include "usecase_config_serialize.h"
#include "usecase_events.h"
#include "usecase_events_serialize.h"

#ifndef IFX_USECASE_ALGO_BUILD_VERSION
#define IFX_USECASE_ALGO_BUILD_VERSION "1.0.0-ab0a816+common.indoorSmartar17"
#endif

#ifndef IFX_USECASE_ALGO_BUILD_HASH
#define IFX_USECASE_ALGO_BUILD_HASH "ab0a816"
#endif

#ifndef IFX_USECASE_ALGO_NAME
#define IFX_USECASE_ALGO_NAME "common"
#endif

#ifndef IFX_USECASE_ALGO_BUILD_SETTINGS
#define IFX_USECASE_ALGO_BUILD_SETTINGS "indoorSmartar17"
#endif

#ifndef IFX_BUILD_INFO
#define IFX_BUILD_INFO IFX_USECASE_ALGO_BUILD_HASH "+" IFX_USECASE_ALGO_BUILD_SETTINGS
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Constant values */
typedef enum
{
    IFX_USECASE_RADAR_FRAME_TX_ANTENNAS = 1,
    IFX_USECASE_RADAR_FRAME_RX_ANTENNAS = 3,
    IFX_USECASE_RADAR_FRAME_CHIRPS = 17,
    IFX_USECASE_RADAR_FRAME_SAMPLES = 64,

    IFX_USECASE_RADAR_FRAME_TOTAL_SAMPLES = (IFX_USECASE_RADAR_FRAME_TX_ANTENNAS *
                                             IFX_USECASE_RADAR_FRAME_RX_ANTENNAS *
                                             IFX_USECASE_RADAR_FRAME_CHIRPS *
                                             IFX_USECASE_RADAR_FRAME_SAMPLES),

    IFX_USECASE_RADAR_FRAME_SIZE = IFX_USECASE_RADAR_FRAME_TOTAL_SAMPLES * 2
} ifx_usecase_constants;

/**
 * @brief Retrieves the version information of the use case.
 *
 * This function returns the version information of the use case, including the semantic
 * version, name, settings, and build information.
 *
 * @param[out] sem_ver The semantic version of the use case (e.g., "1.2.3").
 * @param[out] name The name of the use case.
 * @param[out] settings The settings configuration name.
 * @param[out] build The build information of the use case.
 * @return 0 on success, a negative value on error.
 */
IFX_USECASE_API int ifx_usecase_get_version(const char** sem_ver, const char** name, const char** settings, const char** build);

/**
 * @brief Retrieves the default configuration for a use case.
 *
 * This function returns the default configuration for a use case, which
 * can be used as a starting point for customization.
 *
 * @param[out] cfg The default configuration for the use case.
 * @return 0 on success, a negative value on error.
 */
IFX_USECASE_API int ifx_usecase_get_default_configuration(ifx_usecase_config* cfg);

/**
 * @brief Initializes a use case with a given configuration.
 *
 * This function initializes a use case with the provided configuration.
 * The configuration can be customized using the default configuration
 * as a starting point.
 *
 * @param[in] cfg The configuration for the use case.
 * @return A handle to the initialized use case
 */
IFX_USECASE_API ifx_usecase_handle ifx_usecase_init(const ifx_usecase_config* cfg);

/**
 * @brief Deinitializes a use case.
 *
 * This function releases any resources allocated by the use case and
 * deinitializes it.
 *
 * @param[in,out] handle Usecase handle
 * @return 0 on success, a negative value on error.
 */
IFX_USECASE_API int ifx_usecase_deinit(ifx_usecase_handle* handle);

/**
 * @brief Retrieves the current configuration of a use case.
 *
 * This function returns the current configuration of a use case,
 * which can be used to inspect or modify the configuration.
 *
 * @param[in] handle Usecase handle
 * @param[out] cfg The current configuration of the use case.
 * @return 0 on success, a negative value on error.
 */
IFX_USECASE_API int ifx_usecase_get_configuration(ifx_usecase_handle handle, ifx_usecase_config* cfg);

/**
 * @brief Sets the configuration of a use case.
 *
 * This function sets the configuration of a use case and reinitializes
 * the pipeline with the new configuration.
 *
 * @param[in] handle Usecase handle
 * @param[in] cfg The configuration for the use case.
 * @return 0 on success, a negative value on error.
 */
IFX_USECASE_API int ifx_usecase_set_configuration(ifx_usecase_handle handle, const ifx_usecase_config* cfg);

/**
 * @brief Process a radar frame.
 *
 * @param handle Usecase handle
 * @param reset True if the pipeline needs to be reset
 * @param frame Radar frame
 * @param[out] event_flags Event flags indicating what events occurred
 * @return 0 on success, a negative value on error.
 */
IFX_USECASE_API int ifx_usecase_process(ifx_usecase_handle handle,
                                        bool reset,
                                        const uint16_t* frame,
                                        ifx_event_flags* event_flags);

/**
 * @brief Get the default settings of the use case.
 *
 * Copies the default settings into the given settings structure
 *
 * @param settings Settings structure
 * @return 0 on success, a negative value on error.
 */
IFX_USECASE_API int ifx_usecase_get_default_settings(ifx_usecase_settings* settings);

/**
 * @brief Get current settings of the use case.
 *
 * @param handle Usecase handle
 * @param settings Settings
 * @return 0 on success, a negative value on error.
 */
IFX_USECASE_API int ifx_usecase_get_settings(ifx_usecase_handle handle,
                                             ifx_usecase_settings* settings);

/**
 * @brief Set settings of the use case.
 *
 * @param handle Usecase handle
 * @param settings Settings
 * @return 0 on success, a negative value on error.
 */
IFX_USECASE_API int ifx_usecase_set_settings(ifx_usecase_handle handle,
                                             const ifx_usecase_settings* settings);

#ifdef __cplusplus
}
#endif

#endif /* USECASE_H */
