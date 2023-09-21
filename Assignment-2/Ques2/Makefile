all:
	-@gcc Process1.c -o Process1
	-@gcc Process2.c -o Process2
	-@gcc Process3.c -o Process3
	-@gcc Main.c
clean:	
	-@rm -fv Process1
	-@rm -fv Process2
	-@rm -fv Process3
	-@rm -fv a.out 
	-@rm -fv file.txt 
run:
	-@sudo rm -f file.txt
	-@sudo taskset -c 3 ./a.out
