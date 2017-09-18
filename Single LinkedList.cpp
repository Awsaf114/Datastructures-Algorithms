#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) ///insert at the beginning of the linked list
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; ///point to previous first node
	list = newNode ; ///set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;
}


struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
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

int insertLast(int item)
{
    struct listNode * newNode , *temp;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    temp = list;
    newNode->item = item;
    newNode->next = 0;
    if(list == 0){
        list = newNode;
        return SUCCESS_VALUE ;
    }
    while(temp->next !=0)
    {
        temp = temp->next;
    }

	temp->next = newNode ; ///point to previous first node
	 ///set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;

}

int insertBefore(int oldItem, int newItem)
{
    struct listNode * temp ,*prev;
    bool flag = true;
    temp = list ; //start at the beginning
    prev = temp;
    while (temp != 0)
    {
        if (temp->item == oldItem){
            flag = false;
            break;
        }
        prev = temp;
        temp = temp->next ; //move to next node
    }
    if(flag)
    {
       insertItem(newItem);
       return SUCCESS_VALUE ;
    }
    else{

    struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = newItem;

	newNode->next = temp;
	if(temp == list){
        list = newNode;
	}
	else{
	prev->next = newNode;
	}
    return SUCCESS_VALUE ;
    }

}

int deleteAfter(int item)
{
    struct listNode *prev;
	struct listNode * res = searchItem(item);
	prev = res;

    if(res==0 || res->next==0 ){
        return NULL_VALUE ;
    }
    else{
        res = res->next;
        prev->next = res->next;
        free(res);

        return SUCCESS_VALUE ;
    }

}

int deleteLast()
{
    struct listNode *temp, *prev ;
	temp = list ; //start at the beginning

	if (temp == 0){
        return NULL_VALUE ; //item not found to delete
    }
	while (temp->next != 0)
	{
		prev = temp;
		temp = temp->next ; //move to next node
	}

	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;

}



int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Print. 5. exit.\n");
        printf("6. Insert item at Last. 7. Insert before (olditem-newitem). \n");
        printf("8. Delete after item. 9. Delete Last item.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
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
            printList();
        }
        else if(ch==5)
        {
            break;
        }
        else if(ch == 6){
                int item;
                scanf("%d",&item);
                insertLast(item);
        }
        else if(ch == 7){
            int item , bef;
            scanf("%d%d",&item , &bef);

            insertBefore(item , bef);
        }
        else if(ch == 8){
            int item;
            scanf("%d",&item );
            deleteAfter(item);
        }
        else if (ch == 9){
            if(deleteLast() == SUCCESS_VALUE){
                cout<<"SUCCESS"<<endl;
            }
            else{
                cout<<"Item not found"<<endl;
            }
        }

    }

}
