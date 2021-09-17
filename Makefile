MMCU 		:= atmega328p

CC			:= avr-g++
FLAGS		:= -Wall -g -Os
CFLAGS	:= -I./inc
MFLAGS	:= -D F_CPU=1000000 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -mmcu=$(MMCU)
LFLAGS	:= -L./lib

AR			:= avr-ar ru --target=ihex
OBJCPY	:= avr-objcopy -j .text -j .data -O ihex
OBJS		:= $(patsubst src/%.cpp, %.o, $(wildcard src/*.cpp)) twi.o

.PHONY: all clean

default: lib/libMLX90614.a clean

all: lib/libMLX90614.a bin/MLX90614_demo.hex clean

%.o: src/%.cpp
	$(CC) $(FLAGS) $(CFLAGS) -c -o $@ $< -lm

twi.o: lib/avr-twi/twi.c
	$(CC) $(FLAGS) $(CFLAGS) $(MFLAGS) -c -o $@ $<

lib/libMLX90614.a: $(OBJS)
	mkdir -p lib
	$(AR) $@ $^

bin/MLX90614_demo.hex: lib/libMLX90614.a
	mkdir -p bin/
	$(CC) $(FLAGS) $(CFLAGS) $(MFLAGS) $(LFLAGS) -o bin/main.elf demo/main.cpp -lMLX90614
	$(OBJCPY) bin/main.elf $@

clean:
	rm -f *.o bin/main.elf

remove:
	rm -rf bin lib/libMLX90614.a