# Makefile for Linux

SHELL = /bin/sh

# System-specific settings

CC =		mpicc	
CCFLAGS =	-O -g -DCHECK
LINK =		mpicc
LINKFLAGS =	-O -g 

.PHONY: all

all: gups_opt ;

clean:
	rm -f gups_vanilla gups_nonpow2 gups_opt *.o

# Link target

gups_vanilla:	gups_vanilla.o
	$(LINK) $(LINKFLAGS) gups_vanilla.o -o gups_vanilla

gups_nonpow2:	gups_nonpow2.o
	$(LINK) $(LINKFLAGS) gups_nonpow2.o -o gups_nonpow2

gups_opt:	gups_opt.o
	$(LINK) $(LINKFLAGS) gups_opt.o -o gups_opt

# Compilation rules

%.o:%.c
	$(CC) $(CCFLAGS) -c $<
