DIR = `basename $(CURDIR)`

EXEC1 = a

EXEC2 = b


OBJS1 = a.o

OBJS2 = b.o


COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(COFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LDFLAGS) $^

.PHONY: clean
clean:
	rm -f *.o $(EXEC1) $(EXEC2)

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
