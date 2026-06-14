################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Pilote/PilotePB13.c \
../Core/Pilote/PiloteSwitch1.c \
../Core/Pilote/Pilote_Attente.c 

OBJS += \
./Core/Pilote/PilotePB13.o \
./Core/Pilote/PiloteSwitch1.o \
./Core/Pilote/Pilote_Attente.o 

C_DEPS += \
./Core/Pilote/PilotePB13.d \
./Core/Pilote/PiloteSwitch1.d \
./Core/Pilote/Pilote_Attente.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Pilote/%.o Core/Pilote/%.su Core/Pilote/%.cyclo: ../Core/Pilote/%.c Core/Pilote/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L031xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Pilote

clean-Core-2f-Pilote:
	-$(RM) ./Core/Pilote/PilotePB13.cyclo ./Core/Pilote/PilotePB13.d ./Core/Pilote/PilotePB13.o ./Core/Pilote/PilotePB13.su ./Core/Pilote/PiloteSwitch1.cyclo ./Core/Pilote/PiloteSwitch1.d ./Core/Pilote/PiloteSwitch1.o ./Core/Pilote/PiloteSwitch1.su ./Core/Pilote/Pilote_Attente.cyclo ./Core/Pilote/Pilote_Attente.d ./Core/Pilote/Pilote_Attente.o ./Core/Pilote/Pilote_Attente.su

.PHONY: clean-Core-2f-Pilote

