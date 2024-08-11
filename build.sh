#!/bin/bash

COMPILER_PATH=/opt/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi/bin

CC=${COMPILER_PATH}/arm-none-eabi-gcc
LD=${COMPILER_PATH}/arm-none-eabi-ld
OBJDUMP=${COMPILER_PATH}/arm-none-eabi-objdump

${CC} -mcpu=cortex-m4 -mthumb -c -Wall \
      -mfpu=fpv4-sp-d16 \
      -std=gnu11 \
      -g \
      --specs=nano.specs \
      -ffunction-sections \
      -fdata-sections \
      -fstack-usage \
      -mfloat-abi=hard \
      -Wno-implicit-function-declaration \
      startup.c -o startup.o \

${CC} -mcpu=cortex-m4 -mthumb -c -Wall \
      -mfpu=fpv4-sp-d16 \
      -mfloat-abi=hard \
      -g \
      -std=gnu11 \
      --specs=nano.specs \
      -ffunction-sections \
      -fdata-sections \
      -fstack-usage \
      -Wno-implicit-function-declaration \
      main.c -o main.o \

${LD} -T linkscript.ld startup.o main.o -M=info/exec.map -o exec.elf

# ${CC} -o "startup.elf" startup.o main.o -mcpu=cortex-m4 -T linkscript.ld --specs=nosys.specs -Wl,-Map="startup.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

${OBJDUMP} -D exec.elf > info/disassembly
${OBJDUMP} -h exec.elf > info/sections

