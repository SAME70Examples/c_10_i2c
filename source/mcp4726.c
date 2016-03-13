#include "mcp4726.h"
#include "i2c_same70.h"

#define MCP4726_ADDRESS (0x62)
#define MCP4726_CMD_WRITE_VOLATILE_MEMORY (0x40)
#define MCP4726_CMD_WRITE_DAC_REGISTER (0x00)

void mcp4726_init(uint16_t initial_value){
    uint8_t data[3] = {MCP4726_CMD_WRITE_VOLATILE_MEMORY,((initial_value >> 4) & 0xFF), ((initial_value << 4) & 0xFF)};
    i2c0_init();
    i2c0_write(MCP4726_ADDRESS, data, 3);
}
void mcp4726_output(uint16_t output_value){
    uint8_t data[2] = {MCP4726_CMD_WRITE_DAC_REGISTER | (output_value >> 8 & 0xF), (output_value & 0xFF)};
    i2c0_write(MCP4726_ADDRESS, data, 2);
}
