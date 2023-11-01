#include<stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

typedef struct Node{
    int val;
    struct Node *next; 
}Node ;

int main()
{
    // Node * head = (Node *)malloc(sizeof(Node));
    // head->val = 10;
    // Node * sec = (Node *)malloc(sizeof(Node));
    // sec->val = 20;
    // head->next = sec;
    // Node * thir = (Node *)malloc(sizeof(Node));
    // thir->val = 30;
    // head->next->next = thir; 

    // Node * curr = head ;
    // while(curr->next!=NULL){
    //     curr = curr->next;
    // }
    // printf("%d", head->val) ;
    Node* test = (Node *)mmap(NULL, 20, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
    printf("%d\n",test);
return 0;
}