#ifndef RUNCAM_H
#define RUNCAM_H

#include <stdint.h>

// runcam reading buffer
// data read off of the UART is used as a parameter
typedef struct {
    uint8_t* buffer;
    size_t len;
} rc_buffer_t;

// device features
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

// camera control actions
typedef enum {
    RC_ACT_WIFI, // simulate click the wifi button
    RC_ACT_POWER, // simulate click the power button
    RC_ACT_CHGMODE, // switch the camera mode
    RC_ACT_START_REC, // start recording
    RC_ACT_STOP_REC, // stop recording
} rc_action_t;

// function pointer to be set by the host
// should write 'data' out to the UART of the RunCam
// assumed returns number of bytes written or -1 on error
extern int (*rc_write)(unsigned char* data, size_t len);

// return type
typedef enum {
    RC_SUCCESS,
    RC_FAILURE,
    RC_BAD_DATA
} RcRetType;


/********* USER FUNCTIONS *********/

// sends an info request to the RunCam
// sets 'requested_bytes' to the number of bytes it requests to be read before
// calling rc_check_feature
// returns RC_SUCCESS on success, RC_FAILURE on failure
RcRetType rc_get_info(size_t* requested_bytes);

// check if a feature is present
// rc_request_feature should be called first and the response passed in as 'response'
// returns RC_SUCCESS on succes or RC_BAD_DATA if the 'response' is bad
RcRetType rc_check_feature(rc_buffer_t response, rc_feature_t feature, bool* present);


// TODO settings, text, and handshake

#endif
