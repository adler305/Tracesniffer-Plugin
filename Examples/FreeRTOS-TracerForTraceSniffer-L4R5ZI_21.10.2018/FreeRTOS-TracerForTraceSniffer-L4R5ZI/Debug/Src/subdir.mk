################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/freertos.c \
../Src/main.c \
../Src/selfFIFO.c \
../Src/stm32l4xx_hal_msp.c \
../Src/stm32l4xx_hal_timebase_TIM.c \
../Src/stm32l4xx_it.c \
../Src/stm32l4xx_nucleo_144.c \
../Src/system_stm32l4xx.c 

OBJS += \
./Src/freertos.o \
./Src/main.o \
./Src/selfFIFO.o \
./Src/stm32l4xx_hal_msp.o \
./Src/stm32l4xx_hal_timebase_TIM.o \
./Src/stm32l4xx_it.o \
./Src/stm32l4xx_nucleo_144.o \
./Src/system_stm32l4xx.o 

C_DEPS += \
./Src/freertos.d \
./Src/main.d \
./Src/selfFIFO.d \
./Src/stm32l4xx_hal_msp.d \
./Src/stm32l4xx_hal_timebase_TIM.d \
./Src/stm32l4xx_it.d \
./Src/stm32l4xx_nucleo_144.d \
./Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L4R5xx -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTraceSniffer-L4R5ZI/Inc" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTraceSniffer-L4R5ZI/Tracer" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTraceSniffer-L4R5ZI/Drivers/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTraceSniffer-L4R5ZI/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTraceSniffer-L4R5ZI/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTraceSniffer-L4R5ZI/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTraceSniffer-L4R5ZI/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTraceSniffer-L4R5ZI/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTraceSniffer-L4R5ZI/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


