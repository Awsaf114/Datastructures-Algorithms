#include<bits/stdc++.h>
#define NULL_VALUE -999999
#define WHITE 0
#define GREY 1
#define BLACK -1

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;




//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges,totalEdges,  count;
	bool directed ;
	vector<vii> adjList;
	int *color , *parent , *dist;
	int *discovery , *finish;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n , int m);
	void addEdge(int u, int v , int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	bool bfs(vector<vii> graph, int source , int t); //will run bfs in the graph
    void dfs(int source); //will run bfs in the graph
    void visit(int source);
    int Ford_Fulkerson(int s , int t);
    bool pathexists(vector<vii> resGraph , int s, int t);
};

Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
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
	this->nVertices = n ;
	this->totalEdges = m;

	//allocate space for the matrix
	color = new int[nVertices];
	parent = new int[nVertices];
	dist = new int[nVertices];
	discovery = new int[nVertices];
	finish = new int[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        color[i] = WHITE;
        vii vec;
        adjList.push_back(vec);
    }

}

int Graph::Ford_Fulkerson(int s , int t){
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    vector<vii> rGraph; // Residual graph where rGraph[i][j] indicates
                     // residual capacity of edge from i to j (if there
                     // is an edge. If rGraph[i][j] is 0, then there is not)
    for(int i = 0 ; i<nVertices ; i++){
        vii vec;
        rGraph.push_back(vec);
    }

    for (u = 0; u < nVertices; u++){
        for (v = 0; v < adjList[u].size() ; v++){
          rGraph[u].push_back(make_pair(adjList[u][v].first , adjList[u][v].second )) ;
        }
    }



    int max_flow = 0;  // There is no flow initially
    // Augment the flow while tere is path from source to sink
    while (bfs( rGraph , s, t))
    {

        int path_flow = INT_MAX;

        for (v=t; v!=s; v= parent[v])
        {
            u = parent[v];
            int index;
            for(int i = 0 ; i< rGraph[u].size() ; i++){
                if(rGraph[u][i].first == v){
                    index = i;
                    break;
                }
            }
            path_flow = min(path_flow, rGraph[u][index].second);
        }

        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];

            for(int i = 0 ; i< rGraph[u].size() ; i++){
                if(rGraph[u][i].first == v){
                    rGraph[u][i].second -= path_flow;
                    break;
                }
            }
            int flag = false;
            int idx;
            for(int i = 0 ; i< rGraph[v].size() ; i++){
                if(rGraph[v][i].first == v){
                    rGraph[v][i].second += path_flow;
                    flag = true;
                    idx = i;
                }
            }
            if(!flag){
                rGraph[v].push_back(make_pair(u , path_flow));
            }

        }

        // Add path flow to overall flow
        max_flow += path_flow;

    }

    ///  Print Graph
    for(int i=0;i<nVertices ;i++)
    {
        printf("%d:", i+1 );
        for(int j=0; j<(int)adjList[i].size();j++)
        {
            printf(" (%d,%d/%d)", rGraph[i][j].first+1 , adjList[i][j].second - rGraph[i][j].second , adjList[i][j].second);
        }
        printf("\n");
    }
    bfs(rGraph , s,t);
    // Return the overall flow
    cout<<"Min cut is : \n";
    for(int i=0; i<nVertices ; i++){

        for(int j=0; j<(int)adjList[i].size();j++)
        {
//            cout<<color[i]<<" "<<color[rGraph[i][j].first]<<endl;
           if(color[i] == BLACK && color[rGraph[i][j].first] == WHITE )
           {
            printf("(%d,%d) Cap-%d ", i+1, rGraph[i][j].first+1 , adjList[i][j].second);

           }

        }

    }
    cout<<endl;
    return max_flow;

}

void Graph::addEdge(int u, int v , int w = 1 )
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    adjList[u].push_back(make_pair(v,w));

    nEdges++;
    if(!directed){
      adjList[v].push_back(make_pair(u,w));
    }
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
//    adjList[u].erase(remove(adjList[u].begin(), adjList[u].end(), v), adjList[u].end());
    nEdges--;
    if(!directed){}
//        adjList[v].erase(remove(adjList[u].begin(), adjList[u].end(), u), adjList[u].end());    }
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
//    if(find(adjList[u].begin(), adjList[u].end(), v) != adjList[u].end()){
//        return true;
//    }
//    else{
//        return false;
//    }

    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices) return 0;

    return (int)adjList[u].size();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int i=0 ; i<nVertices ; i++){
//        if(matrix[u][i]==1 && matrix[v][i]==1){
//            return true;
//        }
    }
    return false;
}

bool Graph::pathexists(vector<vii> resGraph , int s, int t){
    // Create a visited array and mark all vertices as not visited
    bool visited[nVertices];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v < nVertices ; v++)
        {
            if (visited[v]==false && resGraph[u][v].first > 0 )
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    for(int i=0 ; i<nVertices ; i++)
        cout<<parent[i]<<" ";
    return (visited[t] == true);
}

bool Graph::bfs(vector<vii> graph , int source , int t)
{
//    //complete this function
//    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    queue<int> q;
    int k=1;
    color[source] = GREY;
    dist[source] = 0 ;
    q.push(source) ;
    while( !q.empty() )
    {
        bool flag = true;
        source = q.front();
        q.pop();
//        printf("%d  ",source);
        color[source]= BLACK;
        for(int i=0; i<graph[source].size() ; i++){

            if(graph[source][i].first >0 && graph[source][i].second >0 && color[graph[source][i].first]== WHITE ){
                color[graph[source][i].first] = GREY;
                dist[graph[source][i].first] = k;
                q.push(graph[source][i].first);
                parent[graph[source][i].first] = source;
                 flag = false;
            }
        }
        if(!flag)
            k++;

    }
//    printf("\n");
    if(color[t]== BLACK){return true;}
    else{return false;}

}

void Graph::visit(int source){
    if(color[source] == BLACK){
        return;
    }
//    discovery[source] = count;
//    printf("%d ",source);
//    color[source] = GREY;
//    for( int i = 0 ; i<nVertices ; i++){
////        if(matrix[source][i] && color[i]== WHITE){
////            count++;
////            visit(i);
////        }
//    }
    color[source] = BLACK;
    count++;
    finish[source] = count;
    return;
}

void Graph::dfs(int source=0)
{
    count = 1;
//    for(int i = 0; i<nVertices ; i++){
//        color[i] = WHITE;
//    }
//    visit(source);
//        for(int i = 0; i<nVertices ; i++){
//        if(color[i] == WHITE){
//            visit(i);
//        }
//    }
}

int Graph::getDist(int u, int v)
{
//    bfs(u);
//    for(int i=0 ;i<nVertices ; i++){
//        if(i == v){
//            return dist[i];
//        }
//    }
//    //returns the shortest path distance from u to v
//    //must call bfs using u as the source vertex, then use distance array to find the distance
    return 9 ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices ;i++)
    {
        printf("%d:", i +1 );
        for(int j=0; j<(int)adjList[i].size();j++)
        {
            printf(" (%d,%d)", adjList[i][j].first+1 , adjList[i][j].second);
        }
        printf("\n");
    }

}

Graph::~Graph()
{
    if(color) delete [] color;
    if(parent) delete [] parent;
    if(dist) delete [] dist;
    if(discovery) delete [] discovery;
    if(finish) delete [] finish;

    color = 0 ;
    parent = 0 ;
    dist = 0 ;
    discovery = 0 ;
    finish = 0 ;

    //write your destructor here
}


int main()
{
    int n , m, u,v,w ,s,t;
    Graph g(true);
    printf("Enter number of vertices & edges, Source & Sink: ");
    scanf("%d%d%d%d", &n , &m , &s, &t);
    g.setnVertices(n , m);

    for(int i =0 ; i<m ; i++){
        scanf("%d%d%d", &u, &v , &w);
        g.addEdge(u-1, v-1 , w);

    }
    g.printGraph();


    cout << "The maximum possible flow is "<<g.Ford_Fulkerson(s-1, t-1);

    return 0;
}
