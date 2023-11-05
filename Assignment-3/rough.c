#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

typedef struct Node
{
    int val;
    struct Node *next;
} Node;

int main()
{
    Node *test = (Node *)mmap(NULL, sizeof(Node), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON - 1, 0);
    if (test == MAP_FAILED)
    {
        perror("Error in mmap for newNode");
        exit(EXIT_FAILURE);
    }
    printf("%lu\n", test);
    return 0;
}
