#include "runcam.h"
#include "ttyUSB.h"

int initiate_handshake() {
    request_handshake req = malloc(sizeof(request_handshake));
    req.header = HEADER;
    req.command_id = RCDEVICE_PROTOCOL_COMMAND_5KEY_CONNECTION;
    req.action_id = RCDEVICE_PROTOCOL_5KEY_FUNCTION_OPEN;
    
}
