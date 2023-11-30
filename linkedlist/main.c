#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct Node{
    void* data;
    struct Node* next;
};

struct GenLinkedList {
    struct Node* head;
    size_t data_size;
};

struct Node* init_node(void* data) {
    struct Node* node = malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;

    return node;
}

struct GenLinkedList* init_linked_list(size_t data_size) {
    struct GenLinkedList* list = malloc(sizeof(struct GenLinkedList));
    list->head=NULL;
    list->data_size = data_size;

    return list;
}

void prepend(struct GenLinkedList* list, void* data) {
    struct Node* node = init_node(data);

    if (list->head == NULL) {
        list->head = node;
        return;
    }
    printf("not first\n");
    node->next = list->head->next;
    list->head->next = node;
}

void print_list(struct GenLinkedList* list, void (*print)(void*)) {
    struct Node* t = list->head;
    int i=0;

    while(t) {
        printf("i = %d: ",++i);
        print(t->data);
        printf("\n");
        t = t->next;
    }
}

void print_int(void* integer) {
    printf("%d",*((int*) integer));
}

int main(int argv, char** argc) {
    (void) argv;
    (void) argc;
    printf("Hello world\n");

    struct GenLinkedList* list = init_linked_list(sizeof(int));

    int nums[] = {1,2,3,4};
    int len_nums = 4;

    printf("prehend numbers: \n");
    for (int i = 0; i < len_nums; i++) {
        printf("i: %d\n",i);
        prepend(list, &nums[i]);
    }

    print_list(list, print_int);
    
}
