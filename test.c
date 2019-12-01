#include <stdlib.h>
#include "ttyUSB.h"
#include "runcam.h"

int main() {
    open_serial_USB();
    get_device_info();
}
