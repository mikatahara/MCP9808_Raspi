/* 
 * Wiringpi_MCP9808.h
 * MCP9808 for using WiringPi
 * by MikataHara 
 * 2024.10.22
*/

#include <wiringPiI2C.h>

#ifndef _WIRINGPI_MCP9808_H
#define _WIRINGPI_MCP9808_H

#define MCP9808_I2CADDR_DEFAULT 0x18    ///< I2C address
#define MCP9808_REG_CONFIG 0x01         ///< MCP9808 config register

#define MCP9808_REG_CONFIG_SHUTDOWN 0x0100   ///< shutdown config
#define MCP9808_REG_CONFIG_CRITLOCKED 0x0080 ///< critical trip lock
#define MCP9808_REG_CONFIG_WINLOCKED 0x0040  ///< alarm window lock
#define MCP9808_REG_CONFIG_INTCLR 0x0020     ///< interrupt clear
#define MCP9808_REG_CONFIG_ALERTSTAT 0x0010  ///< alert output status
#define MCP9808_REG_CONFIG_ALERTCTRL 0x0008  ///< alert output control
#define MCP9808_REG_CONFIG_ALERTSEL 0x0004   ///< alert output select
#define MCP9808_REG_CONFIG_ALERTPOL 0x0002   ///< alert output polarity
#define MCP9808_REG_CONFIG_ALERTMODE 0x0001  ///< alert output mode

#define MCP9808_REG_UPPER_TEMP 0x02   ///< upper alert boundary
#define MCP9808_REG_LOWER_TEMP 0x03   ///< lower alert boundery
#define MCP9808_REG_CRIT_TEMP 0x04    ///< critical temperature
#define MCP9808_REG_AMBIENT_TEMP 0x05 ///< ambient temperature
#define MCP9808_REG_MANUF_ID 0x06     ///< manufacture ID
#define MCP9808_REG_DEVICE_ID 0x07    ///< device ID
#define MCP9808_REG_RESOLUTION 0x08   ///< resolutin

/*  Class for MCP9808 Temp Sensor */
 
#define NAN -1
 
class Wiringpi_MCP9808 {
public:
    Wiringpi_MCP9808(){}
    bool init(uint8_t addr);

    void write16(uint8_t reg, uint16_t val);
    uint16_t read16(uint8_t reg);
    void write8(uint8_t reg, uint8_t val);
    uint8_t read8(uint8_t reg);

    float readTempC();
    void wake_shutdown(bool sw);

private:
    uint8_t _i2caddr;
};

#endif
