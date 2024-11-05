#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

typedef struct LinkedList LinkedList;

Node* create_node(int data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node != NULL)
	{
		new_node->data = data;
		new_node->next = NULL;
		new_node->prev = NULL;
	}
	return new_node;
}

LinkedList List_Initialize_Array(int* array, int size)
{
	LinkedList list;

	Node* new_node = create_node(array[0]);
	Node* old_node = new_node;
	list.head = new_node;
	list.tail = new_node;
	list.length = 1;
	for (int i = 1; i < size; i++)
	{
		old_node = list.tail;
		new_node = create_node(array[i]);
		list.tail->next = new_node;
		list.tail = new_node;
		if (i == 1)
		{ 
			list.head->next = new_node;
			list.tail->prev = list.head;
		}
		else {
			list.tail->prev = old_node;
		}
		list.length++;
	}
	
	return list;
}

LinkedList List_Initialize(int value)
{
	LinkedList list;
	Node* new_node = create_node(value);
	Node* old_node = new_node;
	list.head = new_node;
	list.tail = new_node;
	list.length = 1;
	return list;
}

void List_Traverse(LinkedList list)
{
	Node* current = list.head;
	while (current != NULL)
	{
		printf("%d ", current->data);
		current = current->next;
	}
}

int List_GetLength(LinkedList list)
{
	return list.length;
}

void List_Insert_Start(LinkedList* list, int value)
{
	Node* new_node = create_node(value);
	if (new_node != NULL)
	{
		list->head->prev = new_node;
		new_node->next = list->head;
		list->head = new_node;
		list->length++;
	}
}

void List_Insert_Index(LinkedList* list, int index, int value)
{
	if (index < 0 || index > list->length)
	{
		printf("Error: Invalid index\n");
		return;
	}
	if (index == 0) return List_Insert_Start(list, value);
	if (index == list->length) return List_Insert_End(&list, value);
	Node* new_node = create_node(value);
	Node* current = list->head;
	for (int i = 0; i < index - 1; ++i)
	{
		current = current->next;
	}
	new_node->next = current->next;
	current->next = new_node;
	new_node->prev = current;
	list->length++;
}

void List_Insert_End(LinkedList* list, int value)
{
	Node* new_node = create_node(value);
	if (new_node != NULL)
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
		list->length++;
	}
}

int List_Dequeue(LinkedList* list)
{
	if (list->head == NULL)
	{
		printf("Error: List is empty\n");
		return -1;
	}
	Node* temp = list->head;
	int value = temp->data;
	list->head = list->head->next;
	list->head->prev = NULL;
	free(temp);
	list->length--;
	return value;
}

int List_Pop(LinkedList* list)
{
	if (list->head == NULL)
	{
		printf("Error: List is empty\n");
		return -1;
	}
	Node* temp = list->tail;
	int value = temp->data;
	list->tail = list->tail->prev;
	list->tail->next = NULL;
	free(temp);
	list->length--;
	return value;
}

int List_GetAtIndex(LinkedList list, int index)
{
	if (index < 0 || index >= list.length)
	{
		printf("Error: Invalid index\n");
		return -1;
	}

	Node* current = list.head;
	for (int i = 0; i < index; ++i)
	{
		current = current->next;
	}
	return current->data;
}

void List_Free(LinkedList* list) {
	Node* current = list->head;
	Node* next = current->next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	list->length = 0;
}