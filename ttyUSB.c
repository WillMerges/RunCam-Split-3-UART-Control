#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include "ttyUSB.h"

#ifdef DEBUG
#include <stdio.h>
#endif

// global fd
int usb_fd = -1;

// returns fd on success, -1 on fail
// sets global fd in the process
int open_serial_USB() {
    usb_fd = open(TTY_PORT, O_RDWR | O_NOCTTY | O_NDELAY);

    if(usb_fd == -1) {
        perror(TTY_PORT);
    } else {
        fcntl(usb_fd, F_SETFL, O_NDELAY); //FNDELAY makes reading non-blocking
    }
    configure_tty();
    return usb_fd;
}

void configure_tty() {
    if(usb_fd != -1) {
        struct termios opt;
        tcgetattr(usb_fd, &opt);
        cfsetispeed(&opt, B115200); //set baudrate
        cfsetospeed(&opt, B115200);
        opt.c_cflag |= CLOCAL;
        opt.c_cflag |= CREAD;
        tcsetattr(usb_fd, TCSANOW, &opt);
    }
}

// return num bytes written on success, -1 on fail
int write_buf(uint8_t* buffer, size_t n) {
#ifdef DEBUG
    printf("writing: ");
    for(size_t i=0; i < n; i++) {
        printf("0x%02X ", *(buffer+i));
    }
    printf("\n");
#endif
    int ret = write(usb_fd, buffer, n);
    if(ret < 0) {
        perror("error writing to USB serial");
        return -1;
    }
    return ret;
}

// return bytes read on success, -1 otherwise
int read_buf(uint8_t* buffer, size_t n) {
    int ret = read(usb_fd, buffer, n);
    if(ret < 0) {
        perror("error reading from USB serial");
        return -1;
    }
    return ret;
}
