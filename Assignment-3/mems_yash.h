#define PAGE_SIZE 4096
#define MAX_PAGE_POINTERS (2048)
#define MAX_PARTITIONS 64

typedef struct mainNode
{
    int page;
    void* pagePointers[MAX_PAGE_POINTERS];
} mainNode;

typedef struct mainChain
{
    mainNode nodes[MAX_PAGE_POINTERS];
} mainChain;

typedef struct page {
    int numPartitions;
    void* partitionPointers[MAX_PARTITIONS];
} page;
