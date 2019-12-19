EXE=test-intru1 test-void

.PHONY:all clean

all:$(EXE)

test-intru1:test-intru1.c dl-intru1.h
	$(CC) -Wall -g -O2 -o $@ $<

test-void:test-void.c dl-void.c dl-void.h
	$(CC) -Wall -g -O2 -o $@ test-void.c dl-void.c

clean:
	rm -fr a.out $(EXE) *.dSYM
