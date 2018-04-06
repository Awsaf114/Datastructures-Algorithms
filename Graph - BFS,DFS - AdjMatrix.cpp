#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0
#define GREY 1
#define BLACK -1


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


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges, count;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	int *color , *parent , *dist;
	int *discovery , *finish;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
    void dfs(int source); //will run bfs in the graph
    void visit(int source);
};


Graph::Graph(bool dir)
{
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
    for(int i=0;i<nVertices;i++)
    {
        color[i] = WHITE;
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    nEdges++;
    if(!directed) matrix[v][u] = 1;

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
    if(matrix[u][v] == 1){
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
                dist[i] = k;
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
    if(color[source] == BLACK){
        return;
    }
    discovery[source] = count;
    printf("%d ",source);
    color[source] = GREY;
    for( int i = 0 ; i<nVertices ; i++){
        if(matrix[source][i] && color[i]== WHITE){
            count++;
            visit(i);
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
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2. Remove edge 3. isEdge\n");
        printf("4. Degree . 5. Print Graph  6. Exit.\n");
        printf("7. Common Adjacent. 8. BFS  9. DFS. 10. Shortest Path\n");

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
    }

}
