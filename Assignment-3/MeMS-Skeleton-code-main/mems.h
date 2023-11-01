/*
All the main functions with respect to the MeMS are inplemented here
read the function discription for more details

NOTE: DO NOT CHANGE THE NAME OR SIGNATURE OF FUNCTIONS ALREADY PROVIDED
you are only allowed to implement the functions
you can also make additional helper functions a you wish

REFER DOCUMENTATION FOR MORE DETAILS ON FUNSTIONS AND THEIR FUNCTIONALITY
*/
// add other headers as required
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#define HOLE 0
#define PROCESS 1

typedef struct subNode
{
    int size;
    int type;
    struct subNode *next;
} subNode;

typedef struct Node
{
    int size;
    struct Node *next;
    subNode *sideChain;
} Node;

Node *head;
/*
Use this macro where ever you need PAGE_SIZE.
As PAGESIZE can differ system to system we should have flexibility to modify this
macro to make the output of all system same and conduct a fair evaluation.
*/
#define PAGE_SIZE 4096

/*
Initializes all the required parameters for the MeMS system. The main parameters to be initialized are:
1. the head of the free list i.e. the pointer that points to the head of the free list
2. the starting MeMS virtual address from which the heap in our MeMS virtual address space will start.
3. any other global variable that you want for the MeMS implementation can be initialized here.
Input Parameter: Nothing
Returns: Nothing
*/
void mems_init()
{
    head = (Node *)mmap(NULL, sizeof(Node), PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
    head->sideChain = NULL;
    head->next = NULL;
}

/*
This function will be called at the end of the MeMS system and its main job is to unmap the
allocated memory using the munmap system call.
Input Parameter: Nothing
Returns: Nothing
*/
void mems_finish()
{
    munmap(head, sizeof(Node));
    munmap(head->sideChain, PAGE_SIZE);

}

/*
Allocates memory of the specified size by reusing a segment from the free list if
a sufficiently large segment is available.

Else, uses the mmap system call to allocate more memory on the heap and updates
the free list accordingly.

Note that while mapping using mmap do not forget to reuse the unused space from mapping
by adding it to the free list.
Parameter: The size of the memory the user program wants
Returns: MeMS Virtual address (that is created by MeMS)
*/
void *mems_malloc(size_t size)
{
    Node *curr = head;
    while (curr->next != NULL)
    {

        if (curr->sideChain == NULL)
        {
            head->sideChain = (subNode *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
            head->sideChain->size = size;
            head->sideChain->type = PROCESS;
            head->sideChain->next = NULL;
            return head->sideChain;
        }
        else
        {
            subNode *currChain = curr->sideChain;
            int val = 0;
            while (currChain->next != NULL)
            {
                val += currChain->size;
                currChain = currChain->next;
            }
            if (val + size <= PAGE_SIZE)
            {
                currChain->next = (subNode *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
                currChain->next->size = size;
                currChain->next->type = PROCESS;
                currChain->next->next = NULL;
                return currChain->next;
            }
            else
            {
                curr->next = (Node *)mmap(NULL, sizeof(Node), PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
                curr->next->next = NULL;
                curr->next->sideChain = NULL;
            }
        }
        curr = curr->next;
    }
}

/*
this function print the stats of the MeMS system like
1. How many pages are utilised by using the mems_malloc
2. how much memory is unused i.e. the memory that is in freelist and is not used.
3. It also prints details about each node in the main chain and each segment (PROCESS or HOLE) in the sub-chain.
Parameter: Nothing
Returns: Nothing but should print the necessary information on STDOUT
*/
void mems_print_stats()
{
}

/*
Returns the MeMS physical address mapped to ptr ( ptr is MeMS virtual address).
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: MeMS physical address mapped to the passed ptr (MeMS virtual address).
*/
void *mems_get(void *v_ptr)
{
}

/*
this function free up the memory pointed by our virtual_address and add it to the free list
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: nothing
*/
void mems_free(void *v_ptr)
{
}