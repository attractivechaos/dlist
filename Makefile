EXE=test-intru1

.PHONY:all clean

all:$(EXE)

test-intru1:test-intru1.c dl-intru1.h
	$(CC) -Wall -g -O2 -o $@ $<

clean:
	rm -fr a.out $(EXE) *.dSYM
