#include<stdio.h>
#include<iostream>

using namespace std;

#define MAX_HEAP_SIZE 100000

#define MAXREAL 999999.0

class HeapItem
{
public:
	int data; //actual data that is stored
	float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
	HeapItem * A; //stores heap items, e.g., nodes
	int heapLength;
	int * map;

	MinHeap() //constructor
	{
		A = new HeapItem[MAX_HEAP_SIZE];
		map = new int[MAX_HEAP_SIZE];
		map[0] = 0;
		map[1] = 0;

		heapLength=0;
	}

	~MinHeap() //destructor
	{
		if(map) delete [] map;
		if(A) delete [] A;
		map = 0; //set to NULL after deletion
		A = 0; //set to NULL after deletion
	}

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
	void initialize(int v[], int n)
	{
		heapLength = n;
		for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
		{
			A[i+1].data = v[i];
			A[i+1].key = MAXREAL;
			map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
		}
	}

	//this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, float key)
    {
        if(data<0){
            printf("Cannot input node");
            return;
        }
//        cout<<map[data]<<endl;
        if(map[data]!=0)
        {
            cout<<"Node Already exists"<<endl;
            return;
        }

        heapLength++;
        A[heapLength].data = data;
        A[heapLength].key = key;
        map[data] = heapLength;


        buHeapify(heapLength);
    }

    //this function removes (and returns) the node which contains the minimum key value
	HeapItem removeMin()
	{
	    if(Empty()){
            printf("Heap is empty");
            return A[0];
	    }
	    HeapItem t = A[1];
	    A[1] = A[heapLength];
	    heapLength--;
	    map[t.data] = 0;
	    heapify(1);
	    return t;

	}


    //The function updates the key value of an existing data
    //stored in the heap
	//Note that updates can result in an increase or decrease of key value
	//Call to heapify or buheapify is required
	void updateKey(int data, float key)
	{
	    int i = map[data];
//	    cout<<i<<endl;
        if(key <A[i].key){
            A[i].key = key;
            buHeapify(i);
        }
        else{
            A[i].key = key;
            heapify(i);
        }

	}


    //This function returns the key value of a data stored in heap
	float getKey(int data)
	{
		int i = map[data];
		return A[i].key;
	}

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
	void heapify(int i)
	{

		int l,r,smallest;
		while(1)
		{
		   // printf("%d  %d  %f  %d\n",i ,A[i].data , A[i].key ,map[A[i].data] );

			l=2*i;      //left child index
			r=2*i+1;    //right child index
			smallest=i;

			if(l>heapLength && r>heapLength)
				break; //nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

			if(A[i].key <= A[smallest].key)
				break;	//we are done heapifying
            else
			{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[smallest];
				map[A[i].data]=i;
				A[smallest]=t;
				map[A[smallest].data]=smallest;
				i=smallest;
			}

		}
	}

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
	void buHeapify(int i)
	{
	    int par;
		while(1)
		{
		   // printf("%d  %d  %f  %d\n",i ,A[i].data , A[i].key ,map[A[i].data] );
            if(i%2 == 0){
                par = i/2;
            }
            else{
                par = (i-1)/2;
            }
            if(i == 1)
                return;


			if(A[i].key >= A[par].key)
				break;	//we are done heapifying
            else
			{
                //swap nodes with smallest parent, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[par];
				map[A[i].data]=i;
				A[par]=t;
				map[A[par].data]=par;
				i=par;
			}

		}

	}



	/*
	void buHeapify(int i)
	{
	    if(i == 1)
            return;

	    //printf("%d  (%d - %f)  %d\n",i ,A[i].data , A[i].key ,map[A[i].data] );
	    if( i%2 !=0){
            buHeapify(i-1);
            if(A[i].key < A[(i-1)/2].key){
                map[A[i].data] = (i-1)/2;
                map[A[(i-1)/2].data] = i;
                HeapItem t = A[i];
                A[i] = A[(i-1)/2];
                A[(i-1)/2] = t;


                //cout<<A[i].key<<" - "<<map[A[i].data]<<endl;
            }

            buHeapify((i-1)/2);

	    }
	    else{
            buHeapify(i-1);
            if(i == 1)
                return;
            if(A[i].key < A[i/2].key){
                map[A[i].data] = i/2;
                map[A[i/2].data] = i;

                HeapItem t = A[i];
                A[i] = A[i/2];
                A[i/2] = t;

                //cout<<A[i].key<<" - "<<map[A[i].data]<<endl;
            }
            buHeapify(i/2);
	    }

	}
	*/

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%d,%.2f) %d", A[i].data, A[i].key,map[A[i].data]);
        }
        printf("\n");
    }

	bool Empty()
	{
		if(heapLength==0)return true;
		else return false;
	}
};


int main()
{
    int choice;
    int data;
    float key;
    MinHeap heap;
    bool exit = false;

//    heap.insertItem(23, 4);
//    heap.insertItem(86, 2);
//    heap.insertItem(34, 3);
//    heap.insertItem(54, 5);
//    heap.insertItem(67, 1);


    while(!exit)
    {
        printf("1. Insert(data-key) 2. RemoveMin 3.Update 4. Print 5. Exit.\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            scanf("%d%f",&data,&key);
            heap.insertItem(data, key);
            heap.printHeap();
            break;
        case 2:
            HeapItem item;
            item = heap.removeMin();
            printf("Removed: (%d,%.2f)\n", item.data, item.key);
            heap.printHeap();
            break;
        case 3:
            scanf("%d%f",&data,&key);
            heap.updateKey(data,key);
            heap.printHeap();
            break;
        case 4:
            heap.printHeap();
            break;
        case 5:
            exit = true;
            break;

        }
    }
    return 0;
}
