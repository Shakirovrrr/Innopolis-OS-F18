#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int val;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct LinkedList {
	Node *head;
	Node *tail;
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
	if (!new) return 0;

	new->size = 0;
	new->head = 0;
	new->tail = 0;

	return new;
}

void __initList(LinkedList *list, Node *new) {
	new->prev = 0;
	new->next = 0;

	list->head = new;
	list->tail = new;
	list->size++;
}

Node *__jumpToNode(LinkedList *list, size_t ix) {
	Node *current = list->head;

	for (int i = 0; i < ix; ++i) {
		current = current->next;
	}

	return current;
}

void __appendNode(LinkedList *list, Node *val) {
	Node *end = list->tail;
	val->prev = end;
	end->next = val;

	list->tail = val;
	list->size++;
}

void __prependNode(LinkedList *list, Node *val) {
	Node *begin = list->head;
	val->next = begin;
	begin->prev = val;

	list->head = val;
	list->size++;
}

char insertNode(LinkedList *list, size_t ix, int val) {
	if ((ix > list->size && list->size != 0) || ix < 0) return 1;

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

	if (ix == list->size) {
		__appendNode(list, new);
		return 0;
	}

	Node *current = __jumpToNode(list, ix);
	new->prev = current->prev;
	new->next = current;
	current->prev->next = new;
	current->prev = new;
	list->size++;

	return 0;
}

char deleteNode(LinkedList *list, size_t ix) {
	if ((ix >= list->size && list->size != 0) || ix < 0) return 1;

	Node *current;
	if (ix == 0) {
		current = list->head;
		current->next->prev = 0;
		list->head = current->next;
	} else if (ix == list->size - 1) {
		current = list->tail;
		current->prev->next = 0;
		list->tail = current->prev;
	} else {
		current = __jumpToNode(list, ix);
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}

	free(current);
	list->size--;

	return 0;
}

void printList(LinkedList *list) {
	if (!list || list->size == 0) {
		printf("\n");
		return;
	}

	Node *it = list->head;
	while (it->next) {
		printf("%d ", it->val);
		it = it->next;
	}
	printf("%d\n", it->val);
}

int main() {
	LinkedList *list = newList();
	char error = 0;

	// Start inserting to empty
	// list from 0th index
	error |= insertNode(list, 0, 3);
	error |= insertNode(list, 1, 2);
	error |= insertNode(list, 1, 4);
	error |= insertNode(list, 2, 1);
	error |= deleteNode(list, 1);

	if (!error) {
		printf("Success\n");
		printList(list);
	} else {
		fprintf(stderr, "Error\n");
	}

	return 0;
}