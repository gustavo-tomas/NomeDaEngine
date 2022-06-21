# makefile ta feio kkkkkkkk um dia eu conserto

# Name of the project
TARGET=Run

# Compiler
CC=g++

# Compiler flags
CC_FLAGS=-std=c++11		\
         -lSDL2     	\
         -lSDL2_image	\
         -lSDL2_ttf   	\
         -lSDL2_mixer

# Command used at clean target
RM = rm

run:
	$(CC) src/Main.cpp src/Game.cpp src/State.cpp src/Sprite.cpp src/Music.cpp $(CC_FLAGS) -o $(TARGET)

clean:
	$(RM) $(TARGET)
