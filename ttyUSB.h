#ifndef TTY_USB
#define TTY_USB

// response packet is 40 bytes and longest data to be retrieved
#define MAX_BUF_SIZE 40

// global file descriptor
int usb_fd = -1

int open_serial_USB();
int write_buf(char* buffer, int n);
int read_buf(char* buffer, int n);

#endif
