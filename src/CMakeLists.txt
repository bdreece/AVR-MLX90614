add_avr_library(mlx90614 MLX90614.cpp)
avr_target_include_directories(mlx90614 PUBLIC ../inc ../lib/avr-twi)
avr_target_link_libraries(mlx90614 twi)
