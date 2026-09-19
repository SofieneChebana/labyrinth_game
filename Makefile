ifeq ($(OS),Windows_NT)
RM = del /F /Q
RMDIR = rmdir /s /q
MKDIR = mkdir
BIN = bin\labyrinth-game.exe
COPY = xcopy assets bin\assets /E /I /Y && xcopy levels bin\levels /E /I /Y && xcopy lib bin\ /E /I /Y
ASSETS = bin\assets
LEVELS = bin\levels
else
RM = rm -f
RMDIR = rmdir -rf
MKDIR = mkdir -p
BIN = bin/labyrinth-game.exe
COPY = cp -r assets/* bin/assets/ && cp -r levels/* bin/levels/ && cp -r lib/* bin/
ASSETS = bin/assets
LEVELS = bin/levels

endif

CC = gcc
CFLAGS = -I ./src/include/SDL2/
LDFLAGS = -L ./src/lib/ -lSDL2 -lSDL2_mixer

SRC = $(wildcard src/*.c)



.PHONY: all clean

all: $(BIN)

$(BIN):
	$(MKDIR) bin
	$(CC) $(SRC) -o $(BIN) $(CFLAGS) $(LDFLAGS)
	cd bin && $(MKDIR) assets && $(MKDIR) levels
	$(COPY)

clean:
	$(RM) $(BIN)
	$(RMDIR) $(ASSETS)
	$(RMDIR) $(LEVELS)
	$(RMDIR) bin
