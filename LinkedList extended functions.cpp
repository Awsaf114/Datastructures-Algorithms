#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

#define NULL_VALUE -9999
#define SUCCESS_VALUE 9999

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
};

struct listNode * list;

struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

int insertFirst(int item) //insert at the beginning
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;

	if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
	return SUCCESS_VALUE ;
}

int deleteLast()
{
    if( list == 0 ){ return NULL_VALUE;}
    struct listNode *temp, *pre ;
    temp = tail ; //start at the end
    int a = temp->item;

    if (temp == list) //delete the first node
	{
		list = 0;
		tail = 0;
		free(temp) ;
		return a;
	}
	if(a!= NULL || list != 0){
	tail = temp->prev;
	temp->prev->next = 0;

	free(temp);

    return a;
	}
	else{
        return NULL_VALUE;
	}
}

struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
//	    cout<<temp->item<<endl;
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}

	return 0; //0 means invalid pointer in C, also called NULL value in C
}

void printListForward()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

void printListBackward()
{
  struct listNode * temp;
    temp = tail;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->prev;
    }
    printf("\n");

}

int deleteAfter(int item)
{
    struct listNode *previ;
	struct listNode * res = searchItem(item);
//	cout<<res->item<<endl;


    if(res == 0){ return NULL_VALUE ;}
    if( res->next!=0 ){
        previ = res;
        res = res->next;
        if(res->next == 0){
          tail = previ;
          previ->next = res->next;

        }
        else{
        previ->next = res->next;
        res->next->prev = previ;
        }
        free(res);
        return SUCCESS_VALUE ;
    }
    else{

        return NULL_VALUE ;
    }
}

int deleteBefore(int item)
{
    struct listNode *previ;

    if(item == NULL_VALUE)
    {
        if(deleteLast() == NULL_VALUE){
                return NULL_VALUE;
        }
        return SUCCESS_VALUE ;
    }
	struct listNode * res = searchItem(item);

    if(res == 0){ return NULL_VALUE ;}

    if( res->prev !=0 ){
        previ = res;
        res = res->prev;
        if(res->prev == 0){
          list = previ;
          previ->prev = res->prev;

        }
        else{
            previ->prev = res->prev;
            res->prev->next = previ;

        }
        free(res);
        return SUCCESS_VALUE ;
    }
    else{

        return NULL_VALUE ;
    }

}

int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Print forward. 5. Print backward. 6. exit. 7. deleteAfter 8.deleteBefore\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }
        else if(ch==2)
        {
            int item = deleteLast();
            if(item!=NULL_VALUE)
            {
                printf("Deleted: %d\n", item);
            }
            else{
               printf("List Empty\n");
            }
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            printListForward();
        }
        else if(ch==5)
        {
            printListBackward();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch == 7){
            int item;
            scanf("%d", &item);
            if(deleteAfter(item) == SUCCESS_VALUE){
                cout<<"Delete Successful"<<endl;
            }
            else{
                cout<<"No item exists"<<endl;
            }
        }
        else if(ch == 8){
            int item;
            scanf("%d", &item);
            if(deleteBefore(item) == SUCCESS_VALUE){
                cout<<"Delete Successful"<<endl;
            }
            else{
                cout<<"No item exists"<<endl;
            }
        }
    }

}

