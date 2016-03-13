#include "i2c_same70.h"
#include "sam.h"                        // Device header

void i2c0_init(void){
    //PERIPHERAL/FUCTION/PIN/MUX SELECT
    //TWIHS0/TWCK0/PA4/A
    //TWIHS0/TWD0/PA3/A
    
    //PA3 and PA4 Pin configuration
    PMC->PMC_PCER0 = 0x1 << ID_PIOA;//Enable peripheral clock PIOA
    PIOA->PIO_PDR = PIO_PA3 | PIO_PA4;//Disable direct pin control
    PIOA->PIO_ABCDSR[0] &= ~(PIO_PA3 | PIO_PA4);//Select Periphral Mux A
    PIOA->PIO_ABCDSR[1] &= ~(PIO_PA3 | PIO_PA4);//Select Periphral Mux A
    
    PMC->PMC_PCER0 = 0x1 << ID_TWIHS0;//Enable peripheral clock TWIHS0
    TWIHS0->TWIHS_CWGR = TWIHS_CWGR_CKDIV(2) | TWIHS_CWGR_CHDIV(187) | TWIHS_CWGR_CLDIV(187);//Clock configuration 100kHz@150MHz
    TWIHS0->TWIHS_CR = TWIHS_CR_MSEN | TWIHS_CR_SVDIS;//Enable master mode
}

void i2c0_write(uint8_t address_7b, uint8_t *pData, int data_length){
    TWIHS0->TWIHS_MMR = TWIHS_MMR_DADR(address_7b) | TWIHS_MMR_IADRSZ_NONE;
    for(int i = 0; i < data_length; i++){
        TWIHS0->TWIHS_THR = pData[i];
        while(!(TWIHS0->TWIHS_SR & TWIHS_SR_TXRDY));//wait until tx ready
    }
    TWIHS0->TWIHS_CR = TWIHS_CR_STOP;
    while(!(TWIHS0->TWIHS_SR & TWIHS_SR_TXCOMP));//wait until tx complete
}

void i2c0_write_at(uint8_t address_7b, uint8_t internal_address, uint8_t *pData, int data_length){
    TWIHS0->TWIHS_MMR = TWIHS_MMR_DADR(address_7b) | TWIHS_MMR_IADRSZ_1_BYTE;
    TWIHS0->TWIHS_IADR = internal_address;
    for(int i = 0; i < data_length; i++){
        TWIHS0->TWIHS_THR = pData[i];
        while(!(TWIHS0->TWIHS_SR & TWIHS_SR_TXRDY));//wait until tx ready
    }
    TWIHS0->TWIHS_CR = TWIHS_CR_STOP;
    while(!(TWIHS0->TWIHS_SR & TWIHS_SR_TXCOMP));//wait until tx complete
}

void i2c0_read_at(uint8_t address_7b, uint8_t internal_address, uint8_t *pData, int data_length){
    TWIHS0->TWIHS_MMR = TWIHS_MMR_DADR(address_7b) | TWIHS_MMR_IADRSZ_1_BYTE | TWIHS_MMR_MREAD;
    TWIHS0->TWIHS_IADR = internal_address;
    
    TWIHS0->TWIHS_CR = (data_length > 1) ? TWIHS_CR_START : TWIHS_CR_START | TWIHS_CR_STOP;
    
    //read all but last byte
    for(int i = 0; i < (data_length - 1); i++){
        while(!(TWIHS0->TWIHS_SR & TWIHS_SR_RXRDY));//wait until rx ready
        pData[i] = TWIHS0->TWIHS_RHR;
    }
    
    //Generate stop and read last byte
    if(data_length > 1) TWIHS0->TWIHS_CR = TWIHS_CR_STOP;
    
    while(!(TWIHS0->TWIHS_SR & TWIHS_SR_RXRDY));//wait until rx ready
    pData[data_length - 1] = TWIHS0->TWIHS_RHR;
    
    while(!(TWIHS0->TWIHS_SR & TWIHS_SR_TXCOMP));//wait until rx complete
}
