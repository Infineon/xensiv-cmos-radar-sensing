#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "usecase_events_serialize.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

static inline char* _print_delimiter(char* buffer, size_t* size, size_t* pos)
{
    strncat(buffer, ",", *size);
    (*size)--;
    (*pos)++;
    return buffer + 1;
}

static inline int _print_presence(const ifx_presence_event* presence, char* json_buffer, size_t json_buffer_size)
{
    int result = snprintf(json_buffer, json_buffer_size, "\"presence\":{\"state\":%s, \"confidence\":%.2f}",
                          presence->state ? "true" : "false", presence->confidence);
    if (result < 0)
    {
        return -EINVAL;
    }
    return result;
}

static inline size_t _print_tracking(const ifx_tracking_event* tracks, uint32_t num_tracks, char* json_buffer,
                                     size_t json_buffer_size)
{
    const char track_preamble[] = "\"tracks\": {";
    const size_t track_preamble_size = sizeof(track_preamble) - 1;

    if (json_buffer_size < track_preamble_size)
    {
        return 0;
    }

    strncat(json_buffer, track_preamble, json_buffer_size);
    json_buffer_size -= track_preamble_size;
    size_t size = track_preamble_size;

    for (uint32_t i = 0; i < num_tracks; i++)
    {
        int cur_len = snprintf(json_buffer + size, json_buffer_size,
                       "\"%ld\":{\"range\":%.2f, \"azimuth\":%.2f, \"elevation\":%.2f, \"speed\": %.2f, \"doppler\": %.2f, \"activity\": %.1f}",
                               tracks[i].id,
                               tracks[i].range,
                               tracks[i].azimuth,
                               tracks[i].elevation,
                               tracks[i].speed,
                               tracks[i].doppler,
                               tracks[i].activity);

        if (cur_len <= 0 || (size_t)cur_len > json_buffer_size)
        {
            return 0;
        }
        size += cur_len;
        json_buffer_size -= cur_len;
        if (json_buffer_size && ((i + 1) < num_tracks))
        {
            _print_delimiter(json_buffer, &json_buffer_size, &size);
        }
    }

    if (json_buffer_size > 0)
    {
        strncat(json_buffer, "}", json_buffer_size);
        size += 1;
    }
    return size;
}

static inline size_t _print_detections(const ifx_detection* detections, uint32_t num_detections, char* json_buffer,
                                       size_t json_buffer_size)
{
    const char detection_preamble[] = "\"detections\": {";
    const size_t detection_preamble_size = sizeof(detection_preamble) - 1;

    if (json_buffer_size < detection_preamble_size)
    {
        return 0;
    }

    strncat(json_buffer, detection_preamble, json_buffer_size);
    json_buffer_size -= detection_preamble_size;
    size_t size = detection_preamble_size;

    const char attributes_preamble[] =
        "\"attributes\":[\"range\",\"azimuth\",\"elevation\",\"doppler\",\"magnitude\",\"type\"],";
    const size_t attributes_preamble_size = sizeof(attributes_preamble) - 1;

    if (json_buffer_size < attributes_preamble_size)
    {
        return 0;
    }

    strncat(json_buffer, attributes_preamble, json_buffer_size);
    json_buffer_size -= attributes_preamble_size;
    size += attributes_preamble_size;

    if (json_buffer_size < 8)
    {
        return 0;
    }

    strncat(json_buffer, "\"data\":[", json_buffer_size);
    json_buffer_size -= 8;
    size += 8;

    uint32_t printed = 0;
    for (uint32_t i = 0; i < num_detections; i++)
    {
        if (detections[i].range == 0.0f)
        {
            continue;
        }
        int cur_len = snprintf(json_buffer + size, json_buffer_size,
                               "[%.2f, %.2f, %.2f, %.2f, %.2f, %d]",
                               detections[i].range,
                               detections[i].azimuth,
                               detections[i].elevation,
                               detections[i].doppler,
                               detections[i].magnitude,
                               detections[i].type);

        if (cur_len <= 0 || (size_t)cur_len > json_buffer_size)
        {
            return 0;
        }
        size += cur_len;
        json_buffer_size -= cur_len;
        printed++;
        if (json_buffer_size && (printed < num_detections))
        {
            _print_delimiter(json_buffer, &json_buffer_size, &size);
        }
    }

    if (json_buffer_size > 1)
    {
        strncat(json_buffer, "]", json_buffer_size);
        json_buffer_size -= 1;
        size += 1;

        strncat(json_buffer, "}", json_buffer_size);
        size += 1;
    }
    return size;
}

static inline int ifx_usecase_helper_events_to_json(uint32_t ts,
                                                    ifx_event_flags events_flags,
                                                    const ifx_presence_event* presence,
                                                    const ifx_tracking_event* tracking, uint32_t num_tracks,
                                                    const ifx_detection* detections, uint32_t num_detections,
                                                    char* json_buffer, size_t json_buffer_size)
{
    char* buffer = json_buffer;
    size_t pos = 0;

    uint32_t h  = ts / 3600000U;
    uint32_t m  = (ts % 3600000U) / 60000U;
    uint32_t s  = (ts % 60000U) / 1000U;
    uint32_t ms = ts % 1000U;

    pos = snprintf(buffer, json_buffer_size, "{\"ts\":\"%02u:%02u:%02u.%03u\"", (unsigned int)h, (unsigned int)m, (unsigned int)s, (unsigned int)ms);
    if (pos <= 0)
    {
        return -EINVAL;
    }

    if ((size_t)pos > json_buffer_size)
    {
        return -EINVAL;
    }

    json_buffer_size -= pos;
    buffer = json_buffer + pos;

    if ((events_flags & IFX_EVENT_FLAG_PRESENCE) && presence)
    {
        buffer = _print_delimiter(buffer, &json_buffer_size, &pos);
        int len = _print_presence(presence, buffer, json_buffer_size);
        if (len <= 0 || (size_t)len > json_buffer_size)
        {
            return -EINVAL;
        }

        buffer = buffer + len;
        pos += len;
        json_buffer_size -= len;
    }

    if (events_flags & IFX_EVENT_FLAG_TRACKING)
    {
        buffer = _print_delimiter(buffer, &json_buffer_size, &pos);
        size_t len = _print_tracking(tracking, num_tracks, buffer, json_buffer_size);

        if (len == 0 || len > json_buffer_size)
        {
            return -EINVAL;
        }

        buffer = buffer + len;
        pos += len;
        json_buffer_size -= len;
    }

    if (events_flags & IFX_EVENT_FLAG_DETECTIONS)
    {
        buffer = _print_delimiter(buffer, &json_buffer_size, &pos);
        size_t len = _print_detections(detections, num_detections, buffer, json_buffer_size);
        if (len == 0 || len > json_buffer_size)
        {
            return -EINVAL;
        }

        buffer = buffer + len;
        pos += len;
        json_buffer_size -= len;
    }
    if (json_buffer_size <= 0)
    {
        return -EINVAL;
    }

    strncat(buffer, "}\n\0", json_buffer_size);
    pos += 3;

    return (int)pos;
}

int ifx_print_event(char* json_buffer,
                    size_t json_buffer_size,
                    ifx_usecase_handle handle,
                    ifx_event_flags events_flags,
                    uint32_t timestamp)
{
    if (!handle)
    {
        return -EINVAL;
    }

    const ifx_presence_event* presence_event = NULL;
    if (events_flags & IFX_EVENT_FLAG_PRESENCE)
    {
        if (ifx_usecase_get_presence_event(handle, &presence_event) < 0)
        {
            return -EINVAL;
        }
    }

    const ifx_tracking_event* tracking_events = NULL;
    uint32_t tracking_event_count = 0;
    if (events_flags & IFX_EVENT_FLAG_TRACKING)
    {
        if (ifx_usecase_get_tracking_events(handle, &tracking_events, &tracking_event_count) < 0)
        {
            return -EINVAL;
        }
    }

    const ifx_detection* detections = NULL;
    uint32_t num_detections = 0;
    if (events_flags & IFX_EVENT_FLAG_DETECTIONS)
    {
        if (ifx_usecase_get_detections(handle, &detections, &num_detections) < 0)
        {
            return -EINVAL;
        }
    }

    return ifx_usecase_helper_events_to_json(timestamp,
                                             events_flags,
                                             presence_event, tracking_events, tracking_event_count, detections,
                                             num_detections, json_buffer, json_buffer_size);
}
