################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Service/serviceRS485.c 

OBJS += \
./Core/Service/serviceRS485.o 

C_DEPS += \
./Core/Service/serviceRS485.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Service/%.o Core/Service/%.su Core/Service/%.cyclo: ../Core/Service/%.c Core/Service/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L031xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Service

clean-Core-2f-Service:
	-$(RM) ./Core/Service/serviceRS485.cyclo ./Core/Service/serviceRS485.d ./Core/Service/serviceRS485.o ./Core/Service/serviceRS485.su

.PHONY: clean-Core-2f-Service

