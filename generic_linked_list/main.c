#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct Node{
    void* data;
    struct Node* next;
};

struct GenLinkedList {
    struct Node* head;
    struct Node* end;
    int size_list;
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
    list->end=NULL;
    list->data_size = data_size;
    list->size_list = 0;

    return list;
}

void insert_start(struct GenLinkedList* list, void* data) {
    struct Node* new_node = init_node(data);

    if (list->head == NULL) {
        list->head = new_node;
        list->end = new_node;
    }
    
    new_node->next = list->head;
    list->head = new_node;
    list->size_list++;
}

void insert_end(struct GenLinkedList* list, void* data) {
    struct Node* new_node = init_node(data);

    if (list->head == NULL) {
        list->head = new_node;
        list->end = new_node;
        list->size_list++;
        return;
    }
    struct Node* current = list->head;
    while(current->next) {
       current = current->next; 
    }

    current->next = new_node;
    list->end = new_node;
    list->size_list++;
}



void *pop_start(struct GenLinkedList* list) {
    if (list->head->next == NULL)
        return NULL;

    struct Node* node = list->head->next;
    list->head->next = node->next;
    list->size_list--;
    void* data = node->data;
    free(node);

    return data;
}

void *pop_end(struct GenLinkedList* list) {
    if (list->head == NULL)
        return NULL;

    if (list->head->next == NULL) {
        struct Node* temp = list->head;
        void* data = temp->data;
        list->head = NULL;
        free(temp);
        list->size_list--;
        return data;
    }
    
    struct Node* current = list->head;
    struct Node* prev = NULL;

    while(current->next != NULL) {
        prev = current;
        current = current->next;
    }

    void* data = current->data;
    prev->next = NULL;
    free(current);
    list->size_list--;
    return data;
}

void free_linked_list(struct GenLinkedList* list) {
    struct Node* current = list->head;
    struct Node* temp = current;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    printf("Freed whole list\n");

    list->head=NULL;
    list->end=NULL;
    list->size_list=0;
    list->data_size=0;
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

    printf("prehend numbers: \n");
    for (int i = 0; i < sizeof(nums)/sizeof(int); i++) {
        printf("i: %d, nums: %d\n",i,nums[i]);
        insert_end(list, &nums[i]);
    }

    /* insert_start(list, &nums[0]); */
    /* insert_start(list, &nums[0]); */
    
    // SEGFAULT
    /* printf("poped value: %d", (int)pop_end(list)); */
    int value1 = *((int*) pop_end(list));
    printf("Poped from end: %d\n", value1);

    /* int value2 = *((int*) pop_start(list)); */
    /* printf("Poped from start: %d\n", value2); */


    print_list(list, print_int);
    
    printf("Size of list: %d\n", list->size_list);

    free_linked_list(list);
}
