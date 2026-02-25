/**
 * @file pipeline_wrapper.h
 * @brief Header file for the simple C wrapper
 */

#ifndef PIPELINE_WRAPPER_H
#define PIPELINE_WRAPPER_H

#include "internal_pipeline_process_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

/**
 * @brief Get default configuration
 * @details Fills the provided config structure with default values
 *
 * @param config Configuration structure to fill
 *
 * @return 0 on success, non-zero on error
 */
EXPORT int pipeline_get_default_config(ifx_var_config_t* config);

/**
 * @brief Configure and initialize the processing pipeline
 * @details Must be called before any processing
 *
 * @param config Configuration structure
 *
 * @return 0 on success, non-zero on error
 */
EXPORT int pipeline_init(const ifx_var_config_t* config);

/**
 * @brief Process a radar frame using stateful wrapper API
 *
 * @param radar_frame Input radar frame data (3264 uint16 values)
 * @param output Output structure (will be filled by this function)
 *
 * @return 0 on success, non-zero on error
 */
EXPORT int pipeline_process(const uint16_t* radar_frame,
                            ifx_result_t* output);

#ifdef __cplusplus
}
#endif

#endif /* PIPELINE_WRAPPER_H */
