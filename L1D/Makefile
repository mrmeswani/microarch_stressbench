# COMPILER OPTIONS
EXEC = L1D 
LIBS = -lm
CC = gcc
+DEBUG = 0
+VERBOSE = 0
+CFLAGS = -O3 -g -Wall -DDEBUG=${DEBUG} -DVERBOSE=${VERBOSE}
LDFLAGS=

# DIRS
BUILD = ./build
BIN = ./bin
SRC = .
INC = . 

SRC_FILES = $(wildcard $(SRC)/*.c)
$(info	SRC is  $(SRC_FILES))
HEADERS = $(wildcard $(INC)/*.h)
EXEC_FILES = $(EXEC:%=$(BIN)/%)
$(info	EXEC_FILES is  $(EXEC_FILES))
OBJ_FILES = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRC_FILES))


default: $(EXEC_FILES)
all: default

clean:
	-rm -r -f $(BUILD)
	-rm -r -f $(BIN)

.PHONY: default all clean

$(EXEC_FILES): $(OBJ_FILES)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(LIBS) -o $@ $^
	@echo "Build successful"

$(OBJ_FILES): $(BUILD)/%.o: %.c
	@echo compiling $<
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@
