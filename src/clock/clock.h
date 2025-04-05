#pragma once

typedef enum {
    HSI,
    HSE,
    PLL
} SourceClock;

typedef struct {
    SourceClock source_clock;
} ClockConfiguration;
