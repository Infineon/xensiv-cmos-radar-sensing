#ifndef USECASE_SETTINGS_H
#define USECASE_SETTINGS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "usecase_types.h"

/**
 * Presence Detection and Tracking Use-Case Settings
 * Configuration settings for presence detection and tracking use case
 */

// Error codes for settings API
typedef enum {
    IFX_USECASE_SETTINGS_OK = 0,
    IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE,
    IFX_USECASE_SETTINGS_ERROR_INVALID_VALUE,
    IFX_USECASE_SETTINGS_ERROR_NULL_POINTER
} ifx_usecase_settings_error_t;

/**
 * TX Antenna Orientation
 * Transmit antenna orientation configuration
 * Type: enum
 * Default: 0
 * Enum: TopLeft=0, BottomLeft=1, TopRight=2, BottomRight=3
 */
typedef enum {
    IFX_USECASE_SETTINGS_SENSOR_MOUNTING_ORIENTATION_TX_TOPLEFT = 0,
    IFX_USECASE_SETTINGS_SENSOR_MOUNTING_ORIENTATION_TX_BOTTOMLEFT = 1,
    IFX_USECASE_SETTINGS_SENSOR_MOUNTING_ORIENTATION_TX_TOPRIGHT = 2,
    IFX_USECASE_SETTINGS_SENSOR_MOUNTING_ORIENTATION_TX_BOTTOMRIGHT = 3,
} ifx_usecase_settings_sensor_mounting_orientation_tx_t;

/**
 * Sensor Mounting
 * Radar sensor mounting and orientation configuration
 * Type: group
 */
typedef struct {
    /**
     * orientation_tx: TX Antenna Orientation
     * Transmit antenna orientation configuration
     * Type: enum
     * Default: 0
     * Enum: TopLeft=0, BottomLeft=1, TopRight=2, BottomRight=3
     */
    ifx_usecase_settings_sensor_mounting_orientation_tx_t orientation_tx;
    /**
     * tilt_angle_deg: Tilt Angle
     * Radar tilt angle in degrees (positive is downward)
     * Type: float
     * Range: -45.0 to 45.0
     * Step: 0.5
     * Default: 0.0
     */
    float tilt_angle_deg;
    /**
     * mounting_height_m: Mounting Height
     * Radar mounting height above ground in meters
     * Type: float
     * Range: 0.5 to 5.0
     * Step: 0.1
     * Default: 1.5
     */
    float mounting_height_m;
} ifx_usecase_settings_sensor_mounting_t;

/**
 * Range
 * Range settings in meters
 * Type: group
 */
typedef struct {
    /**
     * min: Minimum Range
     * Minimum detection range in meters
     * Type: float
     * Range: 0.0 to 20.0
     * Step: 0.001
     * Default: 0.0
     */
    float min;
    /**
     * max: Maximum Range
     * Maximum detection range in meters
     * Type: float
     * Range: 0.0 to 20.0
     * Step: 0.001
     * Default: 10.0
     */
    float max;
} ifx_usecase_settings_fov_range_m_t;

/**
 * Azimuth Angle
 * Azimuth angle settings in degrees
 * Type: group
 */
typedef struct {
    /**
     * min: Minimum Azimuth Angle
     * Minimum azimuth angle in degrees (field of view)
     * Type: float
     * Range: -90.0 to 90.0
     * Step: 1.0
     * Default: -90.0
     */
    float min;
    /**
     * max: Maximum Azimuth Angle
     * Maximum azimuth angle in degrees (field of view)
     * Type: float
     * Range: -90.0 to 90.0
     * Step: 1.0
     * Default: 90.0
     */
    float max;
} ifx_usecase_settings_fov_angle_deg_t;

/**
 * Field of View
 * Field of view configuration for detection area
 * Type: group
 */
typedef struct {
    /**
     * range_m: Range
     * Range settings in meters
     * Type: group
     */
    ifx_usecase_settings_fov_range_m_t range_m;
    /**
     * angle_deg: Azimuth Angle
     * Azimuth angle settings in degrees
     * Type: group
     */
    ifx_usecase_settings_fov_angle_deg_t angle_deg;
} ifx_usecase_settings_fov_t;

/**
 * Presence Detection and Tracking Use-Case Settings
 * Configuration settings for presence detection and tracking use case
 * Type: group
 */
struct ifx_usecase_settings_t {
    /**
     * sensor_mounting: Sensor Mounting
     * Radar sensor mounting and orientation configuration
     * Type: group
     */
    ifx_usecase_settings_sensor_mounting_t sensor_mounting;
    /**
     * fov: Field of View
     * Field of view configuration for detection area
     * Type: group
     */
    ifx_usecase_settings_fov_t fov;
};

// Forward declarations
/**
 * Presence Detection and Tracking Use-Case Settings
 * Configuration settings for presence detection and tracking use case
 * Type: group
 */
IFX_USECASE_API ifx_usecase_settings_t ifx_usecase_settings_get_settings(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_settings(ifx_usecase_config* config, const ifx_usecase_settings_t* value);
/**
 * Sensor Mounting
 * Radar sensor mounting and orientation configuration
 * Type: group
 */
IFX_USECASE_API ifx_usecase_settings_sensor_mounting_t ifx_usecase_settings_get_sensor_mounting(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_sensor_mounting(ifx_usecase_config* config, const ifx_usecase_settings_sensor_mounting_t* value);
/**
 * TX Antenna Orientation
 * Transmit antenna orientation configuration
 * Type: enum
 * Default: 0
 * Enum: TopLeft=0, BottomLeft=1, TopRight=2, BottomRight=3
 */
IFX_USECASE_API ifx_usecase_settings_sensor_mounting_orientation_tx_t ifx_usecase_settings_get_sensor_mounting_orientation_tx(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_sensor_mounting_orientation_tx(ifx_usecase_config* config, ifx_usecase_settings_sensor_mounting_orientation_tx_t value);
/**
 * Tilt Angle
 * Radar tilt angle in degrees (positive is downward)
 * Type: float
 * Range: -45.0 to 45.0
 * Step: 0.5
 * Default: 0.0
 */
IFX_USECASE_API float ifx_usecase_settings_get_sensor_mounting_tilt_angle_deg(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_sensor_mounting_tilt_angle_deg(ifx_usecase_config* config, float value);
/**
 * Mounting Height
 * Radar mounting height above ground in meters
 * Type: float
 * Range: 0.5 to 5.0
 * Step: 0.1
 * Default: 1.5
 */
IFX_USECASE_API float ifx_usecase_settings_get_sensor_mounting_mounting_height_m(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_sensor_mounting_mounting_height_m(ifx_usecase_config* config, float value);
/**
 * Field of View
 * Field of view configuration for detection area
 * Type: group
 */
IFX_USECASE_API ifx_usecase_settings_fov_t ifx_usecase_settings_get_fov(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_fov(ifx_usecase_config* config, const ifx_usecase_settings_fov_t* value);
/**
 * Range
 * Range settings in meters
 * Type: group
 */
IFX_USECASE_API ifx_usecase_settings_fov_range_m_t ifx_usecase_settings_get_fov_range_m(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_range_m(ifx_usecase_config* config, const ifx_usecase_settings_fov_range_m_t* value);
/**
 * Minimum Range
 * Minimum detection range in meters
 * Type: float
 * Range: 0.0 to 20.0
 * Step: 0.001
 * Default: 0.0
 */
IFX_USECASE_API float ifx_usecase_settings_get_fov_range_m_min(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_range_m_min(ifx_usecase_config* config, float value);
/**
 * Maximum Range
 * Maximum detection range in meters
 * Type: float
 * Range: 0.0 to 20.0
 * Step: 0.001
 * Default: 10.0
 */
IFX_USECASE_API float ifx_usecase_settings_get_fov_range_m_max(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_range_m_max(ifx_usecase_config* config, float value);
/**
 * Azimuth Angle
 * Azimuth angle settings in degrees
 * Type: group
 */
IFX_USECASE_API ifx_usecase_settings_fov_angle_deg_t ifx_usecase_settings_get_fov_angle_deg(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_angle_deg(ifx_usecase_config* config, const ifx_usecase_settings_fov_angle_deg_t* value);
/**
 * Minimum Azimuth Angle
 * Minimum azimuth angle in degrees (field of view)
 * Type: float
 * Range: -90.0 to 90.0
 * Step: 1.0
 * Default: -90.0
 */
IFX_USECASE_API float ifx_usecase_settings_get_fov_angle_deg_min(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_angle_deg_min(ifx_usecase_config* config, float value);
/**
 * Maximum Azimuth Angle
 * Maximum azimuth angle in degrees (field of view)
 * Type: float
 * Range: -90.0 to 90.0
 * Step: 1.0
 * Default: 90.0
 */
IFX_USECASE_API float ifx_usecase_settings_get_fov_angle_deg_max(const ifx_usecase_config* config);
IFX_USECASE_API ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_angle_deg_max(ifx_usecase_config* config, float value);

#endif /* USECASE_SETTINGS_H */
