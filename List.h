/*
*Sonia Atre
*smatre@ucsc.edu
*
*List.h
*class: CSE101
*10/8/19
*
*Role: header file for List.c
*/
//-----------------------------------------------------------------------------
// List.h
// Header file for the List ADT
//-----------------------------------------------------------------------------
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_



// Exported type --------------------------------------------------------------

// Dictionary
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Constructor for the List ADT.
List newList();

// freeList()
// Destructor for the List ADT.
void freeList(List* pL);


// Access Functions -------------------------------------------------------------
int length(List L); // Returns the number of elements in L.
int index(List L);	//returns current index on cursor if defined, else returns -1

void* front(List L);	//returns element at front of L (Precond: length() > 0)
void* back(List L);	//returns element at back of L (Precond: length() > 0)
void* get(List L);	//returns current element on cursor in L (Precond: length() > 0 && index >= 0)
int equals(List A, List B);	//returns true(1) if List A and B are in same state, else returns false(0)
// Manipulation Procedures -------------------------------------------------------------
void clear(List L);	//resets L to empty state

void moveFront(List L);	//sets cursor under front element if L is not empty, else does nothing
void moveBack(List L);	//sets cursor under back element if L is not empty, else does nothing
void movePrev(List L);	//if cursor defined and not at front -> move cursor one step toward front of L
						//if cursor defined and at front -> cursor becomes undefined
						//if cursor undefined -> do nothing
void moveNext(List L);	//if cursor defined and not at back -> move cursor one step toward back of L
						//if cursor defined and at back -> cursor becomes undefined
						//if cursor undefined -> do nothing
void prepend(List L, void* data);	//Insert new element in L
								//if L not empty -> insert new element before front element of L

void append(List L, void* data);	//Insert new element in L
								//if L not empty -> insert new element before back element of L

void insertBefore(List L, void* data); // Insert new element before cursor.
									// Pre: length()>0, index()>=0
void insertAfter(List L, void* data); // Insert new element after cursor.
									// Pre: length()>0, index()>=0
void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete(List L); // Delete cursor element, making cursor undefined.
					// Pre: length()>0, index()>=0

// Other Operations -----------------------------------------------------------
void printList(FILE* out, List L); 	//prints string representation of L, 
									//with elements in L treated as indices
List copyList(List L); // Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.


#endif
