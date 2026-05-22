#ifndef USECASE_EVENTS_SERIALIZE_H
#define USECASE_EVENTS_SERIALIZE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "usecase_events.h"

/* List of events */
typedef enum
{
    IFX_EVENT_FLAG_NONE = 0,
    IFX_EVENT_FLAG_PRESENCE = 0x1 << 0,
    IFX_EVENT_FLAG_ZONING = 0x1 << 1,
    IFX_EVENT_FLAG_TRACKING = 0x1 << 2,
    IFX_EVENT_FLAG_DETECTIONS = 0x1 << 3,
    IFX_EVENT_FLAG_ALL = 0xFFFFFFFF,
} ifx_event_flags;

/**
 * @brief Print events as JSONL format to a buffer.
 *
 * @param json_buffer Output buffer
 * @param json_buffer_size Output buffer size
 * @param handle Usecase handle
 * @param events_flags Event flags that shall be written to the output buffer
 * @param timestamp Timestamp in milliseconds
 * @param elapsed_time Elapsed time for the use-case processing in milliseconds
 * @param frames_dropped Dropped frames since last use-case processing
 * @return IFX_USECASE_API
 */
IFX_USECASE_API int ifx_print_event(char* json_buffer,
                                    size_t json_buffer_size,
                                    ifx_usecase_handle handle,
                                    ifx_event_flags events_flags,
                                    uint32_t timestamp);

#endif /* USECASE_EVENTS_SERIALIZE_H */
