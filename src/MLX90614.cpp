/**
 * MLX90614.cpp - Implementation of the MLX90614 driver
 *
 * @author Brian Reece
 * @date 09/16/2021
 */

#include <stddef.h>
#include <math.h>

#ifndef MLX90614_H
#include "MLX90614.hpp"
#endif

#ifndef TWI_H
#include "twi.h"
#endif

/***** STATIC VARIABLES *****/
static uint8_t CMD_READ_FLAGS = 0xF0;
static uint8_t CMD_SLEEP_MODE = 0xFF;
static uint8_t RAM_IR_CH_1 =    0x04;
static uint8_t RAM_IR_CH_2 =    0x05;
static uint8_t RAM_T_AMB =      0x06;
static uint8_t RAM_T_OBJ1 =     0x07;
static uint8_t RAM_T_OBJ2 =     0x08;
static uint8_t EEP_T_O_MAX =    0x10;
static uint8_t EEP_T_O_MIN =    0x11;
static uint8_t EEP_T_A_RANGE =  0x13;
static uint8_t EEP_EMISSIVITY = 0x14;
static uint8_t EEP_CONF_REG_1 = 0x15;
static uint8_t EEP_SMBUS_ADDR = 0x1E;
static uint8_t FLAG_EEBUSY =    0x80;
static uint8_t FLAG_EEDEAD =    0x20;
static uint8_t FLAG_INIT =      0x10;
uint8_t mlx90614::MLX90614::raddr;
uint8_t mlx90614::MLX90614::waddr;
float mlx90614::MLX90614::t_amb;
float mlx90614::MLX90614::t_obj1;
float mlx90614::MLX90614::t_obj2;
float mlx90614::MLX90614::t_o_min;
float mlx90614::MLX90614::t_o_max;
double mlx90614::MLX90614::emissivity;
bool mlx90614::MLX90614::eebusy;
bool mlx90614::MLX90614::eedead;
bool mlx90614::MLX90614::init;


/***** PUBLIC METHODS *****/

mlx90614::MLX90614::MLX90614(uint8_t addr)
{
  mlx90614::MLX90614::raddr = (addr << 1) | 1;
  mlx90614::MLX90614::waddr = addr << 1;
  twi_init();
}

mlx90614::MLX90614::~MLX90614()
{
  mlx90614::MLX90614::raddr = 0;
  mlx90614::MLX90614::waddr = 0;
}

float mlx90614::MLX90614::get_ambient_temp(enum mlx90614::units unit)
{
  // Send command to read from T_a address in RAM
  twi_write(waddr, &RAM_T_AMB, 1, NULL);
  twi_wait();

  // Read value into buffer as floating point Kelvin
  twi_read(raddr, 3, [](uint8_t addr, uint8_t *data)
  {
    mlx90614::MLX90614::t_amb = (float)(*data | *(data + 1) << 7) / 50; 
  });

  // Convert to desired unit  
  return get_temp_from_k(t_amb, unit);
}

float mlx90614::MLX90614::get_obj1_temp(enum mlx90614::units unit)
{
  // Send command to read from T_obj1 address in RAM
  twi_write(waddr, &RAM_T_OBJ1, 1, NULL);
  twi_wait();

  // Read value into buffer as floating point Kelvin
  twi_read(raddr, 3, [](uint8_t addr, uint8_t *data)
  {
    mlx90614::MLX90614::t_obj1 = (float)(*data | *(data + 1) << 7) / 50;
  });

  // Convert to desired unit
  return get_temp_from_k(t_obj1, unit);
}

float mlx90614::MLX90614::get_obj2_temp(enum mlx90614::units unit)
{
  // Send command to read from T_obj2 address in RAM
  twi_write(waddr, &RAM_T_OBJ2, 1, NULL);
  twi_wait();

  // Read value into buffer as floating point Kelvin
  twi_read(raddr, 3, [](uint8_t addr, uint8_t *data)
  {
    mlx90614::MLX90614::t_obj2 = (float)(*data | *(data + 1) << 7) / 50;
  });

  // Convert to desired unit
  return get_temp_from_k(t_obj2, unit);
}

float mlx90614::MLX90614::get_temp_max(enum mlx90614::units unit)
{
  // Send command to read from T_O_max address in EEPROM
  twi_write(waddr, &EEP_T_O_MAX, 1, NULL);
  twi_wait();

  // Read value into buffer as floating point Kelvin
  twi_read(raddr, 3, [](uint8_t addr, uint8_t *data)
  {
    mlx90614::MLX90614::t_o_max = (float)(*data | *(data + 1) << 7) / 100;
  });

  // Convert to desired unit
  return get_temp_from_k(t_o_max, unit);
}

int8_t mlx90614::MLX90614::set_temp_max(float value, enum mlx90614::units unit)
{
  value = get_k_from_temp(value, unit);

  if (value < 0.0 || value > 109.05)
    return -1;

  eep_write(EEP_T_O_MAX, (uint16_t)(value * 100));
  return 0;
}

float mlx90614::MLX90614::get_temp_min(enum mlx90614::units unit)
{
  // Send command to read from T_O_min address in EEPROM
  twi_write(waddr, &EEP_T_O_MIN, 1, NULL);
  twi_wait();

  // Read value into buffer as floating point Kelvin
  twi_read(raddr, 3, [](uint8_t addr, uint8_t *data)
  {
    mlx90614::MLX90614::t_o_min = (float)(*data | *(data + 1) << 7) / 100;
  });

  // Convert to desired unit
  return get_temp_from_k(t_o_min, unit);
} 

int8_t mlx90614::MLX90614::set_temp_min(float value, enum mlx90614::units unit)
{
  value = get_k_from_temp(value, unit);

  if (value < 0.0 || value > 109.05)
    return -1;

  eep_write(EEP_T_O_MIN, (uint16_t)(value * 100));
  return 0;
}

double mlx90614::MLX90614::get_emissivity()
{
  // Send command to read from EMISSIVITY address in EEPROM
  twi_write(waddr, &EEP_EMISSIVITY, 1, NULL);
  twi_wait();

  twi_read(raddr, 3, [](uint8_t addr, uint8_t *data)
  {
    mlx90614::MLX90614::emissivity = (double)(*data | *(data + 1) << 7) / 65535;
  });

  return emissivity;
}

int8_t mlx90614::MLX90614::set_emissivity(double value)
{
  if (value < 0.0 || value > 1.0)
    return -1;

  uint16_t e = (uint16_t)round(value * 65535);
  eep_write(EEP_EMISSIVITY, e);
  return 0;
}

uint8_t mlx90614::MLX90614::get_smbus_addr()
{
  // Send command to read SMBUS_ADDR address from EEPROM
  twi_write(waddr, &EEP_SMBUS_ADDR, 1, NULL);
  twi_wait();

  // Read value into raddr and wadder as uint8_t
  twi_read(raddr, 3, [](uint8_t addr, uint8_t *data)
  {
    mlx90614::MLX90614::waddr = *data << 1;
    mlx90614::MLX90614::raddr = (*data << 1) | 1;
  });

  return mlx90614::MLX90614::waddr >> 1;
}
int8_t mlx90614::MLX90614::set_smbus_addr(uint8_t value)
{
  // Greatest possible 7-bit TWI address
  if (value > 0x7F)
    return -1;

  eep_write(EEP_SMBUS_ADDR, (uint16_t)value);
  return 0;
}

bool mlx90614::MLX90614::is_eep_busy()
{
  get_flags();
  return mlx90614::MLX90614::eebusy;
}

bool mlx90614::MLX90614::is_eep_dead()
{
  get_flags();
  return mlx90614::MLX90614::eedead;
}

bool mlx90614::MLX90614::is_init()
{
  get_flags();
  return mlx90614::MLX90614::init;
}

/***** PRIVATE METHODS *****/

float mlx90614::MLX90614::get_temp_from_k(float temp_k, enum mlx90614::units unit)
{
  if (unit == mlx90614::CELSIUS)
    return temp_k - 273.15;
  else if (unit == mlx90614::FAHRENHEIT)
    return (temp_k * 1.8) - 459.67;
  else // unit == mlx90614::KELVIN
    return temp_k;
}

float mlx90614::MLX90614::get_k_from_temp(float value, enum mlx90614::units unit)
{
  if (unit == mlx90614::CELSIUS)
    return value + 273.15;
  else if (unit == mlx90614::FAHRENHEIT)
    return (value + 459.67) / 1.8;
  else // unit == mlx90614::KELVIN
    return value;
}

void mlx90614::MLX90614::eep_write(uint8_t addr, uint16_t value)
{
  uint8_t zeros[2] = { 0x00, 0x00 };
  uint8_t data[2] = { value & 0x00FF, value >> 7 };

  twi_write(waddr, &addr, 1, NULL);
  twi_wait();
  twi_write(waddr, zeros, 2, NULL);
  twi_wait();
  twi_write(waddr, data, 2, NULL);
  twi_wait();
}

void mlx90614::MLX90614::get_flags()
{
  // Send command to read flags
  twi_write(waddr, &CMD_READ_FLAGS, 1, NULL);
  twi_wait();

  // Read value into buffers as booleans.
  twi_read(raddr, 3, [](uint8_t addr, uint8_t *data)
  {
    uint16_t raw = *data | *(data + 1) << 7;
    mlx90614::MLX90614::eebusy = raw & FLAG_EEBUSY != 0;
    mlx90614::MLX90614::eedead = raw & FLAG_EEDEAD != 0;
    mlx90614::MLX90614::init   = raw & FLAG_INIT   != 0;
  });
}