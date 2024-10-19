DIR = `basename $(CURDIR)`
########################################
 LIB1 = funkcje
 EXEC1 = 7a
 EXEC2 = producent
 EXEC3 = konsument
########################################
 EXECS = $(EXEC1) $(EXEC2) $(EXEC3)
########################################
 OBJS1 = $(EXEC1).o
 OBJS2 = $(EXEC2).o
 OBJS3 = $(EXEC3).o
########################################
LIBS1 = $(LIB1).c
########################################
 COFLAGS = -Wall -O
 LDFLAGS = -Wall -O
 CO = gcc
 LD = $(CO)
########################################
 %.o: %.c
	$(CO) $(COFLAGS) -c $<
########################################
 .PHONY: all
 all: $(EXECS)
########################################
 $(EXEC1): $(OBJS1) $(LIBS1)
	 $(LD) -o $@ $(LDFLAGS) $^
########################################
 $(EXEC2): $(OBJS2) $(LIBS1)
	 $(LD) -o $@ $(LDFLAGS) $^
 ########################################
  $(EXEC3): $(OBJS3) $(LIBS1)
	 $(LD) -o $@ $(LDFLAGS) $^
 ########################################
.PHONY: run
run: $(EXECS)
	./$(EXEC1) input
	@diff -s input output
########################################
 .PHONY: clean
 clean:
	rm -f *.o  *~ $(EXECS)
########################################
 .PHONY: tar
 tar: clean
	(cd ../; tar -cvzf "$(DIR)".tar.gz  "$(DIR)" )
########################################