#ifndef USECASE_EVENTS_H
#define USECASE_EVENTS_H

#include <stdbool.h>
#include <stdint.h>

#include "usecase_types.h"

/* Use-case track event */
typedef struct
{
    float range;
    float azimuth;
    float elevation;
    float speed;
    float doppler;
    float activity;
    bool is_static;
    uint32_t id;
    float confidence;
} ifx_tracking_event;

typedef enum
{
    IFX_DETECTION_TYPE_CW_MACRO = 1,
    IFX_DETECTION_TYPE_CW_MICRO = 2,
    IFX_DETECTION_TYPE_CW_STATIC = 3
} ifx_detection_type;

typedef struct
{
    float range;
    float azimuth;
    float elevation;
    float doppler;
    float magnitude;
    ifx_detection_type type;
} ifx_detection;

/* Presence event. */
typedef struct
{
    bool state;
    float confidence;
} ifx_presence_event;

/**
 * @brief Gets a pointer to a list of detection events.
 * @note The event is only valid until the next call to ifx_usecase_process.
 * @param handle Usecase handle
 * @param[out] detections A pointer to a pointer of type ifx_detection,
 * which will point to the internal retrieved detection event structure.
 * @param[out] detections_count Number of detections returned through detections pointer.
 * @return 0 on success, a negative value on error.
 * @see ifx_detection
 */
IFX_USECASE_API int ifx_usecase_get_detections(ifx_usecase_handle handle,
                                               const ifx_detection** detections,
                                               uint32_t* detections_count);

/**
 * @brief Gets a pointer to the presence event.
 *
 * @note The event is only valid until the next call to ifx_usecase_process.
 *
 * @param handle Usecase handle
 * @param[out] presence_event A pointer to a pointer of type ifx_presence_event,
 * which will point to the internal retrieved presence event structure.
 * @return 0 on success, a negative value on error.
 * @see ifx_presence_event
 */
IFX_USECASE_API int ifx_usecase_get_presence_event(ifx_usecase_handle handle,
                                                   const ifx_presence_event** presence_event);

/**
 * @brief Gets a pointer to a list of tracking events.
 *
 * @note The event is only valid until the next call to ifx_usecase_process.
 *
 * @param handle Usecase handle
 * @param[out] tracking_events A pointer to a pointer of type ifx_tracking_event,
 * which will point to the internal retrieved tracking event structure.
 * @param[out] tracking_events_count Number of events returned through tracking_events pointer.
 * @return 0 on success, a negative value on error.
 * @see ifx_tracking_event
 */
IFX_USECASE_API int ifx_usecase_get_tracking_events(ifx_usecase_handle handle,
                                                    const ifx_tracking_event** tracking_events,
                                                    uint32_t* tracking_events_count);

#endif /* USECASE_EVENTS_H */
