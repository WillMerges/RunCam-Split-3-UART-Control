#ifndef RUNCAM
#define RUNCAM

#include <sys/types.h>
#include <stdint.h>

#define HEADER 0xCC

// device info
#define RCDEVICE_PROTOCOL_COMMAND_GET_DEVICE_INFO 0x00
typedef struct response_info_s {
    uint8_t header;
    uint8_t protocol_version;
    uint16_t feature;
    uint8_t crc8;
} response_info;

#pragma pack(1)
struct request_info_s {
    uint8_t header;
    uint8_t command_id;
    uint8_t crc8;
};

typedef union {
    struct request_info_s request;
    uint8_t as_bytes[sizeof(struct request_info_s)];
} request_info;

// camera control
#define RCDEVICE_PROTOCOL_COMMAND_CAMERA_CONTROL 0x01
typedef struct request_control_s {
    uint8_t header;
    uint8_t command_id;
    uint8_t action_id;
    uint8_t crc8;
} request_control;

// handshake
#define RCDEVICE_PROTOCOL_COMMAND_5KEY_CONNECTION 0x04
#define RCDEVICE_PROTOCOL_5KEY_FUNCTION_OPEN 0x01
#define RCDEVICE_PROTOCOL_5KEY_FUNCTION_CLOSE 0x02

typedef struct request_control_s request_handshake; //control and handshake have same request structure

typedef struct response_handshake_s {
    uint8_t header;
    uint8_t action_id_response;
    uint8_t crc8;
} response_handshake;

// functions
response_info get_device_info();

#endif
