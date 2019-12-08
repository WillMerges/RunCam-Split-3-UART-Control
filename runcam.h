#ifndef RUNCAM
#define RUNCAM

#include <sys/types.h>
#include <stdint.h>

#ifndef RUNCAM_S
struct response_info_s {};
struct request_info_s {};
struct request_control_s {};
struct response_handshake_s {};
#endif

#define HEADER 0xCC

// device info
#define RCDEVICE_PROTOCOL_COMMAND_GET_DEVICE_INFO 0x00
typedef union {
    struct response_info_s response;
    uint8_t as_bytes[sizeof(struct response_info_s)];
} response_info;

typedef union {
    struct request_info_s request;
    uint8_t as_bytes[sizeof(struct request_info_s)];
} request_info;

// camera control
#define RCDEVICE_PROTOCOL_COMMAND_CAMERA_CONTROL 0x01
typedef union {
    struct request_control_s request;
    char as_bytes[sizeof(struct request_control_s)];
} request_control;

// handshake
#define RCDEVICE_PROTOCOL_COMMAND_5KEY_CONNECTION 0x04
#define RCDEVICE_PROTOCOL_5KEY_FUNCTION_OPEN 0x01
#define RCDEVICE_PROTOCOL_5KEY_FUNCTION_CLOSE 0x02
//control and handshake have same request structure
typedef request_control request_handshake;

typedef union {
    struct response_handshake_s response;
    char as_bytes[(sizeof(struct response_handshake_s))];
} response_handshake;

// functions
response_info* get_device_info();

#endif
