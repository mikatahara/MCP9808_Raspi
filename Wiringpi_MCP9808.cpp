/* 
 * Wiringpi_MCP9808.cpp
 * Modified for Trinket by MikataHara 
 * 2024.10.19
*/

#include <stdint.h>
#include <stdio.h>
#include "Wiringpi_MCP9808.h"

//#define swapBytes(d)  (((uint16_t)d) >> 8) | ((uint16_t)d << 8));

uint16_t swapBytes(uint16_t num) {
    // LSBとMSBを交換するためにビットシフトを使用
    return ((num&0xFF00) >> 8) | ((num << 8)&0xFF00);
}

/*  Initialize */
bool Wiringpi_MCP9808::init(uint8_t addr) {
    uint16_t manuf_id, device_id;
    _i2caddr = wiringPiI2CSetup (addr);
    fprintf(stderr,"_i2caddr=%d\n",_i2caddr);
    if (_i2caddr > 0){
        manuf_id = read16(MCP9808_REG_MANUF_ID);
        device_id = read16(MCP9808_REG_DEVICE_ID);
        fprintf(stderr,"MCP9808_REG_MANUF_ID=%04x\n",manuf_id);
        fprintf(stderr,"MCP9808_REG_DEVICE_ID=%04x\n",device_id);
        if (manuf_id != 0x0054) return false;
        if (device_id != 0x0400) return false;
        write16(MCP9808_REG_CONFIG, 0x0);
    } else {
        return false;
    }
    return true;
}

void Wiringpi_MCP9808::write8(uint8_t reg, uint8_t val){
    wiringPiI2CWriteReg8 (_i2caddr, reg, val);
}

uint8_t Wiringpi_MCP9808::read8(uint8_t reg){
    uint16_t result =  wiringPiI2CReadReg8 (_i2caddr,reg);
    return result;
}

void Wiringpi_MCP9808::write16(uint8_t reg, uint16_t val){
    wiringPiI2CWriteReg16 (_i2caddr, reg, swapBytes(val));
}

uint16_t Wiringpi_MCP9808::read16(uint8_t reg){
    uint16_t result =  wiringPiI2CReadReg16 (_i2caddr,reg);
    return swapBytes(result);
}

/* Read Temperature */
float Wiringpi_MCP9808::readTempC() {
  float temp = NAN;
  uint16_t t = read16(MCP9808_REG_AMBIENT_TEMP);

  if (t != 0xFFFF) {
    temp = t & 0x0FFF;
    temp /= 16.0;
    if (t & 0x1000)
      temp -= 256;
  }
  return temp;
}

/* Wakeup and Shutdown */
/* true : wake */
/* false : shutdown */

void Wiringpi_MCP9808::wake_shutdown(bool sw) {
  uint16_t conf_shutdown;
  uint16_t conf_register = read16(MCP9808_REG_CONFIG);
  if (sw == true) {
    conf_shutdown = conf_register | MCP9808_REG_CONFIG_SHUTDOWN;
    write16(MCP9808_REG_CONFIG, conf_shutdown);
  }
  else if (sw == false) {
    conf_shutdown = conf_register & ~MCP9808_REG_CONFIG_SHUTDOWN;
    write16(MCP9808_REG_CONFIG, conf_shutdown);
  }
}

