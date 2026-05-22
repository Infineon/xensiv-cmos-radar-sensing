#ifndef USECASE_SETTINGS_SERIALIZE_H
#define USECASE_SETTINGS_SERIALIZE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "usecase_settings.h"

/**
 * @brief Returns the JSON schema for the user-configurable settings.
 *
 * The returned string is a null-terminated, statically allocated JSON Schema
 * document describing all user-configurable settings and their constraints.
 *
 * @return Null-terminated JSON Schema string.
 */
IFX_USECASE_API const char* ifx_usecase_settings_schema_json(void);

/**
 * @brief Serializes the user settings to a JSON string.
 *
 * @param[in]  config           Configuration whose settings to serialize.
 * @param[out] json_buffer      Buffer to write the JSON string into.
 * @param[in]  json_buffer_size Size of @p json_buffer in bytes.
 * @return true on success, false if the buffer is too small or serialization fails.
 */
IFX_USECASE_API bool ifx_usecase_settings_serialize(const ifx_usecase_config* config, char* json_buffer, size_t json_buffer_size);

/**
 * @brief Deserializes a JSON string into the user settings of a configuration.
 *
 * @param[in]  json_str JSON string to parse.
 * @param[out] config   Configuration whose settings are populated from @p json_str.
 * @return true on success, false if parsing fails.
 */
IFX_USECASE_API bool ifx_usecase_settings_deserialize(const char* json_str, ifx_usecase_config* config);

#endif /* USECASE_SETTINGS_SERIALIZE_H */
