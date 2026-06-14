################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LibrairieWS/Interface_FctWS.c \
../Core/LibrairieWS/Interface_ws2812b_driver.c 

OBJS += \
./Core/LibrairieWS/Interface_FctWS.o \
./Core/LibrairieWS/Interface_ws2812b_driver.o 

C_DEPS += \
./Core/LibrairieWS/Interface_FctWS.d \
./Core/LibrairieWS/Interface_ws2812b_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LibrairieWS/%.o Core/LibrairieWS/%.su Core/LibrairieWS/%.cyclo: ../Core/LibrairieWS/%.c Core/LibrairieWS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L031xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-LibrairieWS

clean-Core-2f-LibrairieWS:
	-$(RM) ./Core/LibrairieWS/Interface_FctWS.cyclo ./Core/LibrairieWS/Interface_FctWS.d ./Core/LibrairieWS/Interface_FctWS.o ./Core/LibrairieWS/Interface_FctWS.su ./Core/LibrairieWS/Interface_ws2812b_driver.cyclo ./Core/LibrairieWS/Interface_ws2812b_driver.d ./Core/LibrairieWS/Interface_ws2812b_driver.o ./Core/LibrairieWS/Interface_ws2812b_driver.su

.PHONY: clean-Core-2f-LibrairieWS

