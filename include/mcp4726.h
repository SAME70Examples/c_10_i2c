#ifndef _MCP4726_H
#define _MCP4726_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void mcp4726_init(uint16_t initial_value);
void mcp4726_output(uint16_t output_value);

#ifdef __cplusplus
}
#endif

#endif /* _MCP4726_H */
