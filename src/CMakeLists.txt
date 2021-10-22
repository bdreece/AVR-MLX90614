<<<<<<< HEAD
add_avr_library(mlx90614 MLX90614.cpp)
avr_target_include_directories(mlx90614 PUBLIC ../inc ../lib/avr-twi)
avr_target_link_libraries(mlx90614 twi)
=======
add_avr_library(MLX90614 MLX90614.cpp)
avr_target_include_directories(MLX90614 PUBLIC ../inc ../lib/avr-twi)
avr_target_link_libraries(MLX90614 PUBLIC twi)
>>>>>>> c87d4be6d3cc7c2302930ea336c9252b035ddb47
