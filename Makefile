CFLAGS =  -g  -Ilinuxlib/include
LFLAGS = -Llinuxlib/libraries -lGL -lGLU -lglut -lalut -lopenal -lSOIL
CC = g++
SRCDIR = src
OUTDIR = linuxbuild
CPPFILES = src/main.cpp src/audio.cpp src/game_state.cpp src/menu_state.cpp \
	src/render_world.cpp src/texture.cpp
OFILES = $(CPPFILES:.cpp=.o)

all:go
.cpp.o: $(CPPFILES)
	 $(CC) -c $< $(CFLAGS) $(LFLAGS)
go: $(OFILES)
	mv *.o $(SRCDIR) 	
	$(CC) $(OFILES) -o themazegame $(CFLAGS) $(LFLAGS)
