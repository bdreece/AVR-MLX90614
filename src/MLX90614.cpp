/**
 * MLX90614.cpp - Implementation of the MLX90614 driver
 *
 * @author Brian Reece
 * @date 09/16/2021
 */

#ifndef MLX90614_H
#include "MLX90614.hpp"
#endif

using namespace mlx90614;

/***** STATIC STRUCTS *****/

const struct commands MLX90614::CMDS = {
  .CMD_RAM_ACCESS = 0x00,
  .CMD_EEP_ACCESS = 0x10,
  .CMD_READ_FLAGS = 0xF0,
  .CMD_SLEEP_MODE = 0xFF,
};

const struct ram_addrs MLX90614::RAM = {
  .RAM_IR_CH_1    = 0x04,
  .RAM_IR_CH_2    = 0x05,
  .RAM_T_AMB      = 0x06,
  .RAM_T_OBJ1     = 0x07,
  .RAM_T_OBJ2     = 0x08,
};

const struct eep_addrs MLX90614::EEP = {
  .T_O_MAX        = 0x00,
  .T_O_MIN        = 0x01,
  .T_A_RANGE      = 0x03,
  .EMISSIVITY     = 0x04,
  .CONF_REG_1     = 0x05,
  .SMBUS_ADDR     = 0x0E,
};

const struct flags MLX90614::FLAGS = {
  .EEBUSY         = 0x80,
  .EEDEAD         = 0x20,
  .INIT           = 0x10,
};

/***** PUBLIC METHODS *****/

MLX90614::MLX90614(uint8_t addr)
{
  this->addr = addr;
  
}

MLX90614::~MLX90614()
{

}

float MLX90614::get_ambient_temp_c()
{
  return 0.0;
}

float MLX90614::get_ambient_temp_f()
{
  return 0.0;
}

float MLX90614::get_obj1_temp_c()
{
  return 0.0;
}

float MLX90614::get_obj1_temp_f()
{
  return 0.0;
}

float MLX90614::get_obj2_temp_c()
{
  return 0.0;
}

float MLX90614::get_obj2_temp_f()
{
  return 0.0;
}

float MLX90614::get_temp_max()
{
  return 0.0;
}

void MLX90614::set_temp_max(float value)
{

}

float MLX90614::get_temp_min()
{
  return 0.0;
} 

void MLX90614::set_temp_min(float value)
{

}

uint8_t MLX90614::get_smbus_addr()
{
  return 0;
}

void MLX90614::set_smbus_addr(uint8_t value)
{

}

bool MLX90614::is_eep_busy()
{
  return false;
}

bool MLX90614::is_eep_dead()
{
  return false;
}

bool MLX90614::is_init()
{
  return false;
}

/***** PRIVATE METHODS *****/

uint16_t MLX90614::read_ram(uint8_t addr)
{
  return 0;
}

uint16_t MLX90614::read_eep(uint8_t addr)
{
  return 0;
}

uint16_t MLX90614::read_flags()
{
  return 0;
}