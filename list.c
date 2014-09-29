#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

 //modified from moodle solutions to hw03
void list_append(int value, node **head) {
    node *newNode = malloc(sizeof(node));
    node *temp = head;
    newNode->value = value;
    newNode->next = NULL;
    if (head == NULL){
        head = newNode;
    }else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// three helper functions for sort -- taken from moodle solution to hw03
void list_insert(node *new,  node **head) {
    new->next = *head;    
    *head = new;
}

void list_unlink(node *dead, node **head) {
    if (*head == dead) {
        *head = (*head)->next;
        return;
    }
    node *tmp = *head;
    while (tmp->next != NULL) {
        if (tmp->next == dead) {
            tmp->next = dead->next;
            return;
        }
        tmp = tmp->next;
    }
}

// borrowed from moodle
node *find_largest( node *list) {
    node *largest = list;
    list = list->next;
    while (list != NULL) {
        if (largest->value < list->value) {
            largest = list;
        }
        list = list->next;
    }
    return largest;
}

 //modified version of posted solutions to hw03
void list_sort( node **head) {
    node *sorted = NULL;
    node *old = *head;
    while (old != NULL) {
        node *largest = find_largest(old);
        list_unlink(largest, &old);
        list_insert(largest, &sorted);
    }
    *head = sorted;
}

void list_print(const node *list) {
    int i = 0;
    printf("***list contents begin***\n");
    while (list != NULL) {
        printf("%d\n", list->value);
        list = list->next;
    }
    printf("***list contents end***\n");
}