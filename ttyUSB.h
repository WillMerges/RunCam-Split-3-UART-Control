#ifndef TTY_USB
#define TTY_USB

// response packet is 40 bytes and longest data to be retrieved
#define MAX_BUF_SIZE 40
#define TTY_PORT "/dev/ttyUSB0"

int open_serial_USB();
int write_buf(char* buffer, int n);
int read_buf(char* buffer, int n);
void configure_tty();

#endif
