#include "watchdog_same70.h"
#include "i2c_same70.h"
#include "mcp4726.h"

int main(){
    watchdog_disable();
    mcp4726_init(2048);
    mcp4726_output(2048);
    while(1){
    }
}
