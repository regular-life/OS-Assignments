all: word dir date

word:
	gcc -o word word.c

dir: 
	gcc -o dir dir.c

date:
	gcc -o date date.c

clean:
	-@rm -f word dir date

#To remove all .txt files in current working directory
remove_txt:
	-@rm -f *.txt

#To remove all directories in current working directory
remove_dirs:
	-@find . -depth -type d ! -name '.' ! -name '..' -exec rm -r {} \;

