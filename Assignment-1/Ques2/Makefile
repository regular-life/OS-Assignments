CFLAGS = -Wall -Wextra
INSTALL_DIR := $(shell pwd)

all: word dir date

word: word.c
	gcc $(CFLAGS) -o word word.c

dir: dir.c
	gcc $(CFLAGS) -o dir dir.c

date: date.c
	gcc $(CFLAGS) -o date date.c

install: all
	echo "alias word='${INSTALL_DIR}/word'" >> ~/.bashrc
	echo "alias dir='${INSTALL_DIR}/dir'" >> ~/.bashrc
	echo "alias date='${INSTALL_DIR}/date'" >> ~/.bashrc
	echo "Please run source ~/.bashrc to use customized commands"

clean:
	-@rm -f word dir date
