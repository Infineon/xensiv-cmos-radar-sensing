#include "usecase_config_serialize.h"
#include <stdio.h>
#include <string.h>
#include "json.h"

bool ifx_usecase_config_serialize(const ifx_usecase_config* config, char* json_buffer, size_t json_buffer_size)
{
    int offset = 0;
    int ret;
    
    #define APPEND(...) do { \
        ret = snprintf(json_buffer + offset, json_buffer_size - offset, __VA_ARGS__); \
        if (ret < 0 || (size_t)ret >= json_buffer_size - offset) { return false; } \
        offset += ret; \
    } while(0)
    
    APPEND("{");
    APPEND("\"filter_ground_range\":");
    APPEND("{");
    APPEND("\"height_based_exclusion\":");
    APPEND("{");
    APPEND("\"enable\":");
    APPEND("%u", config->filter_ground_range.height_based_exclusion.enable);
    APPEND(",");
    APPEND("\"azi_max\":");
    APPEND("%.6f", config->filter_ground_range.height_based_exclusion.azi_max);
    APPEND(",");
    APPEND("\"azi_min\":");
    APPEND("%.6f", config->filter_ground_range.height_based_exclusion.azi_min);
    APPEND(",");
    APPEND("\"exclude_above\":");
    APPEND("%.6f", config->filter_ground_range.height_based_exclusion.exclude_above);
    APPEND(",");
    APPEND("\"exclude_below\":");
    APPEND("%.6f", config->filter_ground_range.height_based_exclusion.exclude_below);
    APPEND(",");
    APPEND("\"range_limit_m\":");
    APPEND("%.6f", config->filter_ground_range.height_based_exclusion.range_limit_m);
    APPEND(",");
    APPEND("\"ground_range_limit_m\":");
    APPEND("%.6f", config->filter_ground_range.height_based_exclusion.ground_range_limit_m);
    APPEND("}");
    APPEND(",");
    APPEND("\"max_monopulse_ele_angle\":");
    APPEND("%.6f", config->filter_ground_range.max_monopulse_ele_angle);
    APPEND(",");
    APPEND("\"min_monopulse_ele_angle\":");
    APPEND("%.6f", config->filter_ground_range.min_monopulse_ele_angle);
    APPEND(",");
    APPEND("\"max_cylindrical_azi_angle\":");
    APPEND("%.6f", config->filter_ground_range.max_cylindrical_azi_angle);
    APPEND(",");
    APPEND("\"min_cylindrical_azi_angle\":");
    APPEND("%.6f", config->filter_ground_range.min_cylindrical_azi_angle);
    APPEND(",");
    APPEND("\"min_radar_range\":");
    APPEND("%.6f", config->filter_ground_range.min_radar_range);
    APPEND(",");
    APPEND("\"range_combination\":");
    APPEND("{");
    APPEND("\"enabled\":");
    APPEND("%u", config->filter_ground_range.range_combination.enabled);
    APPEND(",");
    APPEND("\"range_min\":");
    APPEND("%.6f", config->filter_ground_range.range_combination.range_min);
    APPEND(",");
    APPEND("\"range_max\":");
    APPEND("%.6f", config->filter_ground_range.range_combination.range_max);
    APPEND(",");
    APPEND("\"h_max\":");
    APPEND("%.6f", config->filter_ground_range.range_combination.h_max);
    APPEND(",");
    APPEND("\"h_min\":");
    APPEND("%.6f", config->filter_ground_range.range_combination.h_min);
    APPEND("}");
    APPEND("}");
    APPEND(",");
    APPEND("\"fov_config\":");
    APPEND("{");
    APPEND("\"min_max_ground_range\":");
    APPEND("[");
    for (int i1 = 0; i1 < 2; i1++)
    {
        if (i1 > 0) { APPEND(","); }
        APPEND("%.6f", config->fov_config.min_max_ground_range[i1]);
    }
    APPEND("]");
    APPEND(",");
    APPEND("\"min_max_azimuth\":");
    APPEND("[");
    for (int i2 = 0; i2 < 2; i2++)
    {
        if (i2 > 0) { APPEND(","); }
        APPEND("%.6f", config->fov_config.min_max_azimuth[i2]);
    }
    APPEND("]");
    APPEND("}");
    APPEND(",");
    APPEND("\"calib_mat\":");
    APPEND("{");
    APPEND("\"E\":");
    APPEND("{\"real\":[");
    for (int r3 = 0; r3 < 3; r3++)
    {
        if (r3 > 0) { APPEND(","); }
        APPEND("[");
        for (int c4 = 0; c4 < 3; c4++)
        {
            int idx = r3 + c4 * 3;
            if (c4 > 0) { APPEND(","); }
            APPEND("%.6f", config->calib_mat.E[idx].re);
        }
        APPEND("]");
    }
    APPEND("],\"imag\":[");
    for (int r3 = 0; r3 < 3; r3++)
    {
        if (r3 > 0) { APPEND(","); }
        APPEND("[");
        for (int c4 = 0; c4 < 3; c4++)
        {
            int idx = r3 + c4 * 3;
            if (c4 > 0) { APPEND(","); }
            APPEND("%.6f", config->calib_mat.E[idx].im);
        }
        APPEND("]");
    }
    APPEND("]}");
    APPEND(",");
    APPEND("\"H\":");
    APPEND("{\"real\":[");
    for (int r5 = 0; r5 < 3; r5++)
    {
        if (r5 > 0) { APPEND(","); }
        APPEND("[");
        for (int c6 = 0; c6 < 3; c6++)
        {
            int idx = r5 + c6 * 3;
            if (c6 > 0) { APPEND(","); }
            APPEND("%.6f", config->calib_mat.H[idx].re);
        }
        APPEND("]");
    }
    APPEND("],\"imag\":[");
    for (int r5 = 0; r5 < 3; r5++)
    {
        if (r5 > 0) { APPEND(","); }
        APPEND("[");
        for (int c6 = 0; c6 < 3; c6++)
        {
            int idx = r5 + c6 * 3;
            if (c6 > 0) { APPEND(","); }
            APPEND("%.6f", config->calib_mat.H[idx].im);
        }
        APPEND("]");
    }
    APPEND("]}");
    APPEND("}");
    APPEND(",");
    APPEND("\"calib_mat_type\":");
    APPEND("%u", config->calib_mat_type);
    APPEND(",");
    APPEND("\"radar_mount_config\":");
    APPEND("{");
    APPEND("\"tilt_angle_deg\":");
    APPEND("%.6f", config->radar_mount_config.tilt_angle_deg);
    APPEND(",");
    APPEND("\"mounting_height_m\":");
    APPEND("%.6f", config->radar_mount_config.mounting_height_m);
    APPEND(",");
    APPEND("\"orientation_tx\":");
    APPEND("%u", config->radar_mount_config.orientation_tx);
    APPEND("}");
    APPEND("}");
    json_buffer[offset] = 0;
    return true;
}

bool ifx_usecase_config_deserialize(const char* json_str, ifx_usecase_config* config)
{
    struct json root = json_parse(json_str);
    if (!json_exists(root))
    {
        return false;
    }
    
    {
        struct json field7 = json_get(json_str, "filter_ground_range");
        if (json_exists(field7))
        {
            {
                struct json field8 = json_object_get(field7, "height_based_exclusion");
                if (json_exists(field8))
                {
                    {
                        struct json field9 = json_object_get(field8, "enable");
                        if (json_exists(field9))
                        {
                            config->filter_ground_range.height_based_exclusion.enable = (unsigned char)json_int(field9);
                        }
                    }
                    {
                        struct json field10 = json_object_get(field8, "azi_max");
                        if (json_exists(field10))
                        {
                            config->filter_ground_range.height_based_exclusion.azi_max = (float)json_double(field10);
                        }
                    }
                    {
                        struct json field11 = json_object_get(field8, "azi_min");
                        if (json_exists(field11))
                        {
                            config->filter_ground_range.height_based_exclusion.azi_min = (float)json_double(field11);
                        }
                    }
                    {
                        struct json field12 = json_object_get(field8, "exclude_above");
                        if (json_exists(field12))
                        {
                            config->filter_ground_range.height_based_exclusion.exclude_above = (float)json_double(field12);
                        }
                    }
                    {
                        struct json field13 = json_object_get(field8, "exclude_below");
                        if (json_exists(field13))
                        {
                            config->filter_ground_range.height_based_exclusion.exclude_below = (float)json_double(field13);
                        }
                    }
                    {
                        struct json field14 = json_object_get(field8, "range_limit_m");
                        if (json_exists(field14))
                        {
                            config->filter_ground_range.height_based_exclusion.range_limit_m = (float)json_double(field14);
                        }
                    }
                    {
                        struct json field15 = json_object_get(field8, "ground_range_limit_m");
                        if (json_exists(field15))
                        {
                            config->filter_ground_range.height_based_exclusion.ground_range_limit_m = (float)json_double(field15);
                        }
                    }
                }
            }
            {
                struct json field16 = json_object_get(field7, "max_monopulse_ele_angle");
                if (json_exists(field16))
                {
                    config->filter_ground_range.max_monopulse_ele_angle = (float)json_double(field16);
                }
            }
            {
                struct json field17 = json_object_get(field7, "min_monopulse_ele_angle");
                if (json_exists(field17))
                {
                    config->filter_ground_range.min_monopulse_ele_angle = (float)json_double(field17);
                }
            }
            {
                struct json field18 = json_object_get(field7, "max_cylindrical_azi_angle");
                if (json_exists(field18))
                {
                    config->filter_ground_range.max_cylindrical_azi_angle = (float)json_double(field18);
                }
            }
            {
                struct json field19 = json_object_get(field7, "min_cylindrical_azi_angle");
                if (json_exists(field19))
                {
                    config->filter_ground_range.min_cylindrical_azi_angle = (float)json_double(field19);
                }
            }
            {
                struct json field20 = json_object_get(field7, "min_radar_range");
                if (json_exists(field20))
                {
                    config->filter_ground_range.min_radar_range = (float)json_double(field20);
                }
            }
            {
                struct json field21 = json_object_get(field7, "range_combination");
                if (json_exists(field21))
                {
                    {
                        struct json field22 = json_object_get(field21, "enabled");
                        if (json_exists(field22))
                        {
                            config->filter_ground_range.range_combination.enabled = (unsigned char)json_int(field22);
                        }
                    }
                    {
                        struct json field23 = json_object_get(field21, "range_min");
                        if (json_exists(field23))
                        {
                            config->filter_ground_range.range_combination.range_min = (float)json_double(field23);
                        }
                    }
                    {
                        struct json field24 = json_object_get(field21, "range_max");
                        if (json_exists(field24))
                        {
                            config->filter_ground_range.range_combination.range_max = (float)json_double(field24);
                        }
                    }
                    {
                        struct json field25 = json_object_get(field21, "h_max");
                        if (json_exists(field25))
                        {
                            config->filter_ground_range.range_combination.h_max = (float)json_double(field25);
                        }
                    }
                    {
                        struct json field26 = json_object_get(field21, "h_min");
                        if (json_exists(field26))
                        {
                            config->filter_ground_range.range_combination.h_min = (float)json_double(field26);
                        }
                    }
                }
            }
        }
    }
    {
        struct json field27 = json_get(json_str, "fov_config");
        if (json_exists(field27))
        {
            {
                struct json field28 = json_object_get(field27, "min_max_ground_range");
                if (json_exists(field28))
                {
                    {
                        for (int i29 = 0; i29 < 2; i29++)
                        {
                            struct json elem30 = json_array_get(field28, i29);
                            if (json_exists(elem30))
                            {
                                config->fov_config.min_max_ground_range[i29] = (float)json_double(elem30);
                            }
                        }
                    }
                }
            }
            {
                struct json field31 = json_object_get(field27, "min_max_azimuth");
                if (json_exists(field31))
                {
                    {
                        for (int i32 = 0; i32 < 2; i32++)
                        {
                            struct json elem33 = json_array_get(field31, i32);
                            if (json_exists(elem33))
                            {
                                config->fov_config.min_max_azimuth[i32] = (float)json_double(elem33);
                            }
                        }
                    }
                }
            }
        }
    }
    {
        struct json field34 = json_get(json_str, "calib_mat");
        if (json_exists(field34))
        {
            {
                struct json field35 = json_object_get(field34, "E");
                if (json_exists(field35))
                {
                    {
                        struct json real_array38 = json_object_get(field35, "real");
                        struct json imag_array39 = json_object_get(field35, "imag");
                        if (json_exists(real_array38) && json_exists(imag_array39))
                        {
                            for (int r36 = 0; r36 < 3; r36++)
                            {
                                struct json real_row40 = json_array_get(real_array38, r36);
                                struct json imag_row41 = json_array_get(imag_array39, r36);
                                if (json_exists(real_row40) && json_exists(imag_row41))
                                {
                                    for (int c37 = 0; c37 < 3; c37++)
                                    {
                                        int idx = r36 + c37 * 3;
                                        struct json real_val42 = json_array_get(real_row40, c37);
                                        struct json imag_val43 = json_array_get(imag_row41, c37);
                                        if (json_exists(real_val42) && json_exists(imag_val43))
                                        {
                                            config->calib_mat.E[idx].re = (real32_T)json_double(real_val42);
                                            config->calib_mat.E[idx].im = (real32_T)json_double(imag_val43);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            {
                struct json field44 = json_object_get(field34, "H");
                if (json_exists(field44))
                {
                    {
                        struct json real_array47 = json_object_get(field44, "real");
                        struct json imag_array48 = json_object_get(field44, "imag");
                        if (json_exists(real_array47) && json_exists(imag_array48))
                        {
                            for (int r45 = 0; r45 < 3; r45++)
                            {
                                struct json real_row49 = json_array_get(real_array47, r45);
                                struct json imag_row50 = json_array_get(imag_array48, r45);
                                if (json_exists(real_row49) && json_exists(imag_row50))
                                {
                                    for (int c46 = 0; c46 < 3; c46++)
                                    {
                                        int idx = r45 + c46 * 3;
                                        struct json real_val51 = json_array_get(real_row49, c46);
                                        struct json imag_val52 = json_array_get(imag_row50, c46);
                                        if (json_exists(real_val51) && json_exists(imag_val52))
                                        {
                                            config->calib_mat.H[idx].re = (real32_T)json_double(real_val51);
                                            config->calib_mat.H[idx].im = (real32_T)json_double(imag_val52);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    {
        struct json field53 = json_get(json_str, "calib_mat_type");
        if (json_exists(field53))
        {
            config->calib_mat_type = (unsigned int)json_int(field53);
        }
    }
    {
        struct json field54 = json_get(json_str, "radar_mount_config");
        if (json_exists(field54))
        {
            {
                struct json field55 = json_object_get(field54, "tilt_angle_deg");
                if (json_exists(field55))
                {
                    config->radar_mount_config.tilt_angle_deg = (float)json_double(field55);
                }
            }
            {
                struct json field56 = json_object_get(field54, "mounting_height_m");
                if (json_exists(field56))
                {
                    config->radar_mount_config.mounting_height_m = (float)json_double(field56);
                }
            }
            {
                struct json field57 = json_object_get(field54, "orientation_tx");
                if (json_exists(field57))
                {
                    config->radar_mount_config.orientation_tx = (unsigned int)json_int(field57);
                }
            }
        }
    }
    
    return true;
}
