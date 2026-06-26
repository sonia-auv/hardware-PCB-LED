################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Pilote/PilotePB13.c \
../Core/Pilote/PiloteSwitch1.c \
../Core/Pilote/Pilote_Attente.c \
../Core/Pilote/piloteEvenement.c \
../Core/Pilote/piloteMutex.c \
../Core/Pilote/piloteRS485.c \
../Core/Pilote/pilote_thread.c 

OBJS += \
./Core/Pilote/PilotePB13.o \
./Core/Pilote/PiloteSwitch1.o \
./Core/Pilote/Pilote_Attente.o \
./Core/Pilote/piloteEvenement.o \
./Core/Pilote/piloteMutex.o \
./Core/Pilote/piloteRS485.o \
./Core/Pilote/pilote_thread.o 

C_DEPS += \
./Core/Pilote/PilotePB13.d \
./Core/Pilote/PiloteSwitch1.d \
./Core/Pilote/Pilote_Attente.d \
./Core/Pilote/piloteEvenement.d \
./Core/Pilote/piloteMutex.d \
./Core/Pilote/piloteRS485.d \
./Core/Pilote/pilote_thread.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Pilote/%.o Core/Pilote/%.su Core/Pilote/%.cyclo: ../Core/Pilote/%.c Core/Pilote/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L031xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Pilote

clean-Core-2f-Pilote:
	-$(RM) ./Core/Pilote/PilotePB13.cyclo ./Core/Pilote/PilotePB13.d ./Core/Pilote/PilotePB13.o ./Core/Pilote/PilotePB13.su ./Core/Pilote/PiloteSwitch1.cyclo ./Core/Pilote/PiloteSwitch1.d ./Core/Pilote/PiloteSwitch1.o ./Core/Pilote/PiloteSwitch1.su ./Core/Pilote/Pilote_Attente.cyclo ./Core/Pilote/Pilote_Attente.d ./Core/Pilote/Pilote_Attente.o ./Core/Pilote/Pilote_Attente.su ./Core/Pilote/piloteEvenement.cyclo ./Core/Pilote/piloteEvenement.d ./Core/Pilote/piloteEvenement.o ./Core/Pilote/piloteEvenement.su ./Core/Pilote/piloteMutex.cyclo ./Core/Pilote/piloteMutex.d ./Core/Pilote/piloteMutex.o ./Core/Pilote/piloteMutex.su ./Core/Pilote/piloteRS485.cyclo ./Core/Pilote/piloteRS485.d ./Core/Pilote/piloteRS485.o ./Core/Pilote/piloteRS485.su ./Core/Pilote/pilote_thread.cyclo ./Core/Pilote/pilote_thread.d ./Core/Pilote/pilote_thread.o ./Core/Pilote/pilote_thread.su

.PHONY: clean-Core-2f-Pilote

