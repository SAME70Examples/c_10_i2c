#include "watchdog_same70.h"
#include "sam.h"                        // Device header

void watchdog_disable(void){
    WDT->WDT_CR = WDT_CR_KEY_PASSWD;
    WDT->WDT_MR = WDT_MR_WDDIS;
}
