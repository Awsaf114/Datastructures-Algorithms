#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0
#define GREY 1
#define BLACK -1

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



//*************** Heap class ends *******************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges, count , edges;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	int *color , *parent , *dist , *key;
	int *discovery , *finish;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v , int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
    void dfs(int source); //will run bfs in the graph
    void visit(int source);
    bool isconnected(int src = 0);
    void MST_Prim(int root);
};


void Graph::MST_Prim( int root){
    MinHeap heap;

    for(int i=0 ; i< nVertices ; i++ )
    {
        heap.insertItem( i , INFINITY );
    }
    heap.updateKey(root , 0);
    while(!heap.Empty()){
        HeapItem item;
        item = heap.removeMin();

    for(int i = 0 ; i< nVertices ; i++){

        if(matrix[item.data][i]>0 && matrix[item.data][i]< key[i] )
        {
            key[i] = matrix[item.data][i];

        }
    }

}
  for(int i=0 ; i<nVertices ; i++){
        cout<<key[i]<<" -"<<i<<endl;
    }

}




bool Graph::isconnected(int src)
{
    bfs(src);
    if(directed){
    for(int i=0 ;i<nVertices ; i++){
        for(int j=0 ;i<nVertices ; i++){
            if(matrix[i][j] == 1){
               matrix[j][i] = 1;
            }
        }
    }

    }
    for(int i=0 ;i<nVertices ; i++){
        if(dist[i] == INFINITY){
            return false;
        }
    }

    return true;
}

Graph::Graph(bool dir)
{
    key = 0;
    edges = 0;
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	color =0; //define other variables to be initialized
    parent=0;
    dist=0;
    discovery=0;
    finish=0;
    count = 1;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
	color = new int[nVertices];
	parent = new int[nVertices];
	dist = new int[nVertices];
	discovery = new int[nVertices];
	finish = new int[nVertices];
    matrix = new int*[nVertices];
    key = new int [nVertices];
    for(int i=0;i<nVertices;i++)
    {

        key[i] = INFINITY;
        color[i] = WHITE;
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v , int w = 1)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = w;
    nEdges++;
    if(!directed) matrix[v][u] = w;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 0;
    nEdges--;
    if(!directed) matrix[v][u] = 0;

}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if(matrix[u][v] >= 1){
        return true;
    }
    else{
        return false;
    }

    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices) return 0;
    int count =0;
    for(int i =0 ; i<nVertices ; i++){
        if(matrix[u][i]==1){
            count++;
        }
    }
    return count;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int i=0 ; i<nVertices ; i++){
        if(matrix[u][i]==1 && matrix[v][i]==1){
            return true;
        }
    }
    return false;



}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
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
        color[source]= BLACK;
        for(int i=0; i<nVertices ; i++){

            if(matrix[source][i]==1 && color[i]== WHITE ){
                color[i] = GREY;
                dist[i] = dist[source] +1;
                q.enqueue(i);
                parent[i] = source;
                 flag = false;
            }
        }
        if(!flag)
            k++;

    }
    printf("\n");

}
void Graph::visit(int source){

    int cntgrey =0;
    if(color[source] == BLACK){
        return;
    }
    discovery[source] = count;
    printf("%d ",source);
    color[source] = GREY;
    for( int i = 0 ; i<nVertices ; i++){
        if(matrix[source][i] && color[i]== GREY){
            cntgrey++;
     //       printf("%d-----",cntgrey);
        }
        if(matrix[source][i] && color[i]== WHITE){
            count++;
            visit(i);
        }
        if(cntgrey>1){
           removeEdge(i, source);

        }
    }
    color[source] = BLACK;
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
            addEdge(i , i-1);
            edges++;
            visit(i);
        }
    }
    if(edges>0){

    printf("\nGraph does not have a spanning tree\nEdges needed : %d",edges);
    printGraph();

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
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return INFINITY ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(matrix) delete [] matrix;
    if(color) delete [] color;
    if(parent) delete [] parent;
    if(dist) delete [] dist;
    if(discovery) delete [] discovery;
    if(finish) delete [] finish;

    matrix = 0 ;
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
    int n , m;
    Graph g;
    //Graph g(true);

    scanf("%d %d", &n , &m);
    g.setnVertices(n);

     int u, v , w;

    for(int i =0 ; i<m ; i++){
        scanf("%d%d%d", &u, &v , &w);
        g.addEdge(u, v , w);

    }

    cout<<"Prim called";
    g.MST_Prim(0);



/*
    while(1)
    {
        printf("1. Add edge. 2. Remove edge 3. isEdge\n");
        printf("4. Degree . 5. Print Graph  6. Exit.\n");
        printf("7. Common Adjacent. 8. BFS  9. DFS. 10. Shortest Path 11. Connected\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u ,v);

        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u ,v)){
                printf("%d-%d is an edge\n",u,v);
            }
            else{
                printf("%d-%d is not an edge\n",u,v);
            }

        }
        else if(ch==4)
        {
            int u;
            scanf("%d", &u);
            int deg = g.getDegree(u);
            printf("Vertex %d has degree %d\n",u, deg);
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u, v)){
                printf("%d and %d has common adjacent\n",u,v);
            }
            else{
                printf("%d and %d does not have common adjacent\n",u,v);
            }
        }
        else if(ch==8)
        {
            int u;
            scanf("%d", &u);
            g.bfs(u);
        }
        else if(ch==9)
        {
            int u;
            scanf("%d", &u);
            g.dfs(u);
            printf("\n");
        }
        else if(ch==10)
        {
            int u ,v;
            scanf("%d%d", &u,&v);
            int x = g.getDist(u ,v);
            if(x!= INFINITY){
                printf("Shortest path is => %d\n",x);
            }
            else{
                printf("Graph is not connected\n");
            }
        }
        else if(ch==11)
        {
            if(g.isconnected(0)){
                printf("TRUE\n");
            }
            else{
                printf("Graph is not connected\n");
            }



        }

    }
*/
    return 0;
}
