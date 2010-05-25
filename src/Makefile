CFLAGS = -lGL -lGLU -lGLUT -g -lALUT -lAL -I../linuxlib/include
CC = g++
SRCDIR = src
OUTDIR = linuxbuild
CPPFILES = audio.cpp game_state.cpp menu_state.cpp \
	render_world.cpp texture.cpp
OFILES = $(CPPFILES:.cpp=.o)


default:go
.cpp.o: $(CPPFILES)
	$(CC) -c $< $(CFLAGS)
go: $(OFILES)
	$(CC) $(OFILES) -o ../themazegame