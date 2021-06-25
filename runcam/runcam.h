#ifndef RUNCAM_H
#define RUNCAM_H

#include <stdlib.h>
#include <stdint.h>

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

// return type
typedef enum {
    RC_SUCCESS,
    RC_FAILURE,
    RC_NEED_DATA,
    RC_BAD_DATA
} RcRetType;


// USER NEEDS TO SET THIS //
// function pointer to be set by the host
// should write 'data' out to the UART of the RunCam
// assumed returns number of bytes written or -1 on error
extern int (*rc_write)(unsigned char* data, size_t len);

// USER NEEDS TO CALL THIS //
// the user should call this function with every byte
// the host receives from the runcam UART
// not fast or efficient but it's like 6 bytes
void rc_recv_byte(uint8_t byte);

/********* USER FUNCTIONS *********/

// sends an info request to the RunCam
// call before calling rc_check_feature
// returns RC_SUCCESS on success, RC_FAILURE on failure
RcRetType rc_get_info();

// check if a feature is present
// returns RC_SUCCESS on success, RC_NEED_DATA if not enough data has been read,
// or RC_BAD_DATA if the data is incorrect
// sets present to 1 if the feature is present, 0 otherwise
RcRetType rc_check_feature(rc_feature_t feature, unsigned char* present);

// execute a command
RcRetType rc_exec_cmd(rc_action_t cmd);

// TODO settings, text, and handshake

#endif
