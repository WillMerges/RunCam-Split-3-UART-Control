#include <stdlib.h>
#include "ttyUSB.h"

// info response struct
#pragma pack(1)
struct response_info_s {
    uint8_t header;
    uint8_t protocol_version;
    uint16_t feature;
    uint8_t crc8;
};

// info request struct
#pragma pack(1)
struct request_info_s {
    uint8_t header;
    uint8_t command_id;
    uint8_t crc8;
};

// control request struct
#pragma pack(1)
struct request_control_s {
    uint8_t header;
    uint8_t command_id;
    uint8_t action_id;
    uint8_t crc8;
};

// handshake response struct
#pragma pack(1)
struct response_handshake_s {
    uint8_t header;
    uint8_t action_id_response;
    uint8_t crc8;
};

#define RUNCAM_S
#include "runcam.h"

// define static helper func
static uint8_t crc_high_first(uint8_t *ptr, uint8_t len);

// request info from the camera
// returns response or NULL if error reading
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
    if(read_buf(res->as_bytes, READ_SIZE_INFO) == -1) {
        fprintf(stderr, "No bytes read from device\n");
        return NULL;
    }

    uint8_t crc8 = crc_high_first(res->as_bytes, READ_SIZE_INFO - 1);
    if(crc8 == res->respose.crc8) {
            return res;
    } else {
        fprintf(stderr, "CRC8 did not match:\ncalculated: %i\ndevice: %i\n", crc8, res->response.crc8);
        return NULL;
    }

}

// modified to work with uint8_t types
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
