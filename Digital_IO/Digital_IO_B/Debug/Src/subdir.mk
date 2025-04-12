################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/digital_io_b.c \
../Src/main_b.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/digital_io_b.o \
./Src/main_b.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/digital_io_b.d \
./Src/main_b.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -c -I../Inc -I"C:/Users/marcu/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.5/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/marcu/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.5/Drivers/CMSIS/Core/Include" -I"C:/Users/marcu/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.5/Drivers/CMSIS/Core_A" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/digital_io_b.cyclo ./Src/digital_io_b.d ./Src/digital_io_b.o ./Src/digital_io_b.su ./Src/main_b.cyclo ./Src/main_b.d ./Src/main_b.o ./Src/main_b.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

