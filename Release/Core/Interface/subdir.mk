################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Interface/Interface_Attente.c \
../Core/Interface/Interface_LEDROUGE.c 

OBJS += \
./Core/Interface/Interface_Attente.o \
./Core/Interface/Interface_LEDROUGE.o 

C_DEPS += \
./Core/Interface/Interface_Attente.d \
./Core/Interface/Interface_LEDROUGE.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Interface/%.o Core/Interface/%.su Core/Interface/%.cyclo: ../Core/Interface/%.c Core/Interface/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L031xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Interface

clean-Core-2f-Interface:
	-$(RM) ./Core/Interface/Interface_Attente.cyclo ./Core/Interface/Interface_Attente.d ./Core/Interface/Interface_Attente.o ./Core/Interface/Interface_Attente.su ./Core/Interface/Interface_LEDROUGE.cyclo ./Core/Interface/Interface_LEDROUGE.d ./Core/Interface/Interface_LEDROUGE.o ./Core/Interface/Interface_LEDROUGE.su

.PHONY: clean-Core-2f-Interface

