#include "usecase_settings_serialize.h"
#include <stdio.h>
#include <string.h>
#include "json.h"

const char* ifx_usecase_settings_schema_json(void)
{
    return
        "{\n"
        "  \"type\": \"group\",\n"
        "  \"title\": \"Presence Detection and Tracking Use-Case Settings\",\n"
        "  \"description\": \"Configuration settings for presence detection and tracking use case\",\n"
        "  \"entries\": {\n"
        "    \"sensor_mounting\": {\n"
        "      \"type\": \"group\",\n"
        "      \"title\": \"Sensor Mounting\",\n"
        "      \"description\": \"Radar sensor mounting and orientation configuration\",\n"
        "      \"entries\": {\n"
        "        \"orientation_tx\": {\n"
        "          \"type\": \"enum\",\n"
        "          \"title\": \"TX Antenna Orientation\",\n"
        "          \"description\": \"Transmit antenna orientation configuration\",\n"
        "          \"enumeration\": {\n"
        "            \"TopLeft\": 0,\n"
        "            \"BottomLeft\": 1,\n"
        "            \"TopRight\": 2,\n"
        "            \"BottomRight\": 3\n"
        "          },\n"
        "          \"default\": 0\n"
        "        },\n"
        "        \"tilt_angle_deg\": {\n"
        "          \"type\": \"float\",\n"
        "          \"title\": \"Tilt Angle\",\n"
        "          \"description\": \"Radar tilt angle in degrees (positive is downward)\",\n"
        "          \"min\": -45.0,\n"
        "          \"max\": 45.0,\n"
        "          \"step\": 0.5,\n"
        "          \"default\": 0\n"
        "        },\n"
        "        \"mounting_height_m\": {\n"
        "          \"type\": \"float\",\n"
        "          \"title\": \"Mounting Height\",\n"
        "          \"description\": \"Radar mounting height above ground in meters\",\n"
        "          \"min\": 0.5,\n"
        "          \"max\": 5.0,\n"
        "          \"step\": 0.1,\n"
        "          \"default\": 1.5\n"
        "        }\n"
        "      }\n"
        "    },\n"
        "    \"fov\": {\n"
        "      \"type\": \"group\",\n"
        "      \"title\": \"Field of View\",\n"
        "      \"description\": \"Field of view configuration for detection area\",\n"
        "      \"entries\": {\n"
        "        \"range_m\": {\n"
        "          \"type\": \"group\",\n"
        "          \"title\": \"Range\",\n"
        "          \"description\": \"Range settings in meters\",\n"
        "          \"entries\": {\n"
        "            \"min\": {\n"
        "              \"type\": \"float\",\n"
        "              \"title\": \"Minimum Range\",\n"
        "              \"description\": \"Minimum detection range in meters\",\n"
        "              \"min\": 0.0,\n"
        "              \"max\": 20.0,\n"
        "              \"step\": 0.001,\n"
        "              \"default\": 0\n"
        "            },\n"
        "            \"max\": {\n"
        "              \"type\": \"float\",\n"
        "              \"title\": \"Maximum Range\",\n"
        "              \"description\": \"Maximum detection range in meters\",\n"
        "              \"min\": 0.0,\n"
        "              \"max\": 20.0,\n"
        "              \"step\": 0.001,\n"
        "              \"default\": 10\n"
        "            }\n"
        "          }\n"
        "        },\n"
        "        \"angle_deg\": {\n"
        "          \"type\": \"group\",\n"
        "          \"title\": \"Azimuth Angle\",\n"
        "          \"description\": \"Azimuth angle settings in degrees\",\n"
        "          \"entries\": {\n"
        "            \"min\": {\n"
        "              \"type\": \"float\",\n"
        "              \"title\": \"Minimum Azimuth Angle\",\n"
        "              \"description\": \"Minimum azimuth angle in degrees (field of view)\",\n"
        "              \"min\": -90.0,\n"
        "              \"max\": 90.0,\n"
        "              \"step\": 1.0,\n"
        "              \"default\": -90\n"
        "            },\n"
        "            \"max\": {\n"
        "              \"type\": \"float\",\n"
        "              \"title\": \"Maximum Azimuth Angle\",\n"
        "              \"description\": \"Maximum azimuth angle in degrees (field of view)\",\n"
        "              \"min\": -90.0,\n"
        "              \"max\": 90.0,\n"
        "              \"step\": 1.0,\n"
        "              \"default\": 90\n"
        "            }\n"
        "          }\n"
        "        }\n"
        "      }\n"
        "    }\n"
        "  }\n"
        "}\n"
        ;
}

bool ifx_usecase_settings_serialize(const ifx_usecase_config* config, char* json_buffer, size_t json_buffer_size)
{
    int offset = 0;
    int ret;
    
    #define APPEND(...) do { \
        ret = snprintf(json_buffer + offset, json_buffer_size - offset, __VA_ARGS__); \
        if (ret < 0 || (size_t)ret >= json_buffer_size - offset) { return false; } \
        offset += ret; \
    } while(0)
    
    APPEND("{");
    APPEND("\"sensor_mounting\":");
    APPEND("{");
    APPEND("\"orientation_tx\":");
    APPEND("%d", config->radar_mount_config.orientation_tx);
    APPEND(",");
    APPEND("\"tilt_angle_deg\":");
    APPEND("%.6f", config->radar_mount_config.tilt_angle_deg);
    APPEND(",");
    APPEND("\"mounting_height_m\":");
    APPEND("%.6f", config->radar_mount_config.mounting_height_m);
    APPEND("}");
    APPEND(",");
    APPEND("\"fov\":");
    APPEND("{");
    APPEND("\"range_m\":");
    APPEND("{");
    APPEND("\"min\":");
    APPEND("%.6f", config->fov_config.min_max_ground_range[0]);
    APPEND(",");
    APPEND("\"max\":");
    APPEND("%.6f", config->fov_config.min_max_ground_range[1]);
    APPEND("}");
    APPEND(",");
    APPEND("\"angle_deg\":");
    APPEND("{");
    APPEND("\"min\":");
    APPEND("%.6f", config->fov_config.min_max_azimuth[0]);
    APPEND(",");
    APPEND("\"max\":");
    APPEND("%.6f", config->fov_config.min_max_azimuth[1]);
    APPEND("}");
    APPEND("}");
    APPEND("}");
    json_buffer[offset] = 0;
    return true;
}

bool ifx_usecase_settings_deserialize(const char* json_str, ifx_usecase_config* config)
{
    struct json root = json_parse(json_str);
    if (!json_exists(root))
    {
        return false;
    }
    
    {
        struct json field1 = json_get(json_str, "sensor_mounting");
        if (json_exists(field1))
        {
            {
                struct json field2 = json_object_get(field1, "orientation_tx");
                if (json_exists(field2))
                {
                    config->radar_mount_config.orientation_tx = (ifx_usecase_settings_sensor_mounting_orientation_tx_t)json_int(field2);
                }
            }
            {
                struct json field3 = json_object_get(field1, "tilt_angle_deg");
                if (json_exists(field3))
                {
                    config->radar_mount_config.tilt_angle_deg = (float)json_double(field3);
                }
            }
            {
                struct json field4 = json_object_get(field1, "mounting_height_m");
                if (json_exists(field4))
                {
                    config->radar_mount_config.mounting_height_m = (float)json_double(field4);
                }
            }
        }
    }
    {
        struct json field5 = json_get(json_str, "fov");
        if (json_exists(field5))
        {
            {
                struct json field6 = json_object_get(field5, "range_m");
                if (json_exists(field6))
                {
                    {
                        struct json field7 = json_object_get(field6, "min");
                        if (json_exists(field7))
                        {
                            config->fov_config.min_max_ground_range[0] = (float)json_double(field7);
                        }
                    }
                    {
                        struct json field8 = json_object_get(field6, "max");
                        if (json_exists(field8))
                        {
                            config->fov_config.min_max_ground_range[1] = (float)json_double(field8);
                        }
                    }
                }
            }
            {
                struct json field9 = json_object_get(field5, "angle_deg");
                if (json_exists(field9))
                {
                    {
                        struct json field10 = json_object_get(field9, "min");
                        if (json_exists(field10))
                        {
                            config->fov_config.min_max_azimuth[0] = (float)json_double(field10);
                        }
                    }
                    {
                        struct json field11 = json_object_get(field9, "max");
                        if (json_exists(field11))
                        {
                            config->fov_config.min_max_azimuth[1] = (float)json_double(field11);
                        }
                    }
                }
            }
        }
    }
    
    return true;
}
