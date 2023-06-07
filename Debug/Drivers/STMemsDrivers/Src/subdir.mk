################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STMemsDrivers/Src/lsm6dsox_reg.c 

OBJS += \
./Drivers/STMemsDrivers/Src/lsm6dsox_reg.o 

C_DEPS += \
./Drivers/STMemsDrivers/Src/lsm6dsox_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STMemsDrivers/Src/%.o: ../Drivers/STMemsDrivers/Src/%.c Drivers/STMemsDrivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R9xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/David/STM32CubeIDE/workspace_1.8.0/nvc/Sensors" -I"C:/Users/David/STM32CubeIDE/workspace_1.8.0/nvc/Drivers/STMemsDrivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STMemsDrivers-2f-Src

clean-Drivers-2f-STMemsDrivers-2f-Src:
	-$(RM) ./Drivers/STMemsDrivers/Src/lsm6dsox_reg.d ./Drivers/STMemsDrivers/Src/lsm6dsox_reg.o

.PHONY: clean-Drivers-2f-STMemsDrivers-2f-Src

