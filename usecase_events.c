#include "usecase_events.h"

#include <errno.h>

#include "pipeline_wrapper.h"

#define IFX_MAX_TRACKS (sizeof(((ifx_result_t*)0)->sd_tracks.track_id) / sizeof(((ifx_result_t*)0)->sd_tracks.track_id[0]))
#define IFX_MAX_DETECTIONS_CW_MACRO_DETECTIONS (sizeof(((ifx_result_t*)0)->cw_macro_detections.data) / sizeof(((ifx_result_t*)0)->cw_macro_detections.data[0]))
#define IFX_MAX_DETECTIONS_CW_MICRO_DETECTIONS (sizeof(((ifx_result_t*)0)->cw_micro_detections.data) / sizeof(((ifx_result_t*)0)->cw_micro_detections.data[0]))
#define IFX_MAX_DETECTIONS_CW_STATIC_DETECTIONS (sizeof(((ifx_result_t*)0)->cw_static_detections.data) / sizeof(((ifx_result_t*)0)->cw_static_detections.data[0]))
#define IFX_MAX_ALL_DETECTIONS (IFX_MAX_DETECTIONS_CW_MACRO_DETECTIONS + IFX_MAX_DETECTIONS_CW_MICRO_DETECTIONS + IFX_MAX_DETECTIONS_CW_STATIC_DETECTIONS)

static struct
{
    ifx_presence_event presence;
    ifx_tracking_event tracking[IFX_MAX_TRACKS];
    uint32_t tracking_count;

    ifx_detection all_detections[IFX_MAX_ALL_DETECTIONS];
    uint32_t detection_count;
} g_events;

static uint32_t copy_detections(ifx_detection* dest, uint32_t dest_size,
                                const emxArray_ifx_Detection_t_16x2* src,
                                int type)
{
    if (!dest || !src)
    {
        return 0;
    }

    uint32_t total_elements = src->size[0];
    uint32_t copied_count = 0;

    for (uint32_t i=0; i < total_elements; i++)
    {
        if (copied_count >= dest_size)
        {
            break;
        }
        if (src->data[i].range_m == 0.0f)
        {
            break;
        }
        dest[copied_count].range = src->data[i].range_m;
        dest[copied_count].azimuth = src->data[i].azi_angle_deg;
        dest[copied_count].elevation = src->data[i].ele_angle_deg;
        dest[copied_count].doppler = src->data[i].doppler_mps;
        dest[copied_count].magnitude = src->data[i].magnitude_db;
        dest[copied_count].type = type;
        copied_count++;
    }

    return copied_count;
}

void ifx_usecase_events_update(const ifx_result_t* output)
{
    if (!output)
    {
        return;
    }

    g_events.tracking_count = 0;
    g_events.detection_count = 0;
    g_events.presence.state = false;
    g_events.presence.confidence = 0.0f;
    const ifx_tracks_t* tracks = &output->sd_tracks;
    const uint32_t max_tracks = sizeof(tracks->track_id) / sizeof(tracks->track_id[0]);
    for (uint32_t i=0; i < max_tracks; i++)
    {
        if (tracks->track_id[i])
        {
            g_events.tracking[g_events.tracking_count].id = (uint32_t)tracks->track_id[i];
            g_events.tracking[g_events.tracking_count].range = tracks->range_m[i];
            g_events.tracking[g_events.tracking_count].azimuth = tracks->azi_angle_deg[i];
            g_events.tracking[g_events.tracking_count].elevation = tracks->ele_angle_deg[i];
            g_events.tracking[g_events.tracking_count].speed = tracks->velocity_mps[i];
            g_events.tracking[g_events.tracking_count].activity = tracks->stats[i].activity;
            g_events.tracking[g_events.tracking_count].doppler = tracks->doppler_mps[i];
            g_events.tracking[g_events.tracking_count].is_static = false;
            g_events.tracking[g_events.tracking_count].confidence = 0.0f;
            g_events.tracking_count++;
        }
    }
    if (g_events.tracking_count > 0)
    {
        g_events.presence.state = true;
        g_events.presence.confidence = 1.0f;
    }
    g_events.detection_count += copy_detections(
        g_events.all_detections + g_events.detection_count,
        IFX_MAX_ALL_DETECTIONS - g_events.detection_count,
        &output->cw_macro_detections, (int)1);
    g_events.detection_count += copy_detections(
        g_events.all_detections + g_events.detection_count,
        IFX_MAX_ALL_DETECTIONS - g_events.detection_count,
        &output->cw_micro_detections, (int)2);
    g_events.detection_count += copy_detections(
        g_events.all_detections + g_events.detection_count,
        IFX_MAX_ALL_DETECTIONS - g_events.detection_count,
        &output->cw_static_detections, (int)3);
}

int ifx_usecase_get_detections(ifx_usecase_handle handle,
                               const ifx_detection** detections,
                               uint32_t* detections_count)
{
    if (!handle || !detections || !detections_count)
    {
        return -EINVAL;
    }

    *detections = &g_events.all_detections[0];
    *detections_count = g_events.detection_count;

    return 0;
}

int ifx_usecase_get_presence_event(ifx_usecase_handle handle,
                                   const ifx_presence_event** presence_event)
{
    if (!handle || !presence_event)
    {
        return -EINVAL;
    }

    *presence_event = &g_events.presence;

    return 0;
}

int ifx_usecase_get_tracking_events(ifx_usecase_handle handle,
                                    const ifx_tracking_event** tracking_events,
                                    uint32_t* tracking_events_count)
{
    if (!handle || !tracking_events || !tracking_events_count)
    {
        return -EINVAL;
    }

    *tracking_events = &g_events.tracking[0];
    *tracking_events_count = g_events.tracking_count;

    return 0;
}
