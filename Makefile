CPP = g++
OPTS = -I "irrklang/include" -L "/usr/lib" irrklang/bin/linux-gcc-64/libIrrKlang.so -pthread

all:
	$(CPP) wener.cpp -o example -lGL -lGLU -lGLEW -lglut -lSOIL $(OPTS)





clean:
	rm example
