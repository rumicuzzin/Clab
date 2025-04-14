################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/digital_io_c.c \
../Src/main_c.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/digital_io_c.o \
./Src/main_c.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/digital_io_c.d \
./Src/main_c.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -c -I../Inc -I"C:/Users/marcu/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.5/Drivers/CMSIS/Core_A" -I"C:/Users/marcu/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.5/Drivers/CMSIS/Core/Include" -I"C:/Users/marcu/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.5/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/digital_io_c.cyclo ./Src/digital_io_c.d ./Src/digital_io_c.o ./Src/digital_io_c.su ./Src/main_c.cyclo ./Src/main_c.d ./Src/main_c.o ./Src/main_c.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

