# Makefile of Radio
CC = cc
CP = cp
RM = rm

CFLAGS = -lm \
	-I ./include \
	-I ./lib

RADIO_VPATH = . \
	include \
	lib \
	maker \
	player
	
.PHONY: all radiomaker radioplayer clean

radiomaker: radiomaker.o crc32.o radio.o 
	$(CC) $(CFLAGS) -o $@ $^
radioplayer: main.o crc32.o radio.o
	$(CC) $(CFLAGS) -o $@ $^
all: radiomaker radioplayer
	echo "build all"
clean:
	$(RM) -rvf *.exe *.o *.out

%.o: %.c
	$(CC) $(CFLAGS) -c $<

vpath %.h $(RADIO_VPATH)
vpath %.c $(RADIO_VPATH)

