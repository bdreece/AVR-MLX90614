/*! \brief MLX90614 Driver
 *  Header file for the Melexis MLX90614 I2C Driver
 *
 *  \author Brian Reece
 *  \date 09/15/2021
 */

#ifndef MLX90614_H
#define MLX90614_H

#include <stdbool.h>
#include <stdint.h>

namespace mlx90614
{
  struct commands
  { 
    uint8_t CMD_RAM_ACCESS;
    uint8_t CMD_EEP_ACCESS;
    uint8_t CMD_READ_FLAGS;
    uint8_t CMD_SLEEP_MODE;
  };

  struct ram_addrs
  {
    uint8_t RAM_IR_CH_1;
    uint8_t RAM_IR_CH_2;
    uint8_t RAM_T_AMB;
    uint8_t RAM_T_OBJ1;
    uint8_t RAM_T_OBJ2;
  };

  struct eep_addrs
  {
    uint8_t T_O_MAX;
    uint8_t T_O_MIN;
    uint8_t T_A_RANGE;
    uint8_t EMISSIVITY;
    uint8_t CONF_REG_1;
    uint8_t SMBUS_ADDR;
  };

  struct flags
  {
    uint8_t EEBUSY;
    uint8_t EEDEAD;
    uint8_t INIT;
  };

  class MLX90614
  {
    public:
      MLX90614(uint8_t addr);
      ~MLX90614();
      
      float get_ambient_temp_c();
      float get_ambient_temp_f();
      
      float get_obj1_temp_c();
      float get_obj1_temp_f();
      float get_obj2_temp_c();
      float get_obj2_temp_f();
      
      float get_temp_max();
      void set_temp_max(float value);

      float get_temp_min();
      void set_temp_min(float value);

      uint8_t get_smbus_addr();
      void set_smbus_addr(uint8_t value);

      bool is_eep_busy();
      bool is_eep_dead();
      bool is_init();

    private:
      uint8_t addr;
      static const struct commands CMDS;
      static const struct ram_addrs RAM;
      static const struct eep_addrs EEP;
      static const struct flags FLAGS;
      uint16_t read_ram(uint8_t addr);
      uint16_t read_eep(uint8_t addr);
      uint16_t read_flags();
  };
}

#endif // MLX90614_H