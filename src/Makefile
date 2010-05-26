CFLAGS = -lGL -lGLU -lglut -g -lalut -lopenal -lSOIL -I../linuxlib/include
LFLAGS = -L../linuxlib/libraries
CC = g++
SRCDIR = src
OUTDIR = linuxbuild
CPPFILES = main.cpp audio.cpp game_state.cpp menu_state.cpp \
	render_world.cpp texture.cpp
OFILES = $(CPPFILES:.cpp=.o)


default:go
.cpp.o: $(CPPFILES)
	$(CC) -c $< $(CFLAGS) $(LFLAGS)
go: $(OFILES)
	$(CC) $(OFILES) -o themazegame $(CFLAGS) $(LFLAGS)
