#include "usecase_settings.h"

ifx_usecase_settings_t ifx_usecase_settings_get_settings(const ifx_usecase_config* config)
{
    ifx_usecase_settings_t result;
    result.sensor_mounting = ifx_usecase_settings_get_sensor_mounting(config);
    result.fov = ifx_usecase_settings_get_fov(config);
    return result;
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_settings(ifx_usecase_config* config, const ifx_usecase_settings_t* value)
{
    if (config == NULL || value == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    ifx_usecase_settings_error_t rc_sensor_mounting = ifx_usecase_settings_set_sensor_mounting(config, &value->sensor_mounting);
    if (rc_sensor_mounting != IFX_USECASE_SETTINGS_OK) { return rc_sensor_mounting; }
    ifx_usecase_settings_error_t rc_fov = ifx_usecase_settings_set_fov(config, &value->fov);
    if (rc_fov != IFX_USECASE_SETTINGS_OK) { return rc_fov; }
    return IFX_USECASE_SETTINGS_OK;
}

ifx_usecase_settings_sensor_mounting_t ifx_usecase_settings_get_sensor_mounting(const ifx_usecase_config* config)
{
    ifx_usecase_settings_sensor_mounting_t result;
    result.orientation_tx = config->radar_mount_config.orientation_tx;
    result.tilt_angle_deg = config->radar_mount_config.tilt_angle_deg;
    result.mounting_height_m = config->radar_mount_config.mounting_height_m;
    return result;
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_sensor_mounting(ifx_usecase_config* config, const ifx_usecase_settings_sensor_mounting_t* value)
{
    if (config == NULL || value == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    config->radar_mount_config.orientation_tx = value->orientation_tx;
    if (value->tilt_angle_deg < -45.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value->tilt_angle_deg > 45.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->radar_mount_config.tilt_angle_deg = value->tilt_angle_deg;
    if (value->mounting_height_m < 0.5) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value->mounting_height_m > 5.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->radar_mount_config.mounting_height_m = value->mounting_height_m;
    return IFX_USECASE_SETTINGS_OK;
}

ifx_usecase_settings_sensor_mounting_orientation_tx_t ifx_usecase_settings_get_sensor_mounting_orientation_tx(const ifx_usecase_config* config)
{
    if (config == NULL) { return 0; }
    return config->radar_mount_config.orientation_tx;
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_sensor_mounting_orientation_tx(ifx_usecase_config* config, ifx_usecase_settings_sensor_mounting_orientation_tx_t value)
{
    if (config == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    config->radar_mount_config.orientation_tx = value;
    return IFX_USECASE_SETTINGS_OK;
}

float ifx_usecase_settings_get_sensor_mounting_tilt_angle_deg(const ifx_usecase_config* config)
{
    if (config == NULL) { return 0; }
    return config->radar_mount_config.tilt_angle_deg;
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_sensor_mounting_tilt_angle_deg(ifx_usecase_config* config, float value)
{
    if (config == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    if (value < -45.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value > 45.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->radar_mount_config.tilt_angle_deg = value;
    return IFX_USECASE_SETTINGS_OK;
}

float ifx_usecase_settings_get_sensor_mounting_mounting_height_m(const ifx_usecase_config* config)
{
    if (config == NULL) { return 0; }
    return config->radar_mount_config.mounting_height_m;
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_sensor_mounting_mounting_height_m(ifx_usecase_config* config, float value)
{
    if (config == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    if (value < 0.5) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value > 5.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->radar_mount_config.mounting_height_m = value;
    return IFX_USECASE_SETTINGS_OK;
}

ifx_usecase_settings_fov_t ifx_usecase_settings_get_fov(const ifx_usecase_config* config)
{
    ifx_usecase_settings_fov_t result;
    result.range_m = ifx_usecase_settings_get_fov_range_m(config);
    result.angle_deg = ifx_usecase_settings_get_fov_angle_deg(config);
    return result;
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_fov(ifx_usecase_config* config, const ifx_usecase_settings_fov_t* value)
{
    if (config == NULL || value == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    ifx_usecase_settings_error_t rc_range_m = ifx_usecase_settings_set_fov_range_m(config, &value->range_m);
    if (rc_range_m != IFX_USECASE_SETTINGS_OK) { return rc_range_m; }
    ifx_usecase_settings_error_t rc_angle_deg = ifx_usecase_settings_set_fov_angle_deg(config, &value->angle_deg);
    if (rc_angle_deg != IFX_USECASE_SETTINGS_OK) { return rc_angle_deg; }
    return IFX_USECASE_SETTINGS_OK;
}

ifx_usecase_settings_fov_range_m_t ifx_usecase_settings_get_fov_range_m(const ifx_usecase_config* config)
{
    ifx_usecase_settings_fov_range_m_t result;
    result.min = config->fov_config.min_max_ground_range[0];
    result.max = config->fov_config.min_max_ground_range[1];
    return result;
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_range_m(ifx_usecase_config* config, const ifx_usecase_settings_fov_range_m_t* value)
{
    if (config == NULL || value == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    if (value->min < 0.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value->min > 20.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->fov_config.min_max_ground_range[0] = value->min;
    if (value->max < 0.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value->max > 20.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->fov_config.min_max_ground_range[1] = value->max;
    return IFX_USECASE_SETTINGS_OK;
}

float ifx_usecase_settings_get_fov_range_m_min(const ifx_usecase_config* config)
{
    if (config == NULL) { return 0; }
    return config->fov_config.min_max_ground_range[0];
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_range_m_min(ifx_usecase_config* config, float value)
{
    if (config == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    if (value < 0.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value > 20.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->fov_config.min_max_ground_range[0] = value;
    return IFX_USECASE_SETTINGS_OK;
}

float ifx_usecase_settings_get_fov_range_m_max(const ifx_usecase_config* config)
{
    if (config == NULL) { return 0; }
    return config->fov_config.min_max_ground_range[1];
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_range_m_max(ifx_usecase_config* config, float value)
{
    if (config == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    if (value < 0.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value > 20.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->fov_config.min_max_ground_range[1] = value;
    return IFX_USECASE_SETTINGS_OK;
}

ifx_usecase_settings_fov_angle_deg_t ifx_usecase_settings_get_fov_angle_deg(const ifx_usecase_config* config)
{
    ifx_usecase_settings_fov_angle_deg_t result;
    result.min = config->fov_config.min_max_azimuth[0];
    result.max = config->fov_config.min_max_azimuth[1];
    return result;
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_angle_deg(ifx_usecase_config* config, const ifx_usecase_settings_fov_angle_deg_t* value)
{
    if (config == NULL || value == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    if (value->min < -90.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value->min > 90.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->fov_config.min_max_azimuth[0] = value->min;
    if (value->max < -90.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value->max > 90.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->fov_config.min_max_azimuth[1] = value->max;
    return IFX_USECASE_SETTINGS_OK;
}

float ifx_usecase_settings_get_fov_angle_deg_min(const ifx_usecase_config* config)
{
    if (config == NULL) { return 0; }
    return config->fov_config.min_max_azimuth[0];
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_angle_deg_min(ifx_usecase_config* config, float value)
{
    if (config == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    if (value < -90.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value > 90.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->fov_config.min_max_azimuth[0] = value;
    return IFX_USECASE_SETTINGS_OK;
}

float ifx_usecase_settings_get_fov_angle_deg_max(const ifx_usecase_config* config)
{
    if (config == NULL) { return 0; }
    return config->fov_config.min_max_azimuth[1];
}

ifx_usecase_settings_error_t ifx_usecase_settings_set_fov_angle_deg_max(ifx_usecase_config* config, float value)
{
    if (config == NULL) { return IFX_USECASE_SETTINGS_ERROR_NULL_POINTER; }
    if (value < -90.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    if (value > 90.0) { return IFX_USECASE_SETTINGS_ERROR_OUT_OF_RANGE; }
    config->fov_config.min_max_azimuth[1] = value;
    return IFX_USECASE_SETTINGS_OK;
}

