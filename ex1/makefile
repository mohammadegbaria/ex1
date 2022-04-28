CC =gcc
OBJS =RLEList.o ./tool/AsciiArtTool.o ./tool/main.o
EXEC =AsciiArtTool
DEBUG_FLAG =
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

RLEList.o : RLEList.c ~mtm/public/2122b/ex1/RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

AsciiArtTool.o: ./tool/AsciiArtTool.c ./tool/AsciiArtTool.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tool/$*.c

main.o: ./tool/main.c ./tool/AsciiArtTool.h ~mtm/public/2122b/ex1/RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) ./tool/$*.c
clean:
	rm -f $(OBJS) $(EXEC)
