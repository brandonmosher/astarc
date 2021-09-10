BIN=astar_terrain_t

.PHONY: all install template compile run clean

all: template compile run
	@-

install:
	@chmod +x install_pyctemp.sh
	./install_pyctemp.sh

template:
	pyctemp --source-dirpath app/${BIN} --target-dirpath include --include-dirpath app --typedef-include-filepath uint8_t:inttypes.h

compile:
	@mkdir -p bin
	echo "app/${BIN}/*"
	gcc -ggdb -Wall -Wextra -pedantic -I include -I app/${BIN} app/${BIN}/* include/*.c -o bin/${BIN} -lm

run:
	./bin/${BIN}

clean:
	rm -rf bin
	rm -rf include