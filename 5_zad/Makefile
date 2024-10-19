DIR = `basename $(CURDIR)`

EXEC1 = 5a
EXEC2 = producent
EXEC3 = konsument


OBJS1 = 5a.o
OBJS2 = producent.o
OBJS3 = konsument.o


COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(COFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LDFLAGS) $^

.PHONY: run
run: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC1) producent konsument input output moj_potok
	@diff -s input output

.PHONY: clean
clean:
	rm -f *.o $(EXEC1) $(EXEC2) $(EXEC3)

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))