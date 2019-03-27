CC=g++
PKG_CONFIG=`pkg-config --cflags --libs sfml-window sfml-graphics sfml-audio`
STANDARD=-std=c++11
BUILD_DIR=./build/
INCLUDES=-I./includes/
SOURCES=./src/*.cpp
EXENAME=game

make:
	$(CC) $(STANDARD) $(SOURCES) $(INCLUDES) $(PKG_CONFIG) -o $(BUILD_DIR)$(EXENAME)

run:
	$(BUILD_DIR)$(EXENAME)
