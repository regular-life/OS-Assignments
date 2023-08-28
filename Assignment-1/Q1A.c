#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

signed main(int argc, char * argv[])
{
    int child_pid = fork() ;
    int parent_pid = -100 ;
    if (child_pid < 0) { printf("Suck it, This failed. \n") ;}
    else if (child_pid > 0)
    {
        parent_pid = getpid() ;
        printf("Parent (P) is having ID <%d>\n", parent_pid) ;
        int wc = wait(NULL) ;
        printf("ID of P's Child is <%d>\n", child_pid) ;
    }
    else
    {
        child_pid = getpid() ;
        parent_pid = getppid() ;
        printf("Child is having ID <%d>\n", child_pid) ;
        printf("My Parent ID is <%d>\n", parent_pid) ;
    }
}
