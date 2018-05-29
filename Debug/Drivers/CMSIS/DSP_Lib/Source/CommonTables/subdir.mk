################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.c \
../Drivers/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.c 

OBJS += \
./Drivers/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.o \
./Drivers/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.o 

C_DEPS += \
./Drivers/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.d \
./Drivers/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP_Lib/Source/CommonTables/%.o: ../Drivers/CMSIS/DSP_Lib/Source/CommonTables/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F405xx -DARM_MATH_CM4 -D__FPU_PRESENT=1U -I"C:/Users/Fabio/Documents/Develop/SRM32/workspace/F4_BSP/Inc" -I"C:/Users/Fabio/Documents/Develop/SRM32/workspace/F4_BSP/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Fabio/Documents/Develop/SRM32/workspace/F4_BSP/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Fabio/Documents/Develop/SRM32/workspace/F4_BSP/Drivers/CMSIS/Include" -I"C:/Users/Fabio/Documents/Develop/SRM32/workspace/F4_BSP/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Fabio/Documents/Develop/SRM32/workspace/F4_BSP/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Fabio/Documents/Develop/SRM32/workspace/F4_BSP/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Fabio/Documents/Develop/SRM32/workspace/F4_BSP/" -std=c11 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

