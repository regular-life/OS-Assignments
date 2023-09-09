all: word dir date

word:
	gcc -o word word.c

dir: 
	gcc -o dir dir.c

date:
	gcc -o date date.c

clean:
	-@rm -f word dir date

#make install to modify shell for commands like word,dir,date.
install:
	echo "alias word='/home/sanyam/Desktop/OS-Assignments-main/Assignment-1/Ques2/word'" >> ~/.bashrc
	echo "alias dir='/home/sanyam/Desktop/OS-Assignments-main/Assignment-1/Ques2/dir'" >> ~/.bashrc
	echo "alias date='/home/sanyam/Desktop/OS-Assignments-main/Assignment-1/Ques2/date'" >> ~/.bashrc

#To remove all .txt files in current working directory
remove_txt:
	-@rm -f *.txt

#To remove all directories in current working directory
remove_dirs:
	-@find . -depth -type d ! -name '.' ! -name '..' -exec rm -r {} \;

