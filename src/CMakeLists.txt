add_avr_library(MLX90614 MLX90614.cpp)
avr_target_include_directories(MLX90614 PUBLIC ../inc ../lib/avr-twi)
avr_target_link_libraries(MLX90614 PUBLIC twi)
