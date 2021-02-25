.PHONY: all install template compile run clean

all: template compile run
	@-

install:
	@chmod +x install_pyctemp.sh
	./install_pyctemp.sh

template:
	pyctemp --source-dirpath app --target-dirpath include --typedef-include uint8_t:inttypes.h

compile:
	@mkdir -p bin
	gcc -ggdb -Wall -Wextra -pedantic -I include include/*.c app/*.c -o bin/path_main -lm

run:
	./bin/path_main

clean:
	rm -rf bin
	rm -rf include