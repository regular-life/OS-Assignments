#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void just_do_it(char *command, char *args)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        execvp(command, args);
        exit(0);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        perror("fork");
    }
}

int main(int argc, char *argv)
{

    char *command = argv[0];
    just_do_it(command, argv + 1);
    if (strncmp(command, "word", 4) == 0)
    {
        just_do_it(command, argv + 1);
    }
    else if (strcmp(command, "dir") == 0)
    {
        just_do_it(command, argv + 1);
    }
    else if (strcmp(command, "date") == 0)
    {
        just_do_it(command, argv + 1);
    }
    else
    {
        printf("Command not Found!\n");
    }

    return 0;
}
