################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Processus/ProcessusAllumage.c \
../Core/Processus/processTestRS485.c 

OBJS += \
./Core/Processus/ProcessusAllumage.o \
./Core/Processus/processTestRS485.o 

C_DEPS += \
./Core/Processus/ProcessusAllumage.d \
./Core/Processus/processTestRS485.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Processus/%.o Core/Processus/%.su Core/Processus/%.cyclo: ../Core/Processus/%.c Core/Processus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L031xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Processus

clean-Core-2f-Processus:
	-$(RM) ./Core/Processus/ProcessusAllumage.cyclo ./Core/Processus/ProcessusAllumage.d ./Core/Processus/ProcessusAllumage.o ./Core/Processus/ProcessusAllumage.su ./Core/Processus/processTestRS485.cyclo ./Core/Processus/processTestRS485.d ./Core/Processus/processTestRS485.o ./Core/Processus/processTestRS485.su

.PHONY: clean-Core-2f-Processus

