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
  //! \brief Temperature units
  enum units
  {
    CELSIUS = 0,
    FAHRENHEIT = 1,
    KELVIN = 2,
  };

  //! \brief Class definition for the MLX90614 driver.
  class MLX90614
  {
    public:
      /*! \brief Constructor
       *  \param addr 7-bit TWI address
       */
      MLX90614(uint8_t addr);
      
      //! \brief Destructor
      ~MLX90614();
      
      /*! \brief Get ambient temperature
       *  \param unit Target temperature unit
       *  \return The ambient temperature in the desired units.
       */
      float get_ambient_temp(enum units unit);
      
      /*! \brief Get object 1 temperature
       *  \param unit Target temperature unit
       *  \return The object 1 temperature in the desired units.
       */
      float get_obj1_temp(enum units unit);
      
      /*! \brief Get object 2 temperature
       *  \param unit Target temperature unit
       *  \return The object 2 temperature in the desired units.
       */
      float get_obj2_temp(enum units unit);
      
      /*! \brief Get the maximum specified temperature
       *  \param unit Target temperature unit
       *  \return The maximum specified temperature in the desired units.
       */
      float get_temp_max(enum units unit);
      
      /*! \brief Set the maximum temperature
       *  \param value The new maximum temperature
       *  \param unit Target temperature unit
       *  \return 0 if successful, -1 on error
       */
      int8_t set_temp_max(float value, enum units unit);

      /*! \brief Get the minimum specified temperature
       *  \param unit Target temperature unit
       *  \return The minimum specified temperature in the desired units.
       */ 
      float get_temp_min(enum units unit);
      
      /*! \brief Set the minimum temperature
       *  \param value The new minimum temperature
       *  \return 0 if successful, -1 on error
       */
      int8_t set_temp_min(float value, enum units unit);

      /*! \brief Get the emissivity
       *  \return The emissivity
       */
      double get_emissivity();
      
      /*! \brief Set the emissivity
       *  \param value The new emissivity
       *  \return 0 if successful, -1 on error
       */
      int8_t set_emissivity(double value);

      /*! \brief Get the SMBus (TWI) address
       *  \return The SMBus (TWI) address
       */
      uint8_t get_smbus_addr();
      
      /*! \brief Set the SMBus (TWI) address
       *  \param value The new SMBus (TWI) address
       *  \return 0 if successful, -1 on error
       */
      int8_t set_smbus_addr(uint8_t value);

      /*! \brief Get whether EEPROM is busy
       *  \return True if EEPROM busy
       */
      bool is_eep_busy();
      
      /*! \brief Get whether EEPROM is dead
       *  \return True if EEPROM dead
       */
      bool is_eep_dead();
      
      /*! \brief Get whether MLX90614 is initializing
       *  \return True if initializing, false if done
       */
      bool is_init();

    private:
      static uint8_t raddr, waddr;
      static float t_amb, t_obj1, t_obj2, t_o_min, t_o_max;
      static double emissivity;
      static bool eebusy, eedead, init;
      float get_temp_from_k(float temp_k, enum units unit);
      float get_k_from_temp(float value, enum units unit);
      void eep_write(uint8_t addr, uint16_t value);
      void get_flags();
  };
}

#endif // MLX90614_H