#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;


class HeapItem
{
public:
	char data; //actual data that is stored
	float key; //key value of the data, heap is constructed based on key

	HeapItem *left;
	HeapItem *right;

	HeapItem(){
        left = 0;
        right = 0;
	}
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
	HeapItem ** A; //stores heap items, e.g., nodes
	int heapLength;

	MinHeap(int n) //constructor
	{
	    //MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
        A =(HeapItem**)malloc(n* sizeof(HeapItem*));
		//*A = new HeapItem[n];
		heapLength=0;
	}

	~MinHeap() //destructor
	{
		if(A) delete [] A;
		A = 0; //set to NULL after deletion
	}

	void internalNode(char data , HeapItem *x , HeapItem *y){
	    heapLength++;
        A[heapLength]->data = data;
        A[heapLength]->key = x->key+y->key;

        if(x->key > y->key){
            A[heapLength]->left = new HeapItem();
            A[heapLength]->left = x;

        }
        else{
            A[heapLength]->left = new HeapItem();
            A[heapLength]->left = x;

        }

        buHeapify(heapLength);

	}

	HeapItem * makeNode(char data , float key)
    {
        HeapItem * node ;
        node = (HeapItem *)malloc(sizeof(HeapItem));
        node->data = data;
        node->key = key;
        node->left = 0;
        node->right = 0;
        return node;
    }



    void insertItem(char data, float key)
    {
        heapLength++;
        HeapItem * newNode = makeNode(data , key);

        A[heapLength] = newNode;
        buHeapify(heapLength);
    }

    HeapItem* removeMin()
	{
        printf("Remove");
	    if(Empty()){
            printf("Heap is empty");
            return A[0];
	    }
	    HeapItem *t = A[1];
	    //printf("\n%c %d\n",t->data , A[1]->key );
	    A[1] = A[heapLength];

	    heapLength--;
	    heapify(1);
	    //printf("\n%c %d\n",t->data , t->key );

	    return t;

	}

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
			else if( A[l]->key < A[r]->key )
				smallest = l;
			else
				smallest = r;

			if(A[i]->key <= A[smallest]->key)
				break;	//we are done heapifying
            else
			{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem *t;
				t=A[i];
				A[i]=A[smallest];
//				map[A[i].data]=i;
				A[smallest]=t;
//				map[A[smallest].data]=smallest;
				i=smallest;
			}

		}
	}

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


			if(A[i]->key >= A[par]->key)
				break;	//we are done heapifying
            else
			{
                //swap nodes with smallest parent, adjust map array accordingly
				HeapItem *t;
				t=A[i];
				A[i]=A[par];
//				map[A[i].data]=i;
				A[par]=t;
//				map[A[par].data]=par;
				i=par;
			}

		}

	}
    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%c,%.2f)", A[i]->data, A[i]->key);
        }
        printf("\n");
    }

	bool Empty()
	{
		if(heapLength==0)return true;
		else return false;
	}

	void Huffman(int n){

        for(int i=0 ; i<n-1 ; i++){
        HeapItem *t1 = A[1];
        A[1] = A[heapLength];
        //free(A[heapLength]);
        heapLength--;
        heapify(1);
        //printHeap();
        //printf("%c %f",t1->data , t1->key);
        HeapItem *t2 = A[1];
        A[1] = A[heapLength];

        heapLength--;
        heapify(1);
        //printHeap();
//        printf("%c %f\n",t1->data , t1->key);
//        printf("%c %f\n",t2->data , t2->key);

        heapLength++;

        HeapItem * newNode = makeNode('$' , t1->key+t2->key);
        A[heapLength] = newNode;


        if(t1->key > t2->key){
//            HeapItem * newNode1 = makeNode(t1->data , t1->key);
            A[heapLength]->right = t1;
//            HeapItem * newNode = makeNode(t2->data , t2->key);
            A[heapLength]->left = t2;

        }
        else{
//            HeapItem * newNode1 = makeNode(t2->data , t2->key);
            A[heapLength]->right = t2;
//            HeapItem * newNode = makeNode(t1->data , t1->key);
            A[heapLength]->left = t1;

        }

        buHeapify(heapLength);
       // printHeap();
        }
        printf("\nHuffman Code : \n" );
        int a[10000] , i=0;
        printInOrder(A[1] , a , i);

      }

	void printInOrder(HeapItem * node , int a[] , int n)
    {
        if(node==0 ) return ;

        //print left sub-tree
        a[n] = 0;
        printInOrder(node->left , a, n+1);


        if(node->data != '$'){
            //print item
            printf("%c :",node->data );
            for(int i=0 ; i<n ; i++){
                printf("%d ",a[i]);
            }
            printf("\n");

        }
        //print right sub-tree
        a[n]=1;
        printInOrder(node->right,a,n+1);
    }

};




int main(){

    int n;
    cin>>n;
    char c;
    float freq;

    MinHeap heap(n+1);

//    cout<<"Hello"<<endl;

    for(int i=0 ; i<n ; i++){

   cin>>c>>freq;
    heap.insertItem(c, freq);
//    heap.insertItem('b', 13);
//    heap.insertItem('f', 5);
//    heap.insertItem('e', 9);
//    heap.insertItem('d', 16);
//    heap.insertItem('a', 45);
    //heap.printHeap();
    }


    heap.Huffman(n);
   // heap.printHeap();
 //   heap.HuffmanDecode();



    return 0;

}
