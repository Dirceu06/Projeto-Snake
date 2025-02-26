# Compilador e flags
CC = gcc
CFLAGS =
LDFLAGS =

# Diretorios e arquivos
SRC = src/main.c 
# HEADERS = include/funcaux.h include/filechange.h include/game.h include/interface.h
OBJ = $(SRC:.c=.o)
EXECUTAVEL = snake

# Detectar sistema operacional
ifeq ($(OS),Windows_NT)
	CFLAGS += -Wall -Wextra -O2 -g -Iinclude -Iraylib/include
	LDFLAGS += -Lraylib/libwin -lraylib -lgdi32 -lwinmm
	EXECUTAVEL := snake.exe
	RUN_CMD = $(EXECUTAVEL)
	RM = cmd /C "del /f /q src\*.o"
	RM_EXECUTAVEL = cmd /C del /f /q $(EXECUTAVEL)
else
	CFLAGS = -Wall -Wextra -O2 -Iinclude -Iraylib/include -m64
	LDFLAGS = -Lraylib/lib -lraylib -lm -lpthread -ldl -lrt -lX11
	RUN_CMD = ./$(EXECUTAVEL)
	RM = rm -f $(OBJ)
	RM_EXECUTAVEL = rm -f $(EXECUTAVEL)
endif

# Regras
all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)

clean_all: clean
	$(RM_EXECUTAVEL)

run: $(EXECUTAVEL)
	$(RUN_CMD)
