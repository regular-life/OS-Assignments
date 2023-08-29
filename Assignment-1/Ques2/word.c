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

signed main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage Error : word [-option] [file_name]\n") ;
        return 1 ;
    }
    else if (argc == 2)
    {
        char *filename = NULL ;
        filename = argv[1] ;
        FILE *file = fopen(filename, "r") ;
        if (! file)
        {
            fprintf(stderr, "word : %s : No such file\n", filename);
            return 1;
        }
        else
        {
            int number_of_words = 0 ;
            char ch ;
            while ( (ch = fgetc(file)) != EOF)
            {
                if (ch == ' ' || ch == '.' || ch == '\n')
                {
                    number_of_words ++ ;
                }
            }
            printf("The number of words is : %d\n", number_of_words) ;
        }
        fclose(file) ;
    }
    else
    {
        if (strcmp(argv[1], "-n") == 0)
        {
            for (int i = 2 ; i < argc ; i ++)
            {
                char *filename = NULL ;
                filename = argv[i] ;
                FILE *file = fopen(filename, "r") ;
                if (! file)
                {
                    fprintf(stderr, "word : %s : No such file\n", filename);
                    return 1;
                }
                else
                {
                    int number_of_words = 0 ;
                    char ch ;
                    while ( (ch = fgetc(file)) != EOF)
                    {
                        if (ch == ' ' || ch == '.')
                        {
                            number_of_words ++ ;
                        }
                    }
                    printf("The number of words is : %d\n", number_of_words) ;
                }
                fclose(file) ;
            }
        }
        else if (strcmp(argv[1], "-d") == 0)
        {
            char *filename1 = NULL, *filename2 = NULL ;
            filename1 = argv[2] ;
            filename2 = argv[3] ;
            FILE *file1 = fopen(filename1, "r") ;
            FILE *file2 = fopen(filename2, "r") ;
            if (file1 && file2)
            {
                int number_of_words_1 = 0 ;
                char ch ;
                while ( (ch = fgetc(file1)) != EOF)
                {
                    if (ch == ' ' || ch == '.')
                    {
                        number_of_words_1 ++ ;
                    }
                }
                int number_of_words_2 = 0 ;
                while ( (ch = fgetc(file2)) != EOF)
                {
                    if (ch == ' ' || ch == '.')
                    {
                        number_of_words_2 ++ ;
                    }
                }
                if (number_of_words_1 > number_of_words_2)
                {
                    printf("File %s has %d more words than File %s\n", argv[2], number_of_words_1 - number_of_words_2, argv[3]) ;
                }
                else if (number_of_words_1 == number_of_words_2)
                {
                    printf("Both files have same number of words, difference is 0.\n") ;
                }
                else
                {
                    printf("File %s has %d more words than File %s\n", argv[3], number_of_words_2 - number_of_words_1, argv[2]) ;
                }
            }
            else if (! file1 && ! file2)
            {
                fprintf(stderr, "word : %s : No such file\n", file1);
                fprintf(stderr, "word : %s : No such file\n", file2);
                return 1 ;
            }
            else if (! file1)
            {
                fprintf(stderr, "word : %s : No such file\n", file1);
                return 1 ;
            }
            else
            {
                fprintf(stderr, "word : %s : No such file\n", file2);
                return 1 ;
            }
            fclose(file1) ;
            fclose(file2) ;
        }
        else
        {
            fprintf(stderr, "Usage Error : word [-option] [file_name]\n") ;
            return 1 ;
        }
    }
}
