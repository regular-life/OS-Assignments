all:
	gcc Process1.c -o Process1
	gcc Process2.c -o Process2
	gcc Process3.c -o Process3
	gcc Main.c
clean:	
	-@rm Process1
	-@rm Process2
	-@rm Process3
	-@rm a.out
	-@rm file.txt
run:
	-@rm file.txt
	taskset -c 3 ./a.out
