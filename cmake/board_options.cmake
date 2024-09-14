set(BOARD_OPTIONS -mcpu=cortex-m4
                  -mfpu=fpv4-sp-d16 
                  -mthumb
                  -mfloat-abi=hard 
                  -nostdlib
                  --specs=nano.specs
                  -O0
)

