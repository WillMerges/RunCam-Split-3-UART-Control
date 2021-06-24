#ifndef RUNCAM_H
#define RUNCAM_H

#include <stdint.h>

#define RC_HEADER 0xCC

// command IDs
// get device info
#define RC_CID_GET_DEVICE_INFO 0x00
// command camera control
#define RC_CID_COMMAND_CAM_CTL 0x01


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
    uint16_t feature;
    uint8_t crc;
} rc_response_info_t;

// device feature masks
// each value represents a one in the nth position of the mask
// e.g. mask = (1 << enum val)
// a one present at that position means the feature is present
typedef enum {
    RC_FT_SIM_POWER,    // simulate power button
    RC_FT_SIM_WIFI,     // simulate wifi button
    RC_FT_CHG_MODE,     // change mode
    RC_FT_SIM_REMOTE,   // simulate 5-key OSD remote
    RC_FT_DEV_SETTINGS, // access to device settings
    RC_FT_DISPLAY_PORT, // DisplayPort device
    RC_FT_START_REC,    // start recording control
    RC_FT_ATTITUDE = 9  // able to request attitude of device
    // for some reason the 8th bit is skipped
} rc_feature_t;


// used for every other action/function command
typedef struct {
    uint8_t header;
    uint8_t command_id;
    uint8_t action_id;
    uint8_t crc;
} rc_request_t;

// camera control actions
typedef enum {
    RC_ACT_WIFI, // simulate click the wifi button
    RC_ACT_POWER, // simulate click the power button
    RC_ACT_CHGMODE, // switch the camera mode
    RC_ACT_START_REC, // start recording
    RC_ACT_STOP_REC, // stop recording
} rc_action_t;

// TODO settings, we can set resolution and draw text


// function pointer to be set by the host
// should write 'data' out to the UART of the RunCam
extern int (*rc_write)(unsigned char* data, size_t len);

// return type
typedef enum {
    RC_SUCCESS,
    RC_FAILURE
} RcRetType;

// TODO we may need to do a handshake?

// USER FUNCTIONS //
// TODO

// I think reading should be handled outside of this module
// buffers passed in after the function is called

#endif
