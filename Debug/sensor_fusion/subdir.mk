################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sensor_fusion/DecodeCommandBytes.c \
../sensor_fusion/approximations.c \
../sensor_fusion/calibration_storage.c \
../sensor_fusion/control.c \
../sensor_fusion/debug.c \
../sensor_fusion/driver_FXAS21002.c \
../sensor_fusion/driver_FXOS8700.c \
../sensor_fusion/driver_KSDK_NVM.c \
../sensor_fusion/driver_MPL3115.c \
../sensor_fusion/driver_pit.c \
../sensor_fusion/driver_systick.c \
../sensor_fusion/fusion.c \
../sensor_fusion/hal_frdm_fxs_mult2_b.c \
../sensor_fusion/magnetic.c \
../sensor_fusion/matrix.c \
../sensor_fusion/orientation.c \
../sensor_fusion/output_stream.c \
../sensor_fusion/precisionAccelerometer.c \
../sensor_fusion/sensor_fusion.c \
../sensor_fusion/status.c 

OBJS += \
./sensor_fusion/DecodeCommandBytes.o \
./sensor_fusion/approximations.o \
./sensor_fusion/calibration_storage.o \
./sensor_fusion/control.o \
./sensor_fusion/debug.o \
./sensor_fusion/driver_FXAS21002.o \
./sensor_fusion/driver_FXOS8700.o \
./sensor_fusion/driver_KSDK_NVM.o \
./sensor_fusion/driver_MPL3115.o \
./sensor_fusion/driver_pit.o \
./sensor_fusion/driver_systick.o \
./sensor_fusion/fusion.o \
./sensor_fusion/hal_frdm_fxs_mult2_b.o \
./sensor_fusion/magnetic.o \
./sensor_fusion/matrix.o \
./sensor_fusion/orientation.o \
./sensor_fusion/output_stream.o \
./sensor_fusion/precisionAccelerometer.o \
./sensor_fusion/sensor_fusion.o \
./sensor_fusion/status.o 

C_DEPS += \
./sensor_fusion/DecodeCommandBytes.d \
./sensor_fusion/approximations.d \
./sensor_fusion/calibration_storage.d \
./sensor_fusion/control.d \
./sensor_fusion/debug.d \
./sensor_fusion/driver_FXAS21002.d \
./sensor_fusion/driver_FXOS8700.d \
./sensor_fusion/driver_KSDK_NVM.d \
./sensor_fusion/driver_MPL3115.d \
./sensor_fusion/driver_pit.d \
./sensor_fusion/driver_systick.d \
./sensor_fusion/fusion.d \
./sensor_fusion/hal_frdm_fxs_mult2_b.d \
./sensor_fusion/magnetic.d \
./sensor_fusion/matrix.d \
./sensor_fusion/orientation.d \
./sensor_fusion/output_stream.d \
./sensor_fusion/precisionAccelerometer.d \
./sensor_fusion/sensor_fusion.d \
./sensor_fusion/status.d 


# Each subdirectory must supply rules for building sources it contributes
sensor_fusion/%.o: ../sensor_fusion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKV31F512VLL12 -DCPU_MKV31F512VLL12_cm4 -DFRDM_KV31F -DFREEDOM -DPRINTF_ADVANCED_ENABLE -DFSL_RTOS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DPATCH_DRIVER_FSL_FTM -DCOM_HDLC_ENABLE -DUART_TIME_LOG -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\include" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\serial_manager" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers\freertos" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\device" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\board" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\uart" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\utilities" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\source" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\lists" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\include" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\serial_manager" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers\freertos" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\device" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\board" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\uart" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\utilities" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\source" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\lists" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\gpio_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\sensors" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\sensor_fusion" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\interfaces" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


