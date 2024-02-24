#include "StrList.h"
#include <stdio.h>
#define TRUE 1
#define FALSE 0
/*
*	Node represents a node data structure
*/
typedef struct _node{
   	char* _data;
    struct _node * _next;
}Node;

/*
 * StrList represents a StrList data structure.
 */
struct _StrList {
	Node* _head;
    size_t _size;
};
typedef struct _StrList StrList;


/*
 * Allocates a new Node
 */
Node* Node_alloc(const char* data, Node* next) {
	Node* p= (Node*)malloc(sizeof(Node));
	if(data != NULL)
	{
		p->_data= (char*)malloc(sizeof((strlen(data)+1)*sizeof(char)));
		strcpy(p->_data,data);
	}
	p->_next= next;
	return p;
}

void Node_free(Node* node) {
	free(node->_data);
	free(node);
}

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc()
{
	StrList* p= (StrList*)malloc(sizeof(StrList));
	p->_head= NULL;
	p->_size= 0;
	return p;
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* StrList)
{
	if (StrList==NULL) return;
	Node* p1= StrList->_head;
	Node* p2;
	while(p1) {
		p2= p1;
		p1= p1->_next;
		Node_free(p2);
	}
	free(StrList);
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* StrList)
{
	return StrList->_size;
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* StrList, const char* data)
{
	if (StrList==NULL) return;
	Node* newNode = Node_alloc(data, NULL);

	if(StrList->_head==NULL)
	{
		StrList->_head = newNode;
	}
	else
	{
		Node* p1 = StrList->_head;
		while(p1->_next) {
			p1 = p1->_next;
		}
		p1->_next = newNode;
	}

	++(StrList->_size);
}

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList* StrList,
	const char* data,int index)
{
	if(StrList==NULL) return;
	
	if (index<StrList->_size)
	{
		Node* p1 = StrList->_head;
		if(index == 0)
		{
			Node* newNode = Node_alloc(data,StrList->_head);
			StrList->_head = newNode;
		}
		else
		{
			index-=1;
			while(p1 && index>=0)  {
				p1 = p1->_next;
				index--;
			}
			Node* newNode = Node_alloc(data,p1->_next);
			p1->_next = newNode;
		}
		++(StrList->_size);
	}
}

/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList)
{
	return StrList->_head->_data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList)
{
	const Node* p = StrList->_head;
	while(p) {
		printf("%s ",p->_data);
		p = p->_next;
	}
	printf("\n");
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* Strlist,int index)
{
	if(Strlist==NULL) return;
	if (index<Strlist->_size)
	{
		Node* p1= Strlist->_head;
		while(p1->_next && index>0)  {
			p1 = p1->_next;
			index--;
		}
		printf("%s\n",p1->_data);
	}
}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* Strlist)
{
	if(Strlist==NULL) return;
	Node* p1= Strlist->_head;
	int sum = 0;
	while(p1) {
		sum+=strlen(p1->_data);
		p1 = p1->_next;
	}
	return sum;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* StrList, const char* data)
{
	if(StrList==NULL) return;
	Node* p1= StrList->_head;
	Node* p2;
	int counter = 0;
	while(p1) {
		if(!strcmp(data,p1->_data)) counter++;
		p1 = p1->_next;
	}
	return counter;
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* StrList, const char* data)
{
	if(StrList == NULL) return;
	Node* p1 = StrList->_head;
	int index = 0;
	while(p1) {
		if(!strcmp(data, p1->_data))
		{
			p1 = p1 ->_next;
			StrList_removeAt(StrList, index);
		}
		else
		{
			p1 = p1->_next;
			index++;
		}
	}
}

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index)
{
	if(StrList==NULL) return;
	
	if (index<StrList->_size)
	{
		Node* p1 = StrList->_head;
		if(index == 0)
		{
			Node* newNode = StrList->_head;
			StrList->_head = StrList->_head->_next;
			Node_free(newNode);
		}
		else
		{
			index-=1;
			while(p1 && index>0)  {
				p1 = p1->_next;
				index--;
			}
			Node* newNode = p1->_next;
			p1->_next = p1->_next->_next;
			Node_free(newNode);
		}
		--(StrList->_size);
	}
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2)
{
	if(StrList1==NULL || StrList2==NULL) return;
	Node* p1 = StrList1->_head;
	Node* f1 = StrList2->_head;
	while(p1) {
		if(strcmp(f1->_data,p1->_data)) return 0;
		p1 = p1->_next;
		f1 = f1->_next;
	}
	return 1;
}

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* StrList)
{
	struct _StrList* clone = StrList_alloc();
	Node* p1 = StrList->_head;

	while(p1->_next) {
		p1 = p1->_next;
		StrList_insertLast(clone,p1->_data);
	}
	return clone;
}

/*
 * Reverces the given StrList. 
 */
void StrList_reverse( StrList* StrList)
{
	Node* previous = NULL;
	Node* current = StrList->_head;
	Node* next = NULL;

	while (current)
	{
		next = current->_next;
		current->_next = previous;
		previous = current;
		current = next;
	}
	StrList->_head = previous;
}

int cmpfunc (const void* a, const void* b) {

	return strcmp(((Node*)a)->_data,((Node*)b)->_data);
}
/*
 * Sort the given list in lexicographical order 
 */
void StrList_sort( StrList* StrList)
{
	Node* p1 = StrList->_head;
	Node** array = (Node**)malloc((StrList->_size)*sizeof(Node*));
	int i = 0;
	while(p1)
	{
		array[i++] = p1;
		p1=p1->_next; 
	}
	qsort(array, StrList->_size, sizeof(Node*), cmpfunc);

	StrList->_head=array[0];
	for(i = 0;i<StrList->_size-1;i++)
	{
		array[i]->_next = array[i+1];
	}
	array[StrList->_size-1]->_next=NULL;

	free(array);
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* StrList)
{
	struct _StrList* clone = StrList_clone(StrList);
	StrList_sort(clone);
	return(StrList_isEqual(StrList,clone));
}

