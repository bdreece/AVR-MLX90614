MMCU 		:= atmega328p

CC			:= avr-g++
FLAGS		:= -Wall -Werror -g -Os
CFLAGS	:= -I./inc
MFLAGS	:= -mmcu=$(MMCU)
LFLAGS	:= -L./lib -lMLX90614

AR			:= avr-ar rcs
OBJCPY	:= avr-objcopy -j .text -j .data -O ihex
OBJS		:= $(patsubst src/%.cpp, %.o, $(wildcard src/*.cpp))

.PHONY: all clean

default: lib/libMLX90614.a clean

all: lib/libMLX90614.a bin/MLX90614_demo.hex clean

%.o: src/%.cpp
	$(CC) $(FLAGS) $(CFLAGS) -c -o $@ $<

lib/libMLX90614.a: $(OBJS)
	mkdir -p lib
	$(AR) $@ $^

bin/MLX90614_demo.hex: lib/libMLX90614.a
	mkdir -p bin/
	$(CC) $(FLAGS) $(CFLAGS) $(MFLAGS) -o bin/main.elf demo/main.cpp $(LFLAGS)
	$(OBJCPY) bin/main.elf $@

clean:
	rm -f *.o bin/main.elf

remove:
	rm -rf bin lib