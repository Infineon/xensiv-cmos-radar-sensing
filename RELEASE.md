# Changelog for Presence Detection and Tracking algorithm library

## Overview

The Presence Detection and Tracking (PDT) library converts raw data from the XENSIV™ 60 GHz CMOS radar sensor into real-time insights on indoor human activity. Because it operates on a frequency spectrum independent of visible light, the system ensures consistent performance in total darkness or low-visibility conditions without requiring optical clarity.

### 1.2.0 (public release)

Update of documentation to include details about the algorithm implementation and link to the documentation.

### 1.0.0 (public release)

This is the initial release of the library to convert raw data from Infineon's cmos radar sensor

#### Add
- **Macro Detection**: Identifies large-scale movements and displacements, such as walking or running
- **Micro Detection**: Detects smaller motions without significant displacement, like hand gestures or posture changes
- **Static Detection**: Captures very subtle movements, including breathing or minor vibrations


#### Change

#### Fixed

#### Improved

## Supported software and tools

This version of the XENSIV™ BGT60CUTRxx 60GHz radar sensor code example was validated for compatibility with the following software and tools:

| Software and tools                        | Version |
| :---                                      | :----:  |
| ModusToolbox™ software environment        | 3.4.0   |
| GCC compiler                              | 10.3.1  |

Minimum required ModusToolbox&trade; software environment: v3.4


© Infineon Technologies AG, 2026.
