# ROBOT_FRDM_KV31F
ROBOT_FRDM_KV31F is composed with:
- mother board FRDM-KV31F 
  see https://www.nxp.com/design/development-boards/freedom-development-boards/mcu-boards/freedom-development-platform-for-kinetis-kv3x-family-mcus:FRDM-KV31F
- sheild FRDM_FXS_MULTI_B (NXP
  see https://www.nxp.com/design/development-boards/freedom-development-boards/sensors/freedom-development-platform-for-nxp-sensors-with-bluetooth-:FRDM-FXS-MULT2-B
- sheild FRDM-MC-LVBLDC (NXP)
  see https://www.nxp.com/design/development-boards/freedom-development-boards/mcu-boards/nxp-freedom-development-platform-for-low-voltage-3-phase-bldc-motor-control:FRDM-MC-LVBLDC
  
All boards can be found in NXP https://www.nxp.com

This system is in charge to:
- to control two LEGO DC motor in charge to move the ROBOT
- to measure accelaration, speed and orientation with gyroscope, accerometer and magnetometer 
- to communicate through bluetooth to mointor measures with NXP Sensor Fusion Toolbox
- to communicate to linux board (odroid-N2) with lpuart device at 500 Khz in real time ( fram rate = 50 Hz)  
- to drive RGB led (status of the board)
- to measure temperature
- to mesure pressure
- to check power supply of the battery (not operational)

This part is developped in C with MCUXpresso IDE with merge of FRDM-KV31 package (SDK_2.6.0_FRDM-KV31F) and (SDK_2.9.0_FRDM-K64F-MULT2B.zip)

The Software development kit SDK_2.6.0_FRDM-KV31F is used to develop embedded software with RTOS with add RTOS drivers required for this project.
The Software development kit SDK_2.9.0_FRDM-K64F-MULT2B.zip is used to get Sensor fusion librairy and bluetooth functionnality

Migration in progress to SDK_2.10 for both
