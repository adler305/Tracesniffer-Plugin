################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/freertos.c \
../Src/main.c \
../Src/selfFIFO.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_hal_timebase_TIM.c \
../Src/stm32f7xx_it.c \
../Src/stm32f7xx_nucleo_144.c \
../Src/system_stm32f7xx.c 

OBJS += \
./Src/freertos.o \
./Src/main.o \
./Src/selfFIFO.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_hal_timebase_TIM.o \
./Src/stm32f7xx_it.o \
./Src/stm32f7xx_nucleo_144.o \
./Src/system_stm32f7xx.o 

C_DEPS += \
./Src/freertos.d \
./Src/main.d \
./Src/selfFIFO.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_hal_timebase_TIM.d \
./Src/stm32f7xx_it.d \
./Src/stm32f7xx_nucleo_144.d \
./Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Inc" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Tracer" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Drivers/CMSIS/Include"  -Og -g3 -ftest-coverage -fprofile-arcs -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


