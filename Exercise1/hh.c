#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct LinkedList {
    LinkedListNode* first;
    LinkedListNode* last;
};

struct LinkedListNode {
    LinkedListNode* previous;
    LinkedListNode* next;
    char* data;
};

LinkedList* LinkedList_create()
{
    LinkedList* list = malloc( sizeof( LinkedList ) );
    list->first = NULL;
    list->last = NULL;
    return list;
}

void LinkedList_append(LinkedList *list, char *data)
{
    LinkedListNode* newnode = malloc(sizeof(LinkedListNode));
    newnode->previous = list->last;
    newnode->next = NULL;
    newnode->data = data;
    if(list->last!=NULL){
        list->last->next = newnode;
    } else {
        list->first = newnode;
    }
    list->last = newnode;
}

static void LinkedListNode_delete(LinkedListNode *rootnode)
{
    if(rootnode->next!=NULL){
        LinkedListNode_delete(rootnode->next);

    }
    free(rootnode);
}

void LinkedList_delete(LinkedList *list)
{
    LinkedListNode_delete(list->first);
    free(list);
}

int main() {
    char* elem = 'c';
    LinkedList* liste;
    liste = LinkedList_create();
    LinkedList_append(liste, elem);
    LinkedList_append(liste, elem);
    LinkedList_append(liste, elem);
    printf("%c", liste->first->data);
    LinkedList_delete(liste);
    printf("%c", liste->first->data);
    free(liste);
    return 0;
}

