################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/freertos/fsl_dspi_freertos.c \
../drivers/freertos/fsl_i2c_freertos.c \
../drivers/freertos/fsl_lpuart_freertos.c \
../drivers/freertos/fsl_uart_freertos.c 

OBJS += \
./drivers/freertos/fsl_dspi_freertos.o \
./drivers/freertos/fsl_i2c_freertos.o \
./drivers/freertos/fsl_lpuart_freertos.o \
./drivers/freertos/fsl_uart_freertos.o 

C_DEPS += \
./drivers/freertos/fsl_dspi_freertos.d \
./drivers/freertos/fsl_i2c_freertos.d \
./drivers/freertos/fsl_lpuart_freertos.d \
./drivers/freertos/fsl_uart_freertos.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/freertos/%.o: ../drivers/freertos/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKV31F512VLL12 -DCPU_MKV31F512VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\include" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\serial_manager" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers\freertos" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\device" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\board" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\uart" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\utilities" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\source" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\lists" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\include" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\serial_manager" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers\freertos" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\device" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\board" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\uart" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\utilities" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\source" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\lists" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F" -Os -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


