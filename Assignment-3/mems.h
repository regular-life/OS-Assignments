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
#define START (void *)1000 // start of virtual address

typedef struct subNode
{
    int size;
    int val;
    int type;
    struct subNode *next;
    struct subNode *prev;
} subNode;

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
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
#define SIZE 1000

struct KeyValuePair
{
    void *virtual_address;
    void *physical_address;
};

struct KeyValuePair dictionary[SIZE];
int dictionarySize = 0;

int InsertDict(void *virtual_address, void *physical_address)
{
    if (dictionarySize < SIZE)
    {
        dictionary[dictionarySize].virtual_address = virtual_address;
        dictionary[dictionarySize++].physical_address = physical_address;
        return 1; // Success
    }
    else
    {
        printf("***Dictionary is full, update SIZE in mems.h to make this work***\n");
        return 0;
    }
}

void *searchDict(void *virtual_address)
{
    for (int i = 0; i < dictionarySize - 1; i++)
    {
        if (dictionary[i + 1].virtual_address > virtual_address)
        {
            return dictionary[i].physical_address + (virtual_address - dictionary[i].virtual_address);
        }
    }
    return NULL;
}

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

void removeFromDictionary(void *virtual_address)
{
    int found = 0;
    for (int i = 0; i < dictionarySize; i++)
    {
        if (dictionary[i].virtual_address == virtual_address)
        {
            found = 1;
             for (int j = i; j < dictionarySize - 1; j++)
            {
                dictionary[j] = dictionary[j + 1];
            }
            dictionarySize--;
            break;
        }
    }
    if (!found)
    {
        printf("Key not found in the dictionary. Cannot remove.\n");
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

void *HOLE_alloc(size_t size)
{
    void *vaddress = START;
    Node *temp = head;
    while (temp != NULL)
    {
        subNode *curr = temp->sideChain;
        subNode *prev = NULL;
        while (curr != NULL)
        {
            if (curr->type == HOLE && curr->size > size)
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
                curr->prev = semiNode ;
                curr->size -= size;
                if (prev == NULL)
                {
                    temp->sideChain = semiNode;
                }
                else
                {
                    prev->next = semiNode;
                    semiNode->prev= prev ;
                }
                InsertDict(vaddress, (void *)semiNode);
                return vaddress;
            }
            else if (curr->type == HOLE && curr->size == size)
            {
                curr->type = PROCESS;
                return vaddress;
            }
            vaddress += curr->size;
            prev = curr;
            curr = curr->next;
        }
        temp = temp->next;
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
    void *add = HOLE_alloc(size);
    if (add != 0)
    {
        return add;
    }
    else
    {
        Node *curr = head;
        while (curr->next)
            curr = curr->next;
        Node *new_node = (Node *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (new_node == MAP_FAILED)
        {
            perror("Error in mmap for newNode");
            exit(EXIT_FAILURE);
        }
        curr->next = new_node;
        new_node->prev = (curr == head ? NULL : curr) ;
        subNode *newNode = (subNode *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        new_node->pages = size / PAGE_SIZE + (size % PAGE_SIZE == 0 ? 0 : 1);
        pages += new_node->pages;
        if (newNode == MAP_FAILED)
        {
            perror("Error in mmap for newNode");
            exit(EXIT_FAILURE);
        }
        newNode->size = new_node->pages * PAGE_SIZE;
        newNode->type = HOLE;
        new_node->sideChain = newNode;
        HOLE_alloc(size);
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
    // printf("Number of pages used : %d\n", pages);
    // printf("Details -> \n");
    printf("----- MeMS SYSTEM STATS -----\n");
    Node *curr = head->next;
    int i = 1;
    void *initial = START;
    int main_chain_length = 0;
    while (curr != NULL)
    {
        printf("MAIN[%d:%d]-> ", initial, curr->pages * PAGE_SIZE + initial - 1);
        // printf("Node: %d contains %d Pages\n", i++, curr->pages);
        subNode *currChain = curr->sideChain;
        while (currChain != NULL)
        {
            if (currChain->type == PROCESS)
            {
                printf("P");
            }
            else if (currChain->type == HOLE)
            {
                printf("H");
            }
            printf("[%d:%d] <-> ", initial, initial + currChain->size - 1);
            initial += currChain->size;
            currChain = currChain->next;
        }
        printf("NULL\n");
        curr = curr->next;
        main_chain_length++;
    }
    printf("Pages used : %d\n", pages);
    curr = head->next;
    int j = 1;
    int space_unused = 0;
    while (curr != NULL)
    {
        subNode *currChain = curr->sideChain;
        while (currChain != NULL)
        {
            if (currChain->type == HOLE)
            {
                space_unused += currChain->size;
            }
            currChain = currChain->next;
        }
        curr = curr->next;
    }
    printf("Space unused : %d\n", space_unused);
    printf("Main chain length: %d\n", main_chain_length);
    int sub_chain_length_array[main_chain_length];
    curr = head->next;
    i = 0;
    while (curr)
    {
        subNode *currChain = curr->sideChain;
        int sub_chain_length = 0;
        while (currChain != NULL)
        {
            sub_chain_length++;
            currChain = currChain->next;
        }
        sub_chain_length_array[i++] = sub_chain_length;
        curr = curr->next;
    }
    printf("Sub chain length array: [");
    for (int i = 0; i < main_chain_length; i++)
    {
        printf("%d", sub_chain_length_array[i]);
        if (i != main_chain_length - 1)
        {
            printf(", ");
        }
    }
    printf("]\n-----------------------------\n");
}

/*
Returns the MeMS physical address mapped to ptr ( ptr is MeMS virtual address).
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: MeMS physical address mapped to the passed ptr (MeMS virtual address).
*/
void *mems_get(void *v_ptr)
{
    return searchDict(v_ptr);
}

/*
this function free up the memory pointed by our virtual_address and add it to the free list
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: nothing
*/
void mems_free(void *v_ptr)
{
    void *trace_addr = START;
    Node *curr = head->next;
    while (curr)
    {
        void *temp_add = 0;
        subNode *curr_chain = curr->sideChain;
        subNode *prev = NULL;
        while (curr_chain != NULL)
        {
            if (trace_addr == v_ptr)
            {
                curr_chain->type = HOLE;
                // Merging two consecutive Holes
                if (prev != NULL && prev->type == HOLE)
                {
                    prev->size += curr_chain->size;
                    prev->next = curr_chain->next;
                    munmap(curr_chain, curr_chain->size);
                    curr_chain = prev;
                }
                if (curr_chain->next != NULL && curr_chain->next->type == HOLE)
                {
                    curr_chain->size += curr_chain->next->size;
                    subNode *temp = curr_chain->next;
                    curr_chain->next = curr_chain->next->next;
                    munmap(temp, temp->size);
                }

                return;
            }
            trace_addr += curr_chain->size;
            temp_add += curr_chain->size;
            prev = curr_chain;
            curr_chain = curr_chain->next;
        }
        trace_addr += ((void *)(PAGE_SIZE * (curr->pages)) - temp_add);
        curr = curr->next;
    }
}
