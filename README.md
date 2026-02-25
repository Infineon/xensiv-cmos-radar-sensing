# XENSIV&trade; BGT60CUTRXX radar sensor

This library provides functions to interface with an algorithm for presence detection and tracking (PDT) of multiple targets using the XENSIV&trade; BGT60CUTRXX radar sensor.

Details of algorithm implementation can be found in the [PDT algorithm](docs/html/algo/index.html)


For further information of the radar sensor, please visit the website <https://www.infineon.com/part/BGT60CUTR13AIP>.


## Features

- Process raw radar data from the internal FIFO of the BGT60CUTRXX sensor
- 3 parallel processing chains for macro, micro, and static detection
- Detections are associated accross frames to provide tracking information of the targets


## How to use this library

To use this library in your application:

1. Add the [sensor-xensiv-bgt60cutrxx](https://github.com/Infineon/sensor-xensiv-bgt60cutrxx) driver to your project to interface with the radar sensor hardware.

2. Include this library in your ModusToolbox&trade; project to access the people detection and tracking algorithm.

3. Refer to the [mtb-example-psoc6-cmos-radar-people-tracking](https://github.com/Infineon/mtb-example-psoc6-cmos-radar-people-tracking) code example for a complete implementation demonstrating how to:
   - Configure the BGT60CUTRXX radar sensor
   - Acquire raw radar data
   - Process the data using the PDT algorithm
   - Output tracking results

The code example provides a ready-to-use reference that you can adapt for your specific application requirements.

## Requirements

- [ModusToolbox&trade;](https://www.infineon.com/modustoolbox) v3.4 or later (tested with v3.4)
- Board support package (BSP) minimum required version: 5.0.0
- Programming language: C
- Associated parts: All [PSOC&trade; 6 MCU](https://www.infineon.com/cms/en/product/microcontroller/32-bit-psoc-arm-cortex-microcontroller/psoc-6-32-bit-arm-cortex-m4-mcu) parts
- Radar sensor: [XENSIV&trade; BGT60CUTRXX](https://www.infineon.com/part/BGT60CUTR13AIP) (tested with BGT60CUTR13AIP)


## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v11.3.1 (`GCC_ARM`) – Default value of `TOOLCHAIN`

## More information

* [API reference guide](https://github.com/Infineon/sensor-xensiv-bgt60cutrxx/docs/api_reference_manual.html)
* [Infineon Technologies](https://www.infineon.com)
* [Infineon GitHub](https://github.com/infineon)
* [PSoC&trade; 6 code examples using ModusToolbox&trade;](https://github.com/infineon/Code-Examples-for-ModusToolbox-Software)
* [ModusToolbox&trade; software](https://github.com/Infineon/modustoolbox-software)

<br>

All referenced product or service names and trademarks are the property of their respective owners.

The Bluetooth&reg; word mark and logos are registered trademarks owned by Bluetooth SIG, Inc., and any use of such marks by Infineon is under license.

PSOC&trade;, formerly known as PSoC&trade;, is a trademark of Infineon Technologies. Any references to PSoC&trade; in this document or others shall be deemed to refer to PSOC&trade;.

---------------------------------------------------------

(c) 2025, Infineon Technologies AG, or an affiliate of Infineon Technologies AG. All rights reserved.
This software, associated documentation and materials ("Software") is owned by Infineon Technologies AG or one of its affiliates ("Infineon") and is protected by and subject to worldwide patent protection, worldwide copyright laws, and international treaty provisions. Therefore, you may use this Software only as provided in the license agreement accompanying the software package from which you obtained this Software. If no license agreement applies, then any use, reproduction, modification, translation, or compilation of this Software is prohibited without the express written permission of Infineon.
<br>
Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A SPECIFIC USE/PURPOSE OR MERCHANTABILITY. Infineon reserves the right to make changes to the Software without notice. You are responsible for properly designing, programming, and testing the functionality and safety of your intended application of the Software, as well as complying with any legal requirements related to its use. Infineon does not guarantee that the Software will be free from intrusion, data theft or loss, or other breaches (“Security Breaches”), and Infineon shall have no liability arising out of any Security Breaches. Unless otherwise explicitly approved by Infineon, the Software may not be used in any application where a failure of the Product or any consequences of the use thereof can reasonably be expected to result in personal injury.
