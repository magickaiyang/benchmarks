CC =		mpicc	
CCFLAGS =	-I../include -Wall -Wextra -O2 -g -DCHECK

.PHONY: all

all: gups_opt ;

clean:
	rm -f gups_opt *.o

gups_opt:	gups_opt.c
	$(CC) $(CCFLAGS) gups_opt.c -o gups_opt

