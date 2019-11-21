#ifndef RUNCAM
#define RUNCAM

#include <sys/types.h>
#include <stdint.h>

#define HEADER 0xCC

// need to add request stuff
#define RCDEVICE_PROTOCOL_COMMAND_GET_DEVICE_INFO 0x00
typedef struct response_info_s {
    uint8_t header;
    uint8_t protocol_version;
    uint16_t feature;
    uint8_t crc8;
} response_info;

#define RCDEVICE_PROTOCOL_COMMAND_CAMERA_CONTROL 0x01
typedef struct request_control_s {
    uint8_t header;
    uint8_t command_id;
    uint8_t action_id;
    uint8_t crc8;
} request_control;

#define RCDEVICE_PROTOCOL_COMMAND_5KEY_CONNECTION 0x04
#define RCDEVICE_PROTOCOL_5KEY_FUNCTION_OPEN 0x01
#define RCDEVICE_PROTOCOL_5KEY_FUNCTION_CLOSE 0x02
typedef struct request_control_t request_handshake; //control and handshake have same request structure
typedef struct response_handshake_s {
    uint8_t header;
    uint8_t action_id_response;
    uint8_t crc8;
} response_handshake;

union serial_packet {
    response_info info;
}

int initiate_handshake()

#endif
