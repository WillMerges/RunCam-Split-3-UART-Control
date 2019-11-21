#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include "ttyUSB.h"

// global fd
int usb_fd = -1;

// returns fd on success, -1 on fail
// sets global fd in the process
int open_serial_USB() {
    usb_fd = open(TTY_PORT, O_RDWR | O_NOCTTY | O_NDELAY);

    if(usb_fd == -1) {
        perror(TTY_PORT);
    } else {
        fcntl(usb_fd, F_SETFL, FNDELAY; //FNDELAY makes reading non-blocking
    }
    configure_tty();
    return usb_fd;
}

void configure_tty() {
    if(usb_fd != -1) {
        struct termios opt;
        tcgetattr(usb_fd, &opt);
        cfsetispeed(&opt, B9600); //set baudrate
        cfsetospeed(&opt, B9600);
        opt.c_cflag |= CLOCAL;
        opt.c_cflag |= CREAD;
        tcsetattr(usb_fd, TCSANOW, &opt);
    }
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
