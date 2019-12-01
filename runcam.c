#include <stdlib.h>
#include "runcam.h"
#include "ttyUSB.h"

#define INFO_CMD 0x00
#define WRITE_SIZE 3
response_info get_device_info() {
    request_info* req = malloc(sizeof(request_info));
    req->request.header = HEADER;
    req->request.command_id = INFO_CMD;
    req->request.crc8 = 0;

    // printf("%02x ", req->request.header);
    // uint8_t c = 0xCC;
    // printf("%02x", c);

    write_buf(req->as_bytes, WRITE_SIZE);
}
