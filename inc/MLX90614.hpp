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

  enum units
  {
    CELSIUS = 0,
    FAHRENHEIT = 1,
    KELVIN = 2,
  };

  class MLX90614
  {
    public:
      MLX90614(uint8_t addr);
      ~MLX90614();
      
      float get_ambient_temp(enum units unit);
      
      float get_obj1_temp(enum units unit);
      float get_obj2_temp(enum units unit);
      
      float get_temp_max(enum units unit);
      int8_t set_temp_max(float value, enum units unit);

      float get_temp_min(enum units unit);
      int8_t set_temp_min(float value, enum units unit);

      double get_emissivity();
      int8_t set_emissivity(double value);

      uint8_t get_smbus_addr();
      int8_t set_smbus_addr(uint8_t value);

      bool is_eep_busy();
      bool is_eep_dead();
      bool is_init();

    private:
      static uint8_t raddr, waddr;
      static float t_amb, t_obj1, t_obj2, t_o_min, t_o_max;
      static double emissivity;
      float get_temp_from_k(float temp_k, enum units unit);
      float get_k_from_temp(float value, enum units unit);
      void eep_write(uint8_t addr, uint16_t value);
  };
}

#endif // MLX90614_H