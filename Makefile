# Austin Van Braeckel
# 2019-11-10
# Makefile for CIS1300 Assignment 4 - Conway's Game of Life

# CC and its flags
CC = gcc
CFLAGS = -ansi -Wall

# Main

cgol: cgol.o deadOrAlive.o
	$(CC) $(CFLAGS) -o cgol cgol.o deadOrAlive.o

cgol.o: cgol.c
	$(CC) $(CFLAGS) -c cgol.c

# Dynamic Version

dynCGOL: dynCGOL.o deadOrAlive.o
	$(CC) $(CFLAGS) -o dynCGOL dynCGOL.o deadOrAlive.o

dynCGOL.o: dynCGOL.c
	$(CC) $(CFLAGS) -c dynCGOL.c

# Function(s)

deadOrAlive.o: deadOrAlive.c
	$(CC) $(CFLAGS) -c deadOrAlive.c

# All

all: cgol.o dynCGOL.o deadOrAlive.o
	$(CC) $(CFLAGS) -o cgol cgol.o deadOrAlive.o
	$(CC) $(CFLAGS) -o dynCGOL dynCGOL.o deadOrAlive.o

# Clean

clean:
	rm *.o cgol dynCGOL
