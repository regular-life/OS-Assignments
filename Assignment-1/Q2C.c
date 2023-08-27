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
        if(stat(argv[2],&filestat) < 0)
        {
            return 1 ;
        }
        char *last_time = ctime(&filestat.st_mtime) ;
        time_t mtime = filestat.st_mtime;

        char rfc_time[100]; 
        strftime(rfc_time, sizeof(rfc_time), "%a, %d %b %Y %H:%M:%S %z", localtime(&mtime));
        if (strcmp(argv[1], "-d") == 0)
        {
            printf("Last modified date and time of %s (STRING format): %s\n", filename, last_time) ;
        }
        else if (strcmp(argv[1], "-R") == 0)
        {
            printf("Last modified date and time of %s (RFC 5322 format): %s\n", filename, rfc_time) ;
        }
        else
        {
            fprintf(stderr, "date : invalid argument\n") ;
        }
    }
}
