#ifndef USECASE_CONFIG_SERIALIZE_H
#define USECASE_CONFIG_SERIALIZE_H

#include <stdbool.h>
#include <stdint.h>
#include "usecase_types.h"

/**
 * @brief Serializes the use-case configuration to a JSON string.
 *
 * @param[in]  config           Configuration to serialize.
 * @param[out] json_buffer      Buffer to write the JSON string into.
 * @param[in]  json_buffer_size Size of @p json_buffer in bytes.
 * @return true on success, false if the buffer is too small or serialization fails.
 */
IFX_USECASE_API bool ifx_usecase_config_serialize(const ifx_usecase_config* config, char* json_buffer, size_t json_buffer_size);

/**
 * @brief Deserializes a JSON string into a use-case configuration.
 *
 * @param[in]  json_str JSON string to parse.
 * @param[out] config   Configuration populated from the JSON string.
 * @return true on success, false if parsing fails.
 */
IFX_USECASE_API bool ifx_usecase_config_deserialize(const char* json_str, ifx_usecase_config* config);

#endif /* USECASE_CONFIG_SERIALIZE_H */
