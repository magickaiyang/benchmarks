CC =		mpicc	
CCFLAGS =	-Wall -Wextra -O2 -g -DCHECK
LINK =		mpicc
LINKFLAGS =	-Wall -Wextra -O2 -g 

.PHONY: all

all: gups_opt ;

clean:
	rm -f gups_opt *.o

# Link target

gups_opt:	gups_opt.o
	$(LINK) $(LINKFLAGS) gups_opt.o -o gups_opt

# Compilation rules

%.o:%.c
	$(CC) $(CCFLAGS) -c $<
