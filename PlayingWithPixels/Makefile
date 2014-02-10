EXE = testscene
OBJS =testscene.cpp png.o rgbapixel.o image.o scene.o

COMPILER = g++
COMPILER_OPTS = -c -g -O0 -Wall -Werror
LINKER = g++
LINKER_OPTS = -lpng

all : $(EXE)

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) $(LINKER_OPTS) -o $(EXE)

png.o : png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) rgbapixel.cpp
testscene.o : testscene.cpp image.h png.h rgbapixel.h	$(COMPILER) $(COMPILER_OPTS) testscene.cpp
image.o :image.cpp png.h rgbapixel.h image.h
	$(COMPILER) $(COMPILER_OPTS) image.cpp
scene.o: scene.cpp png.h rgbapixel.h image.h scene.h
	$(COMPILER) $(COMPILER_OPTS) scene.cpp
	
clean :
	-rm -f *.o $(EXE)
