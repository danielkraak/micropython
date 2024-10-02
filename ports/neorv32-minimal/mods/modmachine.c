// This file is never compiled standalone, it's included directly from
// extmod/modmachine.c via MICROPY_PY_MACHINE_INCLUDEFILE.

#include <stdlib.h>

static void mp_machine_idle(void) {
    // Do nothing.
}

#if MICROPY_PY_MACHINE_RESET

static void mp_machine_reset(void) {
    // exit(0);
}

static mp_int_t mp_machine_reset_cause(void) {
    // Not implemented.
    return 0;
}

#endif
