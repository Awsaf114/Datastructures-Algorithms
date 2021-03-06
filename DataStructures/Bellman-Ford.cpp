#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

#define MAX_HEAP_SIZE 100000

#define MAXREAL 999999.0

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;

}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Heap class begins **********************
class HeapItem
{
public:
	int data; //actual data that is stored
	int key; //key value of the data, heap is constructed based on key
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
    void insertItem(int data, int key)
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
	void updateKey(int data, int key)
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
	int getKey(int data)
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

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%d,%d) %d", A[i].data, A[i].key,map[A[i].data]);
        }
        printf("\n");
    }

	bool Empty()
	{
		if(heapLength==0)return true;
		else return false;
	}
};
//*************** Heap class ends *******************

//****************Dynamic ArrayList class based************************
class GraphNode{
public:
int data;
int weight;
};

class ArrayList
{
	GraphNode * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item , int w) ;
	void removeItem(int item) ;
	void removeItemAt(int pos);
	GraphNode getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new GraphNode[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem , int w)
{
	GraphNode * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new GraphNode[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length].data = newitem ; //store new item
	list[length].weight = w;
	length++ ;
}

int ArrayList::searchItem(int item) /// returns the position of the item being searched
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i].data == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


GraphNode ArrayList::getItem(int position)
{

//   if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("(%d,%d)", list[i].data +1 , list[i].weight);
//    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ,totalEdges ,  count;
	bool directed ;
	ArrayList  * adjList ;
	int *color , *parent , *dist;
	int *discovery , *finish;

	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = true);
	~Graph();
	void setnVertices(int n , int m);
	void addEdge(int u, int v , int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(int source); //will run dfs in the graph
	void visit(int source);
    void MST_Prim(int root);
    void printMST();
    void Bellman_Ford(int source);
};


void Graph::MST_Prim( int root){
    MinHeap heap;

    for(int i=0 ; i< nVertices ; i++ )
    {
        heap.insertItem( i , INFINITY );
    }
    heap.updateKey(root , 0);
    parent[root] = NULL_VALUE;
    while(!heap.Empty()){
        HeapItem item;
        item = heap.removeMin();

    for(int i = 0 ; i< adjList[item.data].getLength() ; i++){
        GraphNode node = adjList[item.data].getItem(i);
        if(  heap.map[node.data] !=0  && node.weight < heap.getKey(node.data)){
            parent[node.data] = item.data;
            heap.updateKey(node.data , node.weight);
        }

    }

}
  printMST();


}

void Graph::printMST(){
    int count = 0;
    cout<<endl<<"Edges of Minimum spanning tree are:"<<endl;

    for(int i=1 ; i< nVertices ; i++){
       count +=  adjList[i].getItem(adjList[i].searchItem(parent[i])).weight;
    printf("%d %d \n", parent[i]+1 , i+1 );

    }

    cout<<count;
}

void Graph::Bellman_Ford(int source){
    bool flag = true;

    for(int i=0 ; i<nVertices ; i++){
        dist[i] = INFINITY;
        parent[i] = -10000;
    }
    dist[source] = 0;


    for(int i = 0 ; i< nVertices ; i++){

        for(int j = 0 ; j< nVertices ; j++){
            for(int k =0 ; k< adjList[j].getLength() ; k++ )
            {
           //     cout<<dist[j]<<" ";
                if(dist[adjList[j].getItem(k).data] > dist[j] + adjList[j].getItem(k).weight){

                    parent[adjList[j].getItem(k).data] = j;
                    dist[adjList[j].getItem(k).data] = dist[j] + adjList[j].getItem(k).weight;

                }

            }

        }
       // cout<<endl;

    }

    for(int j = 0 ; j< nVertices ; j++){
            for(int k =0 ; k< adjList[j].getLength() ; k++ )
            {
                if(dist[adjList[j].getItem(k).data] > dist[j] + adjList[j].getItem(k).weight){

                     //d[i] = d[adjList[i].getItem(k).data] + adjList[i].getItem(k).data;
                    flag = false;
                    break;
                }

            }

    }

    cout<<"V\t\tV.d \t\tV.pi "<<endl;

    for(int i=0 ; i<nVertices ; i++){
        cout<<i+1<<"\t\t"<<dist[i]<<"\t\t"<<parent[i]+1<<endl;
    }
    if(flag){
        cout<<"Negative cycle: NO";
    }
    else{
        cout<<"Negative cycle: YES";
    }


}


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	totalEdges = 0;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	color =0; //define other variables to be initialized
    parent=0;
    dist=0;
    discovery=0;
    finish=0;
    count = 1;
}

void Graph::setnVertices(int n , int m)
{
    color = new int[nVertices];
	parent = new int[nVertices];
	dist = new int[nVertices];
	discovery = new int[nVertices];
	finish = new int[nVertices];

	this->nVertices = n ;
	this->totalEdges = m;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v , int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || totalEdges== nEdges) return; //vertex out of range

    this->nEdges++ ;
	adjList[u].insertItem(v , w) ;
	if(!directed) adjList[v].insertItem(u , w) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges-- ;
	adjList[u].removeItem(v) ;
	if(!directed) adjList[v].removeItem(u) ;
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range
    if(adjList[u].searchItem(v)!= NULL_VALUE){
        return true;
    }
    return false;
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices ) return 0; //vertex out of range

    return adjList[u].getLength();


}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    int l,r;
    l = adjList[u].getLength();
    r = adjList[v].getLength();
    if(l>r){
        for(int j=0 ; j<r ;j++){
            for(int i =0 ; i<l ;i ++){
                if(adjList[u].getItem(i).data == adjList[v].getItem(j).data)
                    return true;
            }
        }
    }
    else{
        for(int j=0 ; j<l ;j++){
            for(int i =0 ; i<r ;i ++){
                if(adjList[u].getItem(j).data == adjList[v].getItem(i).data)
                    return true;
            }
        }

    }
    return false;
}

void Graph::bfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    int k=1;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        bool flag = true;
        source = q.dequeue();
        printf("%d  ",source);
        color[source]= 3;
        for(int i=0; i< adjList[source].getLength() ; i++){
            int idx = adjList[source].getItem(i).data;
            if(color[idx]== 1 ){
                color[idx] = 2;
                dist[idx] = k;
                q.enqueue(idx);
                parent[idx] = source;
                flag = false;
            }
        }
        if(!flag){
        k++;

        }

    }
    printf("\n");
}

void Graph::visit(int source){
    if(color[source] == 3){
        return;
    }
    discovery[source] = count;
    printf("%d ",source);
    color[source] = 2;
    for( int i = 0 ; i<adjList[source].getLength() ; i++){
        int idx = adjList[source].getItem(i).data;
        if(color[idx]== 1){
            count++;
            visit(idx);
        }
    }
    color[source] = 3;
    count++;
    finish[source] = count;
    return;
}
void Graph::dfs(int source=0)
{
    count = 1;
    for(int i = 0; i<nVertices ; i++){
        color[i] = WHITE;
    }
    visit(source);

    for(int i = 0; i<nVertices ; i++){
        if(color[i] == WHITE){
            visit(i);
        }
    }

}

int Graph::getDist(int u, int v)
{

    bfs(u);
    for(int i=0 ;i<nVertices ; i++){
        if(i == v){
            return dist[i];
        }
    }
    return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i+1);
        adjList[i].printList();
//        for(int j=0; j<adjList[i].getLength();j++)
//        {
//            printf(" %d", adjList[i].getItem(j));
//        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(adjList) delete [] adjList;
    if(color) delete [] color;
    if(parent) delete [] parent;
    if(dist) delete [] dist;
    if(discovery) delete [] discovery;
    if(finish) delete [] finish;

    adjList = 0 ;
    color = 0 ;
    parent = 0 ;
    dist = 0 ;
    discovery = 0 ;
    finish = 0 ;

    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n , m ,u,v,w , s;

    Graph g;
    printf("Enter number of vertices & edges: ");
    scanf("%d%d", &n , &m);
    g.setnVertices(n , m);


    for(int i =0 ; i<m ; i++){
        scanf("%d%d%d", &u, &v , &w);
        g.addEdge(u-1, v-1 , w);

    }
    g.printGraph();
    printf("Enter Source: ");

    scanf("%d", &s);

    g.Bellman_Ford(s-1);

}
