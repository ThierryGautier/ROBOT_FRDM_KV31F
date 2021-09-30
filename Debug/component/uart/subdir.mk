################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/uart_adapter.c 

OBJS += \
./component/uart/uart_adapter.o 

C_DEPS += \
./component/uart/uart_adapter.d 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKV31F512VLL12 -DCPU_MKV31F512VLL12_cm4 -DFRDM_KV31F -DFREEDOM -DPRINTF_ADVANCED_ENABLE -DFSL_RTOS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DPATCH_DRIVER_FSL_FTM -DCOM_HDLC_ENABLE -DUART_TIME_LOG -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\include" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\serial_manager" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers\freertos" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\device" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\board" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\uart" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\utilities" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\source" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\lists" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\include" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\serial_manager" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers\freertos" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\device" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\board" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\uart" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\utilities" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\source" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\lists" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\gpio_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\sensors" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\sensor_fusion" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\interfaces" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


