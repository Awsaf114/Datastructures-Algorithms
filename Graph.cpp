#include<bits/stdc++.h>
#include<iostream>
#include<vector>

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0
#define GREY 1
#define BLACK -1

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;


// Take input of undirected weighted graph
// AdjacencyListType &adjList is pass by reference of the adjacency list of type vector<list <vertex>>
// The const keyword is added wherever I know the value does not need to be modified.
void inputAdjacencyList(AdjacencyListType &adjList, int const& edges){
    int source, dest, weight;
    for(int i = 0; i < edges; ++i){
        cin >> source >> dest >> weight;

        adjList[source].push_back(make_pair(dest, weight));
        adjList[dest].push_back(make_pair(source, weight));
    }
}



// If there are no adjacent node "NONE" is printed.
// Now get the node name and the pair by accessing the first and second property.
// Since I have paired node name with weight so, the first is name and next one is the weight
void printCompleteAdjacencyList( AdjacencyListType &adjList, int &v ){

    for(int i = 0; i < adjList.size(); ++i){

        int adjNodes = adjList[i].size();
        printf("Adjacent of: %d", i);

        if(adjNodes > 0){
            list<vertex>::iterator it = adjList[i].begin();
            while(it != adjList[i].end()){
                printf(" -> %d (w:%d)", (*it).first, (*it).second);
                ++it;
            }
        }else{
            printf(" -> NONE");
        }

        printf("\n");
    }

}


// List nodes adjacent or, connected with current node.
// Get the beginning of the list of certain node using adjList[m].begin()
// So traversing the list one by one we can get all adjacent nodes.
void listAdjacentNodes( AdjacencyListType &adjList, int const& m){

    printf("%d", m);
    list<vertex>::iterator it = adjList[m].begin();
    while(it != adjList[m].end()){
        printf(" -> %d (w:%d)", (*it).first, (*it).second);
        ++it;
    }

}


int main(){

    // Input the vertex or, node count of the graph
    printf("Enter number of nodes:\n");
    int v;
    cin >> v;


    // Create the adjacency list structure with size of v.
    AdjacencyListType adjList(v);


    // Input the edge count of the graph
    printf("Enter Edge count:\n");
    int edges;
    cin >> edges;


    // Input the adjacency list
    printf("\nEnter source, destination and weight:\n");
    inputAdjacencyList(adjList, edges);


    // Show the complete adjacency list structure
    printf("\nWhole Adjacency List:\n");
    printCompleteAdjacencyList(adjList, v);


    // Enter a node number to see its adjacent or connected nodes
    printf("\nEnter node number to see adjacent nodes:\n");
    int m;
    scanf("%d", &m);


    // If the given node number is greater than the vertexes or, node count do nothing
    if(m < v){
        listAdjacentNodes(adjList, m);
    }

    return 0;
}
