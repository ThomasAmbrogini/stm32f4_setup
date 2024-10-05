set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(COMPILER_PATH /opt/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi/bin/)
set(COMPILER_PREFIX arm-none-eabi-)

set(STM32F411_OPTIONS -mcpu=cortex-m4
                      -mfpu=fpv4-sp-d16
                      -mthumb
                      -mfloat-abi=hard
                      -nostdlib)

set(CMAKE_C_COMPILER ${COMPILER_PATH}${COMPILER_PREFIX}gcc ${STM32F411_OPTIONS})
set(CMAKE_CXX_COMPILER ${COMPILER_PATH}${COMPILER_PREFIX}g++)

set(CMAKE_C_FLAGS_INIT --specs=nano.specs)

set(CMAKE_LINKER
    ${COMPILER_PREFIX}ld
    CACHE FILEPATH "")
set(CMAKE_GCC_AR
    ${COMPILER_PREFIX}gcc-ar
    CACHE FILEPATH "")
set(CMAKE_GCC_RANLIB
    ${COMPILER_PREFIX}gcc-ranlib
    CACHE FILEPATH "")
set(CMAKE_NM
    ${COMPILER_PREFIX}gcc-nm
    CACHE FILEPATH "")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

