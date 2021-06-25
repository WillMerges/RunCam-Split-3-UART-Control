#include "runcam.h"

#define RC_HEADER 0xCC

// command IDs
// get device info
#define RC_CID_GET_DEVICE_INFO 0x00
// command camera control
#define RC_CID_COMMAND_CAM_CTL 0x01

// dummy write function that always returns error
int dummy_write_func(unsigned char* data, size_t len) {
    // smile and wave boys
    return -1;
}

// function pointer to the write function
// this should change, set to a dummy function to avoic stomping on memory
int (*rc_write)(unsigned char* data, size_t len) = dummy_write_func;

// get device info request
typedef struct {
    uint8_t header;
    uint8_t command_id;
    uint8_t crc;
} rc_request_info_t;

// get device info response
typedef struct {
    uint8_t header;
    uint8_t protocol_version;
    uint16_t features;
    uint8_t crc;
} rc_response_info_t;

// used for every other action/function command
typedef struct {
    uint8_t header;
    uint8_t command_id;
    uint8_t action_id;
    uint8_t crc;
} rc_request_t;

// https://support.runcam.com/hc/en-us/articles/360014537794-RunCam-Device-Protocol
uint8_t crc8_dvb_s2(uint8_t crc, unsigned char a) {
    crc ^= a;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0xD5;
        } else {
            crc = crc << 1;
        }
    }

    return crc;
}

// calculate the CRC8 of a whole buffer
uint8_t crc(uint8_t* data, size_t len) {
    uint8_t crc = 0;
    for(size_t i = 0; i < len; i++) {
        crc = crc8_dvb_s2(crc, data[i]);
    }

    return crc;
}

// TODO maybe have this handle its own receiving? give it a read handler
RcRetType rc_get_info(size_t* requested_bytes) {
    rc_request_info_t rq;
    rq.header = RC_HEADER;
    rq.command_id = RC_CID_GET_DEVICE_INFO;
    rq.crc = crc((uint8_t*)&rq, sizeof(rc_request_info_t) - sizeof(uint8_t));

    if(sizeof(rc_request_info_t) != write((uint8_t*)&rq, sizeof(rc_request_info_t))) {
        return RC_FAILURE;
    }

    return RC_SUCCESS;
}

// feature is the bit index of in the feature word
// e.g. mask = (1 << enum val)
// a one present at that position means the feature is present
RcRetType rc_check_feature(rc_buffer_t response, rc_feature_t feature, bool* present) {
    if(response.len != sizeof(rc_response_info_t)) {
        // size mismatch!
        return RC_BAD_DATA;
    }

    rc_response_info_t* info = (rc_response_info_t*)response;

    if(crc(response.buffer, response.len - sizeof(uint8_t)) != info->crc) {
        return RC_BAD_DATA; // bad CRC
    }

    // TOOD maybe check the header is right, idk
    present = info->features & (1 << feature);

    return RC_SUCCESS;
}
