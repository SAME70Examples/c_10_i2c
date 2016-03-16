#include "watchdog_same70.h"
#include "i2c_same70.h"
#include "mcp4726.h"


#define HMC5883_ADDRESS (0x1E)
#define HMS5833_REG_MODE (0x02)
#define HMS5833_REG_DATA_X_HIGH (0x03)
#define HMS5833_REG_DATA_X_LOW (0x04)
#define HMS5833_REG_DATA_Z_HIGH (0x05)
#define HMS5833_REG_DATA_Z_LOW (0x06)
#define HMS5833_REG_DATA_Y_HIGH (0x07)
#define HMS5833_REG_DATA_Y_LOW (0x08)


int main(){
    watchdog_disable();
    while(1){
    }
}
