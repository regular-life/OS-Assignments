// ASSUMPTION : Pass argument of string within '..' for -d flag, e.g, date -d '2 days ago' d is valid but date -d 2 days ago d is not valid
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
#include <time.h>

signed main(int argc, char *argv[])
{
    char *filename = NULL;
    if (argc != 2 && argc != 3 && argc != 4)
    {
        fprintf(stderr, "Usage: date [-option] [file_name]\n");
        exit(EXIT_FAILURE);
    }
    else if (argc == 2)
    {
        filename = argv[1];
        struct stat filestat;
        if (stat(argv[1], &filestat) < 0)
        {
            fprintf(stderr, "date: cannot extract required data. Please check if the file exists.\n");
            return 1;
        }
        char *last_time = ctime(&filestat.st_mtime);
        time_t mtime = filestat.st_mtime;

        char rfc_time[100];
        strftime(rfc_time, sizeof(rfc_time), "%a, %d %b %Y %H:%M:%S %z", localtime(&mtime));
        printf("%s\n", rfc_time);
    }
    else if (argc == 3 && strcmp(argv[1], "-R") == 0)
    {
        filename = argv[2];
        struct stat filestat;
        if (stat(argv[2], &filestat) < 0)
        {
            fprintf(stderr, "date: cannot extract required data. Please check if the file exists.\n");
            return 1;
        }
        char *last_time = ctime(&filestat.st_mtime);
        time_t mtime = filestat.st_mtime;

        char rfc_time[100];
        strftime(rfc_time, sizeof(rfc_time), "%a, %d %b %Y %H:%M:%S %z", localtime(&mtime));
        printf("%s\n", rfc_time);
    }
    else if (argc == 4 && strcmp(argv[1], "-d") == 0)
    {
        char *str = NULL;
        str = argv[2];
        filename = argv[3];
        struct stat filestat;
        if (stat(argv[3], &filestat) < 0)
        {
            fprintf(stderr, "date: cannot extract required data. Please check if the file exists.\n");
            return 1;
        }
        char *last_time = ctime(&filestat.st_mtime);
        time_t mtime = filestat.st_mtime;

        char rfc_time[100];
        strftime(rfc_time, sizeof(rfc_time), "%a, %d %b %Y %H:%M:%S %z", localtime(&mtime));

        struct tm tm_info;
        if (strptime(last_time, "%a %b %d %H:%M:%S %Y", &tm_info) == NULL)
        {
            fprintf(stderr, "date: Error parsing date string\n");
            return 1;
        }

        if (strcmp(argv[2], "yesterday") == 0)
        {
            tm_info.tm_mday--;
        }
        else if (strcmp(argv[2], "tomorrow") == 0)
        {
            tm_info.tm_mday++;
        }
        else if (strstr(argv[2], "days") != NULL)
        {
            int days;
            if (sscanf(argv[2], "%d days ago", &days) == 1)
            {
                tm_info.tm_mday -= days;
            }
            else if (sscanf(argv[2], "%d days later", &days) == 1)
            {
                tm_info.tm_mday += days;
            }
        }
        else if (strstr(argv[2], "hours") != NULL)
        {
            int hours;
            if (sscanf(argv[2], "%d hours ago", &hours) == 1)
            {
                tm_info.tm_hour -= hours;
            }
            else if (sscanf(argv[2], "%d hours later", &hours) == 1)
            {
                tm_info.tm_hour += hours;
            }
        }
        else if (strstr(argv[2], "minutes") != NULL)
        {
            int minutes;
            if (sscanf(argv[2], "%d minutes ago", &minutes) == 1)
            {
                tm_info.tm_min -= minutes;
            }
            else if (sscanf(argv[2], "%d minutes later", &minutes) == 1)
            {
                tm_info.tm_min += minutes;
            }
        }
        else
        {
            fprintf(stderr, "Usage: date [-option] [file_name]\n");
            return 1;
        }

        time_t adjusted_time = mktime(&tm_info);
        if (adjusted_time == -1)
        {
            fprintf(stderr, "date : Error converting adjusted time\n");
            return 1;
        }

        char adjusted_time_str[100];
        strftime(adjusted_time_str, sizeof(adjusted_time_str), "%a %b %d %H:%M:%S %Y", localtime(&adjusted_time));

        printf("%s\n", adjusted_time_str);
    }
    else
    {
        fprintf(stderr, "Usage: date [-option] [file_name]\n");
        return 1;
    }
}
