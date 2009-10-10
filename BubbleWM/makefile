all: Makefile
	mv -f makefile oldmakefile
	make
	mv -f oldmakefile makefile

install: Makefile
	mv -f makefile oldmakefile
	make -f Makefile install
	mv -f oldmakefile makefile

clean: Makefile
	mv -f makefile oldmakefile
	make -f Makefile clean
	mv -f oldmakefile makefile

Makefile:
	./configure


