/*
*Sonia Atre
*smatre@ucsc.edu
*
*List.c
*class: CSE101
*10/11/19
*
*Role: creates a List ADT used for the Matrix implementation
*/

#include<stdlib.h>
#include<stdio.h>
#include"List.h"
#include<assert.h>

// Private Types and Functions ------------------------------------------------

//NodeObj type
typedef struct NodeObj {
	struct NodeObj* prev;
	struct NodeObj* next;
	void* data;
} NodeObj;

typedef NodeObj* Node;

//ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

//newNode()
//Constructor for Node type
Node newNode(void* d) {
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N->data = d;
	N->prev = NULL;
	N->next = NULL;
	return N;
}

//freeNode()
//Destructor for Node type
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

//Constructors-Destructors ------------------------------------------------

//newList()
//Constructor for the List ADT
List newList() {
	List L = malloc(sizeof(ListObj));
	assert(L != NULL);
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return L;
}

//freeList()
//Destructor for the List ADT
void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

//Access functions -------------------------------------------------------------
//length()
//returns number of elements in L
int length(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: length() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return L->length;
}

//index()
//returns index of current element on cursor
int index(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: index() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return L->index;
}
//front()
//returns element at front of L
//precond: length() > 0
void* front(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: front() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: front() called on empty List\n");
		exit(EXIT_FAILURE);
	}
	return L->front->data;
}

//back()
//returns element at back of L
//precond: length() > 0
void* back(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: back() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: back() called on empty List\n");
		exit(EXIT_FAILURE);
	}
	return L->back->data;
}

//get()
//returns element of L where cursor is
//precond: length > 0 && index >= 0
void* get(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: get() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: get() called on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index < 0) {
		fprintf(stderr, "List Error: get() called on invalid cursor index\n");
		exit(EXIT_FAILURE);
	}
	return L->cursor->data;
}
// Manipulation Procedures -------------------------------------------------------------

//clear()
//returns L to empty state
void clear(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: clear() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	while (L->length > 0) {
		deleteFront(L);
	}
	//freeAllNodes(L->front);

	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

//moveFront()
//moves cursor to front element if L is non-empty, else does nothing
void moveFront(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: moveFront() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->front != NULL) {
		L->index = 0;
		L->cursor = L->front;
	}
}

//moveBack()
//moves cursor to back element if L is non-empty, else does nothing
void moveBack(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: moveBack() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->front != NULL) {
		L->index = L->length - 1;
		L->cursor = L->back;
	}
}

//movePrev()
//if cursor defined, 1. If at front, cursor becomes undef,
//2. If not at front, move cursor one step towards front
//if not defined, do nothing
void movePrev(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: movePrev() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	// if (L->cursor != NULL && L->index != -1) {
	// 	int frontCursor = 0;
	// 	if (L->index != frontCursor) {
	// 		L->cursor = L->cursor->prev;
	// 		L->index--;
	// 	} else {
	// 		L->index = -1;      
	// 	}
	// }
	if (L->index >= 0) {
		L->cursor = L->cursor->prev;
		L->index--;
	}
}

//moveNext()
//if cursor defined, 1. If at back, cursor becomes undef,
//2. If not at back, move cursor one step towards back
//if not defined, do nothing
void moveNext(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: moveNext() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->index != -1) {
		int backCursor = L->length - 1;
		if (L->cursor != NULL && L->index != backCursor) {
			L->cursor = L->cursor->next;
			L->index++;
		} else {
			L->index = -1;
		}
	}
}
//prepend()
//inserts new node before front
void prepend(List L, void* data) {
	if (L == NULL) {
		fprintf(stderr, "List Error: prepend() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(data);

	if (L->front == NULL) {
		L->back = N;
	} else {
		L->front->prev = N;
	}
	N->next = L->front;
	L->front = N;
	L->length++;
	L->index++;
}

//append()
//inserts new node after back element
void append(List L, void* data) {
	if (L == NULL) {
		fprintf(stderr, "List Error: append() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(data);

	if (L->back == NULL) {
		L->front = N;
	} else {
		L->back->next = N;
	}
	N->prev = L->back;
	L->back = N;
	L->length++;
}

//insertBefore
//inserts element before cursor
//Precond: length > 0 && index >= 0
void insertBefore(List L, void* data) {
	if (L == NULL) {
		fprintf(stderr, "List Error: insertBefore() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: insertBefore() called on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index < 0) {
		fprintf(stderr, "List Error: insertBefore() called on invalid cursor index\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == 0) {
		prepend(L, data);
	} else {
		Node N = newNode(data);
		Node C = L->cursor;
		//add each of four pointers
		N->prev = C->prev;
		C->prev->next = N;
		N->next = L->cursor;
		C->prev = N;
		L->index++;
		L->length++;
	}
}

//insertAfter
//inserts element after cursor
//Precond: length > 0 && index >= 0
void insertAfter(List L, void* data) {
	if (L == NULL) {
		fprintf(stderr, "List Error: insertAfter() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: insertAfter() called on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index < 0) {
		fprintf(stderr, "List Error: insertAfter() called on invalid cursor index\n");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(data);
	if (L->index == L->length - 1) {
		append(L, data);
	} else {
		Node C = L->cursor;
		//add each of four pointers
		N->next = C->next;
		N->next->prev = N;
		C->next = N;
		N->prev = C;
		L->length++;
	}
}

//deleteFront()
//deletes element at front of L
void deleteFront(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: deleteFront() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: deleteFront() called on empty List\n");
		exit(EXIT_FAILURE);
	}

	if (L->cursor == L->front) {
		L->cursor = NULL;
		L->index = -1;
	}
	Node N = L->front;
	L->front = N->next;
	if (L->front != NULL) {
		L->front->prev = NULL;
	}
	L->length--;
	if(L->cursor != NULL) {
		L->index--;
	}
	if (L->length == 0) {
		L->back = NULL;
	}
	freeNode(&N);

}

//deleteBack()
//deletes element at back of L
void deleteBack(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: deleteBack() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: deleteBack() called on empty List\n");
		exit(EXIT_FAILURE);
	}

	if (L->cursor == L->back) {
		L->cursor = NULL;
		L->index = -1;
	}
	Node N = L->back;
	L->back = N->prev;
	if (L->back != NULL) {
		L->back->next = NULL;
	}
	L->length--;
	if (L->length == 0) {
		L->front = NULL;
	}
	freeNode(&N);

}

//delete()
//deletes element at cursor
void delete(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: delete() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: delete() called on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index < 0) {
		fprintf(stderr, "List Error: delete() called on invalid cursor index\n");
		exit(EXIT_FAILURE);
	}

	Node N = L->cursor;
	if (N == L->front) {
		deleteFront(L);
	} else if (N == L->back) {
		deleteBack(L);
	} else {
		N->prev->next = N->next;
		N->next->prev = N->prev;
		freeNode(&N);
		L->length--;
	}
	L->cursor = NULL;
	L->index = -1;
}
// Other operations -----------------------------------------------------------
//printList()
//
/*void printList(FILE* out, List L) {
	if (out == NULL) {
		fprintf(stderr, "List Error: printList() called on NULL out reference\n");
		exit(EXIT_FAILURE);
	}
	if (L == NULL) {
		fprintf(stderr, "List Error: printList() called on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(out, "[]\n");
	}
	Node temp = L->front;
	while (temp != NULL) {
		fprintf(out, "%d ", temp->data);
		temp = temp->next;
	}
	fprintf(out, "\n");
}
*/