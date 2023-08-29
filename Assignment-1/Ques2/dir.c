// ASSUMPTION : Folder name can never start with '-' !!!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <dirent.h>

void remove_directory(const char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            char child_path[1024];
            snprintf(child_path, sizeof(child_path), "%s/%s", path, entry->d_name);

            DIR *child_dir = opendir(child_path);

            if (child_dir)
            {
                closedir(child_dir);
                remove_directory(child_path);
            }
            else
            {
                remove(child_path);
            }
        }
    }

    closedir(dir);
    rmdir(path);
}

signed main(int argc, char *argv[])
{
    if (argc == 2)
    {
        char *dirname = argv[1];
        if (dirname[0] == '-')
        {
            fprintf(stderr, "dir: usage error: cannot start the name of a file with a '- character\n");
            return 1;
        }
        int call = mkdir(dirname, 0777);
        if (call == -1)
        {
            fprintf(stderr, "dir: file already exists\n");
        }
        else
        {
            int change_path = (chdir(dirname));
            if (change_path == -1)
            {
                fprintf(stderr, "dir: file path change error\n");
            }
        }
    }
    else if (argc == 3)
    {
        char *dirname = argv[2];
        int call = mkdir(dirname, 0777);
        if (strcmp(argv[1], "-r") == 0)
        {
            if (call == -1)
            {
                remove_directory(dirname);
                int make_new = mkdir(dirname, 0777);
                if (make_new == -1)
                {
                    fprintf(stderr, "dir: file already exists\n");
                }
                else
                {
                    int change_path = (chdir(dirname));
                    if (change_path == -1)
                    {
                        fprintf(stderr, "dir: file path change error\n");
                    }
                }
            }
        }
        else if (strcmp(argv[1], "-v") == 0)
        {
            if (call == -1)
            {
                fprintf(stderr, "dir: file already exists\n");
            }
            else
            {
                printf("File successfully created\n");
                int change_path = chdir(dirname);
                if (change_path == -1)
                {
                    fprintf(stderr, "dir: file path change error\n");
                }
                else
                {
                    printf("File path successfully changed\n");
                }
            }
        }
        else
        {
            fprintf(stderr, "dir: Usage error: Invalid option\n");
        }
    }
    else
    {
        fprintf(stderr, "dir: Usage error: dir [-option] [dir_name]\n");
    }
}
