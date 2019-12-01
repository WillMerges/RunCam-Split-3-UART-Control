#include <stdlib.h>
#include "runcam.h"
#include "ttyUSB.h"

// define static helper func
static uint8_t crc_high_first(uint8_t *ptr, uint8_t len);

// request info from the camera
#define INFO_CMD 0x00
#define WRITE_SIZE_INFO 3
#define READ_SIZE_INFO 5
response_info* get_device_info() {
    request_info* req = malloc(sizeof(request_info));
    req->request.header = HEADER;
    req->request.command_id = INFO_CMD;
    req->request.crc8 = crc_high_first(req->as_bytes, WRITE_SIZE_INFO-1);

    write_buf(req->as_bytes, WRITE_SIZE_INFO);

    response_info* res = malloc(sizeof(response_info));
    read_buf(res->as_bytes, READ_SIZE_INFO);

    return res;
}

// taken from https://azolyoung.gitbooks.io/runcam-split-communication-specification/content/
static uint8_t crc_high_first(uint8_t *ptr, uint8_t len) {
    uint8_t i;
    uint8_t crc = 0x00;
    while (len--) {
        crc ^= *ptr++;
        for (i = 8; i > 0; --i) {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc = (crc << 1);
        }
    }
    return (crc);
}
