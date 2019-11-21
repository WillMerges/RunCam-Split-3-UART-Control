#ifndef RUNCAM
#define RUNCAM

#include <sys/types.h>
#include <stdint.h>

#define HEADER 0xCC

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
    unit8_t crc8;
} request_control;

#define RCDEVICE_PROTOCOL_COMMAND_5KEY_CONNECTION 0x04
typedef struct request_control_t request_handshake; //control and handshake have same request structure
typedef struct response_handshake_s {
    uint8_t header;
    uint8_t action_id_response;
    uint8_t crc8;
} response_handshake;

#endif
