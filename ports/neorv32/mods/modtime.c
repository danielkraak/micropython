// This file is never compiled standalone, it's included directly from
// extmod/modtime.c via MICROPY_PY_TIME_INCLUDEFILE.

#include <stdlib.h>

#include <neorv32.h>


void mp_hal_delay_ms(mp_uint_t ms) {
    neorv32_cpu_delay_ms(ms);
}

void mp_hal_delay_us(mp_uint_t us) {
    neorv32_cpu_delay_ms(us>>10); // TODO HACK: Divide by 1024 to roughly get ms.
}

mp_uint_t mp_hal_ticks_ms(void) {

    uint64_t cycle = neorv32_cpu_get_cycle();

    return (uint32_t)cycle / 100000; // TODO HACK: Assumes 100Mhz clock

}


mp_uint_t mp_hal_ticks_us(void) {

    uint64_t cycle = neorv32_cpu_get_cycle();

    return cycle / 100; // TODO HACK: Assumes 100Mhz clock

}


mp_uint_t mp_hal_ticks_cpu(void) {
    return neorv32_cpu_get_cycle();
}