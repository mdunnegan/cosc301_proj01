#ifndef __LIST_H__
#define __LIST_H__

/* your list data structure declarations */
typedef struct node {
	int value;
	struct node *next;
} node;

/* your function declarations associated with the list */

void list_append(int value, node **head);
void list_print(const node *list);
void list_sort(node **head);
node *find_largest(node *list);
void list_unlink(node *dead, node **head);
void list_insert(node *new, node **head);


#endif // __LIST_H__