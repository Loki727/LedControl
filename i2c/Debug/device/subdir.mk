################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_LPC55S69_cm33_core0.c 

C_DEPS += \
./device/system_LPC55S69_cm33_core0.d 

OBJS += \
./device/system_LPC55S69_cm33_core0.o 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\MCUX\workspace\i2c\drivers" -I"D:\MCUX\workspace\i2c\device" -I"D:\MCUX\workspace\i2c\CMSIS" -I"D:\MCUX\workspace\i2c\utilities" -I"D:\MCUX\workspace\i2c\component\uart" -I"D:\MCUX\workspace\i2c\component\serial_manager" -I"D:\MCUX\workspace\i2c\component\lists" -I"D:\MCUX\workspace\i2c\board" -I"D:\MCUX\workspace\i2c\startup" -I"D:\MCUX\workspace\i2c\drivers" -I"D:\MCUX\workspace\i2c\device" -I"D:\MCUX\workspace\i2c\CMSIS" -I"D:\MCUX\workspace\i2c\utilities" -I"D:\MCUX\workspace\i2c\component\uart" -I"D:\MCUX\workspace\i2c\component\serial_manager" -I"D:\MCUX\workspace\i2c\component\lists" -I"D:\MCUX\workspace\i2c\board" -I"D:\MCUX\workspace\i2c\startup" -I"D:\MCUX\workspace\i2c\source" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-device

clean-device:
	-$(RM) ./device/system_LPC55S69_cm33_core0.d ./device/system_LPC55S69_cm33_core0.o

.PHONY: clean-device

