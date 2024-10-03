#include <stdint.h>

// Currently Core Features is the highest level of features I can compile.
#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_CORE_FEATURES)

// EXTRA_FEATURES compiles, but unfortunately, hangs after receiving first input
//#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_EXTRA_FEATURES)
#define MICROPY_ENABLE_COMPILER     (1)

#define MP_SSIZE_MAX (0x7fffffff)

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
#define MICROPY_PY_BUILTINS_SET                 (1)
#define MICROPY_PY_ATTRTUPLE                    (0)
#define MICROPY_PY_COLLECTIONS                  (1)
#define MICROPY_PY_MATH                         (0) // Note: It may be necessary to enable FLOAT_IMPL to use math libs
#define MICROPY_PY_STRUCT                       (1)
#define MICROPY_PY_BINASCII                     (1)
#define MICROPY_PY_RE                           (1)
#define MICROPY_PY_PLATFORM                     (1)

// Machine submodule
#define MICROPY_PY_MACHINE_INCLUDEFILE          "ports/neorv32/mods/modmachine.c"
#define MICROPY_PY_MACHINE                      (1)
#define MICROPY_PY_MACHINE_MEMX                 (1)

// Time submodule
#define MICROPY_PY_TIME_INCLUDEFILE             "ports/neorv32/mods/modtime.c"
#define MICROPY_PY_TIME                         (1)

// Switch these off to make ROM_LEVEL_EXTRA_FEATURES compile,
// Unfortunately, even with these off, the REPL will hang after receiving the first input
#define MICROPY_PY_ASYNCIO          (0)
#define MICROPY_PY_JSON             (0)
#define MICROPY_PY_IO               (0)
#define MICROPY_PY_IO_FILEIO        (0)
#define MICROPY_PY_SYS_STDFILES     (0)

// For some reason cryptolib does not compile..
// It seems to require an SSL library (e.g. MBEDTLS, but I have not been able to include it
// in compilation so far)
#define MICROPY_PY_SSL                        (0)
#define MICROPY_SSL_MBEDTLS                   (0)
#define MICROPY_PY_CRYPTOLIB                  (0)
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
