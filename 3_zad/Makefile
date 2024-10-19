DIR = `basename $(CURDIR)`

EXEC1 = 3a
EXEC2 = 3b
EXEC3 = 3c
EXEC4 = 3c2


OBJS1 = 3a.o
OBJS2 = 3b.o
OBJS3 = 3c.o
OBJS4 = 3c2.o


COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(COFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LDFLAGS) $^
	
$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LDFLAGS) $^
	
$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LDFLAGS) $^

.PHONY: clean
clean:
	rm -f *.o $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
