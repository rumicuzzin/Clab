################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/cfiles/a.c \
../Src/cfiles/b.c \
../Src/cfiles/c.c \
../Src/cfiles/syscalls.c \
../Src/cfiles/sysmem.c 

OBJS += \
./Src/cfiles/a.o \
./Src/cfiles/b.o \
./Src/cfiles/c.o \
./Src/cfiles/syscalls.o \
./Src/cfiles/sysmem.o 

C_DEPS += \
./Src/cfiles/a.d \
./Src/cfiles/b.d \
./Src/cfiles/c.d \
./Src/cfiles/syscalls.d \
./Src/cfiles/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/cfiles/%.o Src/cfiles/%.su Src/cfiles/%.cyclo: ../Src/cfiles/%.c Src/cfiles/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -c -I../Inc -I/Users/willrumi/Desktop/2025_subs/tron_two/MTRX2700-2025/W10-touch-sensor/Drivers/CMSIS/Include -I/Users/willrumi/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.5/Drivers/CMSIS/Device/ST/STM32F3xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-cfiles

clean-Src-2f-cfiles:
	-$(RM) ./Src/cfiles/a.cyclo ./Src/cfiles/a.d ./Src/cfiles/a.o ./Src/cfiles/a.su ./Src/cfiles/b.cyclo ./Src/cfiles/b.d ./Src/cfiles/b.o ./Src/cfiles/b.su ./Src/cfiles/c.cyclo ./Src/cfiles/c.d ./Src/cfiles/c.o ./Src/cfiles/c.su ./Src/cfiles/syscalls.cyclo ./Src/cfiles/syscalls.d ./Src/cfiles/syscalls.o ./Src/cfiles/syscalls.su ./Src/cfiles/sysmem.cyclo ./Src/cfiles/sysmem.d ./Src/cfiles/sysmem.o ./Src/cfiles/sysmem.su

.PHONY: clean-Src-2f-cfiles

