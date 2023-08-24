#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

signed main(int argc, char *argv[])
{
    char *filename = NULL ;
    if (argc != 3)
    {
        fprintf(stderr, "Usage: date [-option] [file_name]\n") ;
        exit(EXIT_FAILURE) ;
    }
    else
    {
        filename = argv[2] ;
        struct stat filestat ;
        if(stat(argv[1],&filestat) < 0)
        {
            return 1 ;
        }
        char *last_time = ctime(&filestat.st_mtime) ;
        struct tm *tm_info = localtime(&filestat.st_mtime) ;

        if (strcmp(argv[1], "-d") == 0)
        {
            char string_buffer[80] ;
            strftime(string_buffer, sizeof(string_buffer), "%a %b %d %H:%M:%S %Y", tm_info) ;
            printf("Last modified date and time of %s (STRING format): %s\n", filename, string_buffer) ;
        }
        else if (strcmp(argv[1], "-R") == 0)
        {
            char rfc5322_buffer[80] ;
            strftime(rfc5322_buffer, sizeof(rfc5322_buffer), "%a, %d %b %Y %H:%M:%S %z", tm_info) ;
            printf("Last modified date and time of %s (RFC 5322 format): %s\n", filename, rfc5322_buffer) ;
        }
        else
        {
            fprintf(stderr, "date : invalid argument\n") ;
        }
    }
}