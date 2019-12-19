EXE=test-intru1 test-intru2 test-macro1 test-macro2 test-void

.PHONY:all clean

all:$(EXE)

test-intru1:test-intru1.c dl-intru1.h
	$(CC) -Wall -g -O2 -o $@ $<

test-intru2:test-intru2.c dl-intru2.c dl-intru2.h
	$(CC) -Wall -g -O2 -o $@ test-intru2.c dl-intru2.c

test-macro1:test-macro1.c dl-macro1.h
	$(CC) -Wall -g -O2 -o $@ $<

test-macro2:test-macro2.c dl-macro2.h
	$(CC) -Wall -g -O2 -o $@ $<

test-void:test-void.c dl-void.c dl-void.h
	$(CC) -Wall -g -O2 -o $@ test-void.c dl-void.c

clean:
	rm -fr a.out $(EXE) *.dSYM
