INSTALL_DIR := $(shell pwd)

all: word dir date

word: word.c
	gcc -o word word.c

dir: dir.c
	gcc -o dir dir.c

date: date.c
	gcc -o date date.c

install: all
	echo "alias word='${INSTALL_DIR}/word'" >> ~/.bashrc
	echo "alias dir='${INSTALL_DIR}/dir'" >> ~/.bashrc
	echo "alias date='${INSTALL_DIR}/date'" >> ~/.bashrc
	echo "Please run source ~/.bashrc to use customized commands"

clean:
	-@rm -f word dir date

#To remove all .txt files in current working directory
remove_txt:
	-@rm -f *.txt

#To remove all directories in current working directory
remove_dirs:
	-@find . -depth -type d ! -name '.' ! -name '..' -exec rm -r {} \;

