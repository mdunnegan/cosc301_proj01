#ifndef __LIST_H__
#define __LIST_H__

/* your list data structure declarations */


/* your function declarations associated with the list */
typedef struct node {
	int value;
	struct node *next;
} node;

void list_insert(int num, node **head);
void print_list(const node *head);

#endif // __LIST_H__