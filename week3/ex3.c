#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int val;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct LinkedList {
	Node *begin;
	Node *end;
	size_t size;
} LinkedList;

Node *__newNode(int val) {
	Node *new = (Node *) malloc(sizeof(Node));
	if (!new) return 0;
	new->val = val;
	new->prev = 0;
	new->next = 0;

	return new;
}

LinkedList *newList() {
	LinkedList *new = (LinkedList *) malloc(sizeof(LinkedList));
	new->size = 0;
	new->begin = 0;
	new->end = 0;

	return new;
}

void __initList(LinkedList *list, Node *new) {
	new->prev = 0;
	new->next = 0;

	list->begin = new;
	list->end = new;
	list->size++;
}

char __appendNode(LinkedList *list, Node *val) {
	if (!val) return 1;

	Node *end = list->end;
	val->prev = end;
	end->next = val;

	list->end = val;
	list->size++;

	return 0;
}

char __prependNode(LinkedList *list, Node *val) {
	if (!val) return 1;

	Node *begin = list->begin;
	val->next = begin;
	begin->prev = val;

	list->begin = val;
	list->size++;

	return 0;
}

char insertNode(LinkedList *list, size_t ix, int val) {
	if ((ix >= list->size && list->size != 0) || ix < 0) return 1;

	Node *new = __newNode(val);
	if (!new) return 1;

	if (list->size == 0) {
		__initList(list, new);
		return 0;
	}

	if (ix == 0) {
		__prependNode(list, new);
		return 0;
	}

	Node *current = list->begin + ix;
	new->prev = current->prev;
	new->next = current;
	current->prev->next = new;
	current->prev = new;
	list->size++;

	return 0;
}

char deleteNode(LinkedList *list, size_t ix) {
	if ((ix >= list->size && list->size != 0) || ix < 0) return 1;

	Node *current = list->begin + ix;
	current->prev->next = current->next;
	current->next->prev = current->prev;
	list->size--;

	free(current);

	return 0;
}

void printList(LinkedList *list) {
	if (!list || list->size == 0) {
		printf("\n");
		return;
	}

	Node *it = list->begin;
	while (it->next) {
		printf("%d ", it->val);
	}
	printf("%d\n", it->val);
}

int main() {
	LinkedList *list = newList();
	insertNode(list, 0, 0);
	insertNode(list, 1, 1);
	insertNode(list, 1, 2);
	insertNode(list, 3, 4);
	deleteNode(list, 2);
	printList(list);

	return 0;
}