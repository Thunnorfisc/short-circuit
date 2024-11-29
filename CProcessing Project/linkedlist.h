/*
* @author	William Wibisana Dumnanauw (williamwibisana.d)
* @brief	The file contains a linked list data structure
* @file		linkedlist.h
* All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/
#pragma once
/*
* One node, contains data as well as the next and previous nodes
*/
typedef struct Node
{
	int data;
	struct Node* next;
	struct Node* prev;
} Node;

/*
* The entire linked list, containing the length of it, as well as the head node and the tail node
*/
struct LinkedList {
	int length;
	Node* head;
	Node* tail;
};

/*
This is a doubly linked list.
It is a pointer to the struct linkedlist.
Use the functions starting with List_ to modify or access the list.
*/
typedef struct LinkedList LinkedList;

/*
Brief: List Initialization using Array.
This is a initializor for the list using an array as it's input.
Parameters:
  - int* Array: Array that is to be used.
  - int Size: This is the size of the array.
*/
LinkedList List_Initialize_Array(int*, int);

/*
Brief: List Initialization using Value.
This is a initializor for the list using one value as it's input.
Parameters:
  - int value: Value that will be the headd of the linkedlist.
*/
LinkedList List_Initialize(int);

/*
Brief: Traverse through the list and print out the values in order
This traverses through the list in order and prints out the values in order of the nodes.
Parameters:
  - LinkedList list: The list to be traversed through
*/
void List_Traverse(LinkedList);

/*
Brief: Get the length of the list
Parameters:
  - LinkedList list: The list to get the length of
*/
int List_GetLength(LinkedList);

/*
Brief: Insert data at the start of the list
Parameters:
  - LinkedList list: The list which the data would be inserted into
  - int value: The value to be inserted
*/
void List_Insert_Start(LinkedList*, int);

/*
Brief: Insert data at the end of the list
Parameters:
  - LinkedList list: The list which the data would be inserted into
  - int value: The value to be inserted
*/
void List_Insert_End(LinkedList*, int);

/*
Brief: Insert data at a certain index of the list
Parameters:
  - LinkedList list: The list which the data would be inserted into
  - int index: The index where the value will be inserted
  - int value: The value to be inserted
*/
void List_Insert_Index(LinkedList*, int, int);

/*
Brief: Removes the first element/head of the list and returns the value of the head
Parameters:
  - LinkedList list: List to be dequed
*/
int List_Dequeue(LinkedList*);

/*
Brief: Removes the last element/tail of the list and returns the value of the tail
Parameters:
  - LinkedList list: List to be popped
*/
int List_Pop(LinkedList*);

/*
Brief: Gets the element at a certain index, does not remove from list
Parameters:
  - LinkedList list: List which contains the value
  - int index: The index of the element (Starting from 0)
*/
int List_GetAtIndex(LinkedList, int);

/*
Brief: Frees the memory location of the list
If not called, list might cause a memory leak
Parameters:
  - LinkedList list: The list to be deleted and memory freed
*/
void List_Free(LinkedList*);