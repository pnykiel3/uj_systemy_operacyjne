DIR = `basename $(CURDIR)`

EXEC1 = a
EXEC2 = b
EXEC3 = c
EXEC4 = d
EXEC5 = e

OBJS1 = a.o
OBJS2 = b.o
OBJS3 = c.o
OBJS4 = d.o
OBJS5 = e.o

COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(COFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC5): $(OBJS5)
	$(LD) -o $@ $(LDFLAGS) $^


.PHONY: clean
clean:
	rm -f *.o $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
