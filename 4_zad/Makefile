DIR = `basename $(CURDIR)`

EXEC1 = SO_4

OBJS1 = SO_4.o

COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)


FILEIN = input.txt
FILEOUT = output.txt


%.o: %.c
	$(CO) $(CFLAGS) -c $<
 
run: $(EXEC1)
	./$(EXEC1)
	@diff -s $(FILEIN) $(FILEOUT)  
 
$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^
 
 
EXECS = $(EXEC1)

clean:                                                     
	rm -f *.o  *~ $(EXECS) output.txt

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
