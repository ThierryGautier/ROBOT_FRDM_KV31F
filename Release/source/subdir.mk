################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/CalPosition.c \
../source/com.c \
../source/filter.c \
../source/hdlc.c \
../source/lpuart.c \
../source/main_freertos_two_tasks.c \
../source/motors.c \
../source/semihost_hardfault.c \
../source/uart.c 

OBJS += \
./source/CalPosition.o \
./source/com.o \
./source/filter.o \
./source/hdlc.o \
./source/lpuart.o \
./source/main_freertos_two_tasks.o \
./source/motors.o \
./source/semihost_hardfault.o \
./source/uart.o 

C_DEPS += \
./source/CalPosition.d \
./source/com.d \
./source/filter.d \
./source/hdlc.d \
./source/lpuart.d \
./source/main_freertos_two_tasks.d \
./source/motors.d \
./source/semihost_hardfault.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKV31F512VLL12 -DCPU_MKV31F512VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\include" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\serial_manager" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers\freertos" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\device" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\board" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\uart" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\utilities" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\source" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\lists" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\include" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS_driver" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\serial_manager" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\CMSIS" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\drivers\freertos" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\device" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\board" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\uart" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\utilities" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\source" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F\component\lists" -I"D:\THIERRY\workspace\ROBOT_FRDM_KV31F" -Os -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


