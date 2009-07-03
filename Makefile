PROGS = zelda_ph word_sum
LIBS =

CC = gcc
CFLAGS = -Wall -W -Os
LDFLAGS =

OBJS = $(patsubst %,%.o,$(PROGS))

all: $(PROGS)

$(PROGS): %: %.o $(COMMON) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(COMMON) $(LIBS) -o $@

$(OBJS): %.o: %.c Makefile
	$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@

clean:
	-rm -f $(OBJS) $(PROGS)
