#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
	int  value;  // value (int) of this list item 
	struct DLListNode *prev;
	// pointer previous node in list
	struct DLListNode *next;
	// pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
	int  size;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList *newDLList()
{
	DLList *L;

	L = malloc(sizeof (struct DLList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

//inserts nodes to the end of a list
//Complexity: Constant time
void insertList(DLList *mylist, int num){
	DLListNode *newNode;
	newNode = newDLListNode(num);
	if (mylist ->first==0){
		mylist ->first = mylist ->last = newNode;
		mylist ->size++;
	} else {
		mylist ->last ->next = newNode;
		newNode ->prev = mylist ->last;
		mylist ->last = newNode;
		mylist ->size++;
	}
}

// create a DLList from a text file
// Complexity: We traverse the list once so O(n)
DLList *CreateDLListFromFileDlist(const char *filename)
{
 // get data using getc(), it will work for file and stdin.
	int num;	
	DLList *mylist;
	mylist = newDLList();
	if (strcmp(filename,"stdin")){
		FILE *fp;
		fp = fopen(filename, "r");
		assert(fp!=NULL);
		while (fscanf(fp,"%d",&num) > 0){
			insertList(mylist,num);
		}
		fclose(fp);
	} else {
		char *input=NULL;
		unsigned int inputSize = 20;
		while(getline(&input,&inputSize,stdin)!=1)
		{	
			sscanf(input,"%d",&num);
			insertList(mylist,num);
		}		
	}		
	return mylist;
}



// clone a DLList
// Complexity: We traverse the list once so O(n)
DLList *cloneList(DLList *u)
{
	DLList *mylist;
	DLListNode *node, *newNode, *currentNode;
	int i;
	mylist = newDLList();
	for (i=0, node = u->first;i<u->size; node = node->next, i++){
		insertList(mylist,node->value);
	}
	return mylist;
}

// compute the union of two DLLists u and v
// Complexity: traverse the lists m times for n elements O(m.n)
// where m size of u and n is size of v
DLList *setUnion(DLList *u, DLList *v)
{
	DLList *myList;
	DLListNode *uNode, *vNode;
	int i,j,common;
	myList = cloneList(u);
	for (i=0, vNode = v->first;i<v->size; vNode = vNode->next, i++){
		common = 0;
		for (j=0, uNode = u->first;j<u->size;uNode = uNode->next, j++){
			if(vNode->value == uNode->value){
				common = 1;
				break;
			}
		}
		if (common){
			continue;
		}
		DLListNode *newNode = newDLListNode(vNode->value);
		myList->last->next = newNode;
		newNode->prev = myList->last;
		myList ->last = newNode; 
		myList -> size++;
	}
	return myList;
}

// compute the insection of two DLLists u and v
// Complexity: traverse the lists m times for n elements O(m.n)
// where m size of u and n is size of v
DLList *setIntersection(DLList *u, DLList *v)
{
  	DLList *myList;
	DLListNode *uNode, *vNode, *currentNode, *newNode;
	int i,j;
	myList = newDLList();
	for (i=0, vNode = v->first;i<v->size; vNode = vNode->next, i++){
		for (j=0, uNode = u->first;j<u->size;uNode = uNode->next, j++){
			if(vNode->value == uNode->value){
				insertList(myList,vNode->value);
			}
		}
	}
	return myList;
}

// free up all space associated with list
// Complexity: We traverse the list once so O(n)
void freeDLList(DLList *L)
{
	assert(L!=NULL);
	DLListNode *node, *temp;
	node = L->first;
	while(node!=NULL){
		temp = node->next;
		free(node);
		node = temp;
	}
	free(L);

}


// display items of a DLList
// Complexity: We traverse the list once so O(n)
void printDLList(DLList *u)
{
	DLListNode *node;
	int i;
	for(i=0,node=u->first;i<u->size;node = node ->next,i++){
		printf("%d\n",node->value);
	}
}


int main()
{
 DLList *list1, *list2, *list3, *list4;
 list1=CreateDLListFromFileDlist("File_1.txt");
 printDLList(list1);

 list2=CreateDLListFromFileDlist("File_2.txt");
 printDLList(list2);

 list3=setUnion(list1, list2);
 printDLList(list3);

 list4=setIntersection(list1, list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 printf("please type all the integers of list1\n");
 list1=CreateDLListFromFileDlist("stdin");

 printf("please type all the integers of list2\n");
 list2=CreateDLListFromFileDlist("stdin");

 list3=cloneList(list1);
 printDLList(list3);
 list4=cloneList(list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 return 0; 
}
