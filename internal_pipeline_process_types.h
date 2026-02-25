/*
 * File: internal_pipeline_process_types.h
 *
 * MATLAB Coder version            : 24.2
 */

#ifndef INTERNAL_PIPELINE_PROCESS_TYPES_H
#define INTERNAL_PIPELINE_PROCESS_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct10_T
#define typedef_struct10_T
typedef struct {
  uint8_T confirm_max_count_per_frame;
  uint8_T confirm_bin_count;
  uint8_T confirm_frames_per_bin;
} struct10_T;
#endif /* typedef_struct10_T */

#ifndef typedef_struct9_T
#define typedef_struct9_T
typedef struct {
  real32_T association_range;
  real32_T association_angle;
  real32_T association_distance;
  real32_T update_rate;
  real32_T update_rate_multiple;
  struct10_T confirmConfig;
} struct9_T;
#endif /* typedef_struct9_T */

#ifndef typedef_struct13_T
#define typedef_struct13_T
typedef struct {
  boolean_T enable;
  real32_T azi_max;
  real32_T azi_min;
  real32_T exclude_above;
  real32_T exclude_below;
  real32_T range_limit_m;
  real32_T ground_range_limit_m;
} struct13_T;
#endif /* typedef_struct13_T */

#ifndef typedef_struct14_T
#define typedef_struct14_T
typedef struct {
  boolean_T enabled;
  real32_T range_min;
  real32_T range_max;
  real32_T h_max;
  real32_T h_min;
} struct14_T;
#endif /* typedef_struct14_T */

#ifndef typedef_struct12_T
#define typedef_struct12_T
typedef struct {
  struct13_T height_based_exclusion;
  real32_T max_monopulse_ele_angle;
  real32_T min_monopulse_ele_angle;
  real32_T max_cylindrical_azi_angle;
  real32_T min_cylindrical_azi_angle;
  real32_T min_radar_range;
  struct14_T range_combination;
} struct12_T;
#endif /* typedef_struct12_T */

#ifndef typedef_struct17_T
#define typedef_struct17_T
typedef struct {
  real32_T tilt_angle_deg;
  real32_T mounting_height_m;
  uint32_T orientation_tx;
} struct17_T;
#endif /* typedef_struct17_T */

#ifndef typedef_ifx_track_stats_t
#define typedef_ifx_track_stats_t
typedef struct {
  uint32_T count;
  real32_T power_db;
  real32_T doppler_mps_sum;
  real32_T doppler_mps_sum_square;
  real32_T activity;
} ifx_track_stats_t;
#endif /* typedef_ifx_track_stats_t */

#ifndef typedef_ifx_Detection_t
#define typedef_ifx_Detection_t
typedef struct {
  real32_T range_m;
  real32_T azi_angle_deg;
  real32_T ele_angle_deg;
  real32_T doppler_mps;
  real32_T magnitude_db;
  real32_T num_of_detections;
} ifx_Detection_t;
#endif /* typedef_ifx_Detection_t */

#ifndef typedef_struct15_T
#define typedef_struct15_T
typedef struct {
  real32_T min_max_ground_range[2];
  real32_T min_max_azimuth[2];
} struct15_T;
#endif /* typedef_struct15_T */

#ifndef typedef_ifx_tracks_t
#define typedef_ifx_tracks_t
typedef struct {
  real32_T track_id[12];
  real32_T range_m[12];
  real32_T doppler_mps[12];
  real32_T azi_angle_deg[12];
  real32_T ele_angle_deg[12];
  real32_T velocity_mps[12];
  ifx_track_stats_t stats[12];
} ifx_tracks_t;
#endif /* typedef_ifx_tracks_t */

#ifndef typedef_struct16_T
#define typedef_struct16_T
typedef struct {
  creal32_T E[9];
  creal32_T H[9];
} struct16_T;
#endif /* typedef_struct16_T */

#ifndef typedef_ifx_var_config_t
#define typedef_ifx_var_config_t
typedef struct {
  struct12_T filter_ground_range;
  struct15_T fov_config;
  struct16_T calib_mat;
  uint32_T calib_mat_type;
  struct17_T radar_mount_config;
} ifx_var_config_t;
#endif /* typedef_ifx_var_config_t */

#ifndef typedef_emxArray_ifx_Detection_t_16x2
#define typedef_emxArray_ifx_Detection_t_16x2
typedef struct {
  ifx_Detection_t data[32];
  int32_T size[2];
} emxArray_ifx_Detection_t_16x2;
#endif /* typedef_emxArray_ifx_Detection_t_16x2 */

#ifndef typedef_ifx_result_t
#define typedef_ifx_result_t
typedef struct {
  emxArray_ifx_Detection_t_16x2 cw_macro_detections;
  emxArray_ifx_Detection_t_16x2 cw_micro_detections;
  emxArray_ifx_Detection_t_16x2 cw_static_detections;
  ifx_tracks_t sd_tracks;
  real32_T fov_depth[32];
} ifx_result_t;
#endif /* typedef_ifx_result_t */

#endif
/*
 * File trailer for internal_pipeline_process_types.h
 *
 * [EOF]
 */
