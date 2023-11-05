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
#include <stdbool.h>
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
    struct Node *next;
    subNode *sideChain;
    int pages;
} Node;

static Node *head;
static int pages = 0;
/*
Use this macro where ever you need PAGE_SIZE.
As PAGESIZE can differ system to system we should have flexibility to modify this
macro to make the output of all system same and conduct a fair evaluation.
*/
#define PAGE_SIZE 4096

// Helping function to print whole DS
void printList()
{
    Node *curr = head;
    int i = 0;
    while (curr != NULL)
    {
        printf("Node: %d\n", i++);
        subNode *currChain = curr->sideChain;
        while (currChain != NULL)
        {
            printf("Chain: %d\n", currChain);
            currChain = currChain->next;
        }
        curr = curr->next;
    }
}
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
    head = (Node *)mmap(NULL, sizeof(Node), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    head->pages = 0;
    if (head == MAP_FAILED)
    {
        perror("Error in mmap for head");
        exit(EXIT_FAILURE);
    }
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
    Node *curr = head;
    while (curr != NULL)
    {
        subNode *currChain = curr->sideChain;
        while (currChain != NULL)
        {
            subNode *temp = currChain;
            currChain = currChain->next;
            munmap(temp, temp->size);
        }
        Node *temp = curr;
        curr = curr->next;
        munmap(temp, sizeof(Node));
    }
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
    void *vaddress = 0;
    Node *temp = head;
    while (temp != NULL)
    {
        subNode *curr = temp->sideChain;
        subNode *prev = NULL;
        while (curr != NULL)
        {
            vaddress += curr->size;
            if (curr->type == HOLE && curr->size >= size)
            {
                subNode *semiNode = (subNode *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
                if (semiNode == MAP_FAILED)
                {
                    perror("Error in mmap for semiNode");
                    exit(EXIT_FAILURE);
                }
                semiNode->size = size;
                semiNode->type = PROCESS;
                semiNode->next = curr;
                vaddress -= size;
                curr->size -= size;
                if (prev == NULL)
                {
                    temp->sideChain = semiNode;
                }
                else
                {
                    prev->next = semiNode;
                }
                return vaddress;
            }
            prev = curr;
            curr = curr->next;
        }
        temp = temp->next;
    }

    void *v_addr = 0;
    Node *curr = head;
    bool check = false;
    while (curr != NULL)
    {
        void *v_addr_temp = 0;
        subNode *currentchain = curr->sideChain;
        int space_used = 0;
        while (currentchain != NULL)
        {
            space_used += currentchain->size;
            v_addr += currentchain->size;
            v_addr_temp += currentchain->size;
            currentchain = currentchain->next;
        }

        if (space_used + size <= curr->pages * PAGE_SIZE && curr != head)
        {
            printf("allocating in same node\n");
            check = true;
            subNode *newNode = (subNode *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
            if (newNode == MAP_FAILED)
            {
                perror("Error in mmap for newNode");
                exit(EXIT_FAILURE);
            }
            newNode->size = size;
            newNode->type = PROCESS;
            newNode->next = NULL;
            subNode *curr_side = curr->sideChain;
            while (curr_side->next != NULL)
                curr_side = curr_side->next;
            curr_side->next = newNode;
            v_addr += size;
            return v_addr;
        }
        else if (curr != head)
        {
            v_addr += ((void *)(PAGE_SIZE * (curr->pages)) - v_addr_temp);
        }
        curr = curr->next;
    }

    if (!check)
    {
        printf("making new node\n");
        curr = head;
        while (curr->next)
            curr = curr->next;
        Node *new_node = (Node *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (new_node == MAP_FAILED)
        {
            perror("Error in mmap for newNode");
            exit(EXIT_FAILURE);
        }
        curr->next = new_node;
        subNode *newNode = (subNode *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        printf("bbb %lu\n", new_node);
        new_node->pages = size / PAGE_SIZE + (size % PAGE_SIZE == 0 ? 0 : 1);
        pages += new_node->pages;
        if (newNode == MAP_FAILED)
        {
            perror("Error in mmap for newNode");
            exit(EXIT_FAILURE);
        }
        newNode->size = size;
        newNode->type = PROCESS;
        v_addr += size;
        new_node->sideChain = newNode;
        new_node->next = NULL;
        return v_addr;
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
    printf("Number of pages used : %d\n", pages);
    printf("Details -> \n", 0);
    Node *curr = head->next;
    int i = 1;
    while (curr != NULL)
    {
        printf("Node: %d Pages : %d\n", i++, curr->pages);
        subNode *currChain = curr->sideChain;
        while (currChain != NULL)
        {
            if (currChain->type == PROCESS)
            {
                printf("Process of size : %d\n", currChain->size);
            }
            else
            {
                printf("Hole of size : %d\n", currChain->size);
            }
            currChain = currChain->next;
        }
        curr = curr->next;
    }
    printf("Unused space of each Node ->\n");
    curr = head->next;
    int j = 1;
    while (curr != NULL)
    {
        int val = 0;
        subNode *currChain = curr->sideChain;
        while (currChain != NULL)
        {
            val += currChain->size;
            currChain = currChain->next;
        }

        printf("Node %d have unused space of %d bytes\n", j++, curr->pages * PAGE_SIZE - val);
        curr = curr->next;
    }
}

/*
Returns the MeMS physical address mapped to ptr ( ptr is MeMS virtual address).
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: MeMS physical address mapped to the passed ptr (MeMS virtual address).
*/
void *mems_get_sanyam(void *v_ptr)
{
    Node *curr = head->next;
    void *trace_addr = 0;
    while (curr != NULL)
    {
        int count = 0;
        subNode *chain = curr->sideChain;
        while (chain != NULL)
        {
            trace_addr += chain->size;
            count += chain->size;
            if (trace_addr >= v_ptr)
            {
                printf("%lu\n",trace_addr);
                return (void *)curr+1; //doubt
            }
            count += chain->size;
            chain = chain->next;
        }
        trace_addr += ((curr->pages) * PAGE_SIZE )- count;
        if (trace_addr >= v_ptr)
        {
            printf("This is Virtual address of unused space\n");
            return (void *)-1;
        }
        curr = curr->next;
    }
    printf("Invalid v_ptr\n");
    return (void *)(-1);
}


void *mems_get(void *v_ptr)
{
   void *trace_addr = 0;
    Node *curr = head->next;
    while (curr)
    {
        if (curr->pages * PAGE_SIZE + trace_addr < v_ptr)
        {
            trace_addr += curr->pages * PAGE_SIZE;
            curr = curr->next;
        }
        else
        {
            subNode *currChain = curr->sideChain;
            while (currChain)
            {
                trace_addr += currChain->size;
                if (trace_addr > v_ptr)
                {
                    return (void *)currChain;
                }
                else if (trace_addr == v_ptr)
                {
                    return (void *)currChain->next;
                }
                currChain = currChain->next;
            }
        }
    }
    printf("Error in mems_get\n");
    return void *(-1);
}

/*
this function free up the memory pointed by our virtual_address and add it to the free list
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: nothing
*/
void mems_free(void *v_ptr)
{
}
