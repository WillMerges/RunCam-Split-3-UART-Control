#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include "ttyUSB.h"

// returns fd on success, -1 on fail
// sets global fd in the process
int open_serial_USB() {
    usb_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if(usb_fd == -1) {
        perror("unable to open /dev/ttyUSB0");
    } else {
        fcntl(ubs_fd, F_SETFL, FNDELAY) //FNDELAY makes reading non-blocking
    }
    return usb_fd;
}

// return num bytes written on success, -1 on fail
int write_buf(char* buffer, int n) {
    int ret = write(usb_fd, buffer, n);
    if(ret < 0) {
        perror("error writing to USB serial");
        return -1;
    }
    return ret;
}

// return bytes read on success, -1 otherwise
int read_buf(char* buffer, int n) {
    int ret = read(usb_fd, buffer, n);
    if(ret < 0) {
        perror("error reading from USB serial");
        return -1;
    }
    return ret;
}
