CC		= gcc
CFLAGS		= -I $(INC_DIR)
LIBS		= -lbcm2835 -lshiftr

INC_DIR 	= include
SRC_DIR		= src
OBJ_DIR 	= obj

PREFIX		= /usr/local

_DEPS		= eerawr.h
DEPS		= $(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJ		= main.o util.o read.o write.o
OBJ		= $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

all: eerawr

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

eerawr: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

install: eerawr clean
	mkdir -p $(PREFIX)/bin
	cp eerawr $(PREFIX)/bin/eerawr
	chmod +x $(PREFIX)/bin/eerawr

uninstall:
	rm -f $(PREFIX)/bin/eerawr

clean:
	rm -f $(OBJ_DIR)/*.o 

.PHONY: clean install uninstall
