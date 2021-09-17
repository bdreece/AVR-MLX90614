/**
 * main.cpp
 *
 * @author Brian Reece
 * @date 09/16/2021
 */

#ifndef MLX90614_H
#include "MLX90614.hpp"
#endif

using namespace mlx90614;

int main()
{
  MLX90614 sensor = MLX90614();

  float val = sensor.get_ambient_temp_c();
  val = val + 1.0;

  return 0;
}