#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void print_list(const node *list) {
	printf("got here\n");
    while (list != NULL) {
        printf("%d\n", list -> value);
        list = list->next;
    }
}

// adds an element to the list, puts it in the right order!!! How cool is this shit joel
void list_insert(int num, struct node **head) {

	node *initial_head = *head;
	printf("Initialized head\n");

	struct node *prev = NULL;
	printf("Created prev node\n");
    struct node *current = *head;
    printf("Created current node\n");
    struct node *next;
    printf("Created next node\n");

    struct node *new_node = malloc(sizeof(struct node));
    printf("malloc'd new node\n");

    // list is empty!!
    if ((*head) == NULL){
    	printf("entered head = null\n");
		*head = new_node;
		new_node -> value = num;
	    new_node -> next = NULL;
		return;
    }
    
    // list has next
    while ((*head != NULL)){

    	printf("ENTERED MAIN LOOP\n");

    	// new node value is greater than this nodes value (keep looking!)
		if (   num >= (*head) -> value   ){
			(*head) = (*head) -> next;

		} else {
			// this node is smaller than the one we're comparing it to. It has a home!!

			// prev might be null if this is the first element
			if (prev == NULL){
				node * temp = *head; 
				head = new_node;
				new_node -> next = temp;
			} 

			else {
				prev -> next = new_node;
				new_node -> next = next;
				break;
			}

			
			// the previous node got lost. 
		}

		// update pointers and crap. Wham. 
		next = current -> next;  
        current -> next = prev;  
        prev = current;
    	current = next;

    }

    // list doesn't have next
    new_node -> value = num;
    new_node -> next = NULL;
    *head = initial_head;
}