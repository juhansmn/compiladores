CC = gcc
CCFLAGS = -Wall -Wshadow -O2
LFLAGS = -lm

.PHONY = all clean

example-fact: example_fact.o tinyexpr.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

.c.o:
	$(CC) -c $(CCFLAGS) $< -o $@

clean:
	rm -f *.o *.exe example-fact
