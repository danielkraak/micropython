#include <unistd.h>
#include "py/mpconfig.h"

#include <neorv32.h>

/*
 * Core UART functions to implement for a port
 */

//Receive single character
int mp_hal_stdin_rx_chr(void) {

    unsigned char c = 0;
    // Wait for data to be available
    while (!neorv32_uart0_available()) {}
    c = (char)neorv32_uart0_getc();

    return c;

}



// Send string of given length
mp_uint_t mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {

    mp_uint_t ret = len;

    while (len--) {
        neorv32_uart0_putc(*str++);
    }
    return ret;
}
