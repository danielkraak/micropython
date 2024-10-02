#include <stdint.h>


// Currently Core Features is the highest level of features I can compile.
// Bigger feature sets seem to require implementation of more HAL features.
#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_CORE_FEATURES)
//#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_EXTRA_FEATURES)
#define MICROPY_ENABLE_COMPILER     (1)

// Python internal features.
#define MICROPY_ENABLE_GC                       (1)
#define MICROPY_HELPER_REPL                     (1)
#define MICROPY_ERROR_REPORTING                 (MICROPY_ERROR_REPORTING_TERSE)

// Disable floating point. This is necessary when standard library is not linked (-nostdlib)
//#define MICROPY_FLOAT_IMPL                      (MICROPY_FLOAT_IMPL_FLOAT)
#define MICROPY_FLOAT_IMPL                      (0)

// We need LONGINT to support writing to memory addresses using the machine library (they are long apparently)
#define MICROPY_LONGINT_IMPL (MICROPY_LONGINT_IMPL_LONGLONG)

// Fine control over Python builtins, classes, modules, etc.
#define MICROPY_PY_ASYNC_AWAIT                  (0)
#define MICROPY_PY_BUILTINS_SET                 (0)
#define MICROPY_PY_ATTRTUPLE                    (0)
#define MICROPY_PY_COLLECTIONS                  (1)
#define MICROPY_PY_MATH                         (0) // Note: It may be necessary to enable FLOAT_IMPL to use math libs
#define MICROPY_PY_IO                           (0)
#define MICROPY_PY_STRUCT                       (1)
#define MICROPY_PY_BINASCII                     (1)

// Machine submodule
#define MICROPY_PY_MACHINE_INCLUDEFILE          "ports/neorv32-minimal/mods/modmachine.c"
#define MICROPY_PY_MACHINE                      (1)
#define MICROPY_PY_MACHINE_MEMX                 (1)

// For some reason cryptolib does not compile..
#define MICROPY_PY_CRYPTOLIB                    (0)
#define MICROPY_PY_HASHLIB                    (1)
#define MICROPY_PY_HASHLIB256                 (1)

// Type definitions for the specific machine.

typedef intptr_t mp_int_t; // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// We need to provide a declaration/definition of alloca().
#include <alloca.h>

// Define the port's name and hardware.
#define MICROPY_HW_BOARD_NAME "NeoRV32-Board"
#define MICROPY_HW_MCU_NAME   "NeoRV32"

#define MP_STATE_PORT MP_STATE_VM