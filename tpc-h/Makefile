# SPDX-License-Identifier: GPL-2.0
#

CFLAGS += -Wall -Wextra -O3 -march=native
LDFLAGS += -lm -ldl -lpthread

all: shell

shell: shell.c sqlite3.c sqlite3.h 
	$(CC) $(CFLAGS) -o shell shell.c sqlite3.c $(LDFLAGS) 

clean:
	$(RM) shell 
