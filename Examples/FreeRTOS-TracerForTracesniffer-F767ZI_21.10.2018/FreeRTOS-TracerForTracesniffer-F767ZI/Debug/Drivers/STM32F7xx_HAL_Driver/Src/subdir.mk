################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c 

OBJS += \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.o 

C_DEPS += \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F7xx_HAL_Driver/Src/%.o: ../Drivers/STM32F7xx_HAL_Driver/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Inc" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Tracer" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/JonasPC/Documents/Workspaces/OpenSTM_l4r5zi/FreeRTOS-TracerForTracesniffer-F767ZI/Drivers/CMSIS/Include"  -Og -g3 -ftest-coverage -fprofile-arcs -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


