#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_external_command(char *command, char *args)
{
    printf("%s\n", args[0]);
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
    execute_external_command(command, argv + 1);
    if (strncmp(command, "word", 4) == 0)
    {
        execute_external_command(command, argv + 1);
    }
    else if (strcmp(command, "dir") == 0)
    {
        execute_external_command(command, argv + 1);
    }
    else if (strcmp(command, "date") == 0)
    {
        execute_external_command(command, argv + 1);
    }
    else
    {
        printf("Command not Found!\n");
    }

    return 0;
}
