#include "graph.h"
#include "graphRepresentation.h"

//! Prim related stuff
edgeT getMinimumEdgeForCurrentlyVisitedNodes(int * visited)
{
    int i,j;
    edgeT minEdge;
    minEdge.weight=MAX;

    for (i=0; i<nrOfVerteces; i++)
    {
        for (j=0; j<nrOfVerteces; j++)
        {
            if(visited[i] == VISITED && visited[j] != VISITED && adjMatrix[i][j] > 0)
            {
                if(adjMatrix[i][j]<minEdge.weight)
                {
                    minEdge.source = i;
                    minEdge.destination = j;
                    minEdge.weight = adjMatrix[i][j];
                }
            }
        }
    }

    return minEdge;
}

void printEdges(edgeT* edges, int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf("%c -> %c\t",edges[i].source+65, edges[i].destination+65);
    }
    printf("\n");
}

void prim(int startNode)
{
    printf("Prim's Algorithm started\n");

    int nrVertecesVisited=0,i;
    int * visited = (int*)malloc(nrOfVerteces * sizeof(int));
    for(i=0; i<nrOfVerteces; i++)
    {
        visited[i] = UNVISITED;
    }
    int minCost = 0;

    edgeT * edges = (edgeT*) malloc((nrOfVerteces-1) * sizeof(edgeT));

    visited[startNode] = VISITED;

    while(nrVertecesVisited<nrOfVerteces-1)
    {
        edgeT minEdge = getMinimumEdgeForCurrentlyVisitedNodes(visited);
        visited[minEdge.destination]=VISITED;
        edges[nrVertecesVisited++] = minEdge;
        minCost+=minEdge.weight;
    }

    printEdges(edges, nrVertecesVisited);
    printf("Cost of MST by Prim's Algorithm: %d\n",minCost);
    printf("Prim's algorithm ended\n\n");
}

//! Kruskal related stuff
edgeT getMinimumEdgeForAdjacencyMatrix(int ** adjMat)
{
    int i,j;
    edgeT minEdge;
    minEdge.weight=MAX;

    for (i=0; i<nrOfVerteces; i++)
    {
        for (j=0; j<nrOfVerteces; j++)
        {
            if(adjMat[i][j] > 0)
            {
                if(adjMat[i][j]<minEdge.weight)
                {
                    minEdge.source = i;
                    minEdge.destination = j;
                    minEdge.weight = adjMat[i][j];
                }
            }
        }
    }

    return minEdge;
}

int ** getCopyOfAdjecencyMatrix()
{
    int i,j;
    int ** copyAdjMatrix =(int**)malloc(nrOfVerteces*sizeof(int*));
    for (i=0; i<nrOfVerteces; i++)
    {
        *(copyAdjMatrix+i)=(int*)malloc(nrOfVerteces*sizeof(int));
        for(j=0; j<nrOfVerteces; j++)
        {
            copyAdjMatrix[i][j] = adjMatrix[i][j];
        }
    }
    return copyAdjMatrix;
}

int getParent(int * parent, int i)
{
    while(parent[i])
        i=parent[i];
    return i;
}

int uni(int * parent, int i,int j)
{
    if(i!=j)
    {
        parent[j]=i;
        return 1;
    }
    return 0;
}

void kruskal()
{
    printf("\nKruskal Algorithm started\n");
    int nrOfEdges=0,i,s,b;
    edgeT minEdge;
    int **matrix=getCopyOfAdjecencyMatrix();
    int *parent=(int*)malloc(nrOfVerteces*sizeof(int));
    edgeT *edges=(edgeT*)malloc(sizeof(edgeT)*(nrOfVerteces-1));

    for(i=0; i<nrOfVerteces; i++)
    {
        parent[i]=i;
    }
    while(nrOfEdges<nrOfVerteces-1)
    {
        minEdge=getMinimumEdgeForAdjacencyMatrix(matrix);
        matrix[minEdge.source][minEdge.destination] = 0;
        matrix[minEdge.destination][minEdge.source] = 0;

        if(parent[minEdge.source] != parent[minEdge.destination])
        {
            edges[nrOfEdges] = minEdge;
            if(parent[minEdge.source] > parent[minEdge.destination])
            {
                s = parent[minEdge.destination];
                b = parent[minEdge.source];
            }
            else
            {
                s = parent[minEdge.source];
                b = parent[minEdge.destination];
            }

            for(i=0; i<nrOfVerteces; i++)
            {
                if(parent[i] == s)
                    parent[i] = b;
            }
            nrOfEdges++;
            printEdges(edges,nrOfEdges);
        }


    }
    printf("\nKRUSKAL's algorithm ended\n\n");
}

//! Dijsktra related stuff

int getMinDistanceVertex(int * distances, int * visited)
{
    int min=MAX, i;
    int minV;
    for(i=0; i<nrOfVerteces; i++)
    {
        if(distances[i] < min && visited[i] == UNVISITED)
        {
            minV = i;
        }
    }
    return minV;
}

void dijkstra(int startNode)
{
    printf("Dijkstra's Algorithm started\n");
    int * distances = (int*)malloc(nrOfVerteces * sizeof(int));
    int * previous  = (int*)malloc(nrOfVerteces * sizeof(int));
    int * visited   = (int*)malloc(nrOfVerteces * sizeof(int));
    int nrOfVertecesVisited=0,i;
    for(i=0; i<nrOfVerteces; i++)
    {
        distances[i] = MAX;
        previous[i]  = UNDEFINED;
        visited[i] = UNVISITED;
    }
    distances[startNode] = 0;

    while(nrOfVertecesVisited < nrOfVerteces)
    {
        int u = getMinDistanceVertex(distances,visited);
        visited[u] = VISITED;

        int nrOfNeighbors = getNumberOfNeighborsOfVertex(u);
        int * neighbors = getAllNeighborsOfVertex(u);
        for(i=0; i<nrOfNeighbors; i++)
        {
            int w = neighbors[i];
            int alt = distances[u] + adjMatrix[u][w];
            if(alt<distances[w])
            {
                distances[w] = alt;
                previous[w] = u;
            }
        }
        nrOfVertecesVisited++;
    }

    for(i=0; i<nrOfVerteces; i++)
    {
        int u=i;
        if(i!=startNode)
        {
            while(previous[u] != UNDEFINED)
            {
                push(u);
                u = previous[u];
            }

            printf("Path from %c to %c is: %c ",startNode + 65, i+65, startNode + 65);
            while(!isEmptyStack())
            {
                printf("-> %c ",peekStack()->content + 65);
                pop();
            }
            printf("\n");
        }
    }

    printf("Dijkstra's Algorithm ended\n");
}

//!Bellmann Ford stuff

void printpaths(int i,int startNode,int parent[10])
{
    if(i==startNode)printf("%c",startNode+65);
    else{
        printpaths(parent[i],startNode,parent);
        printf("->%c",i+65);
    }

}

void printDist(int*dist,int*parent,int startNode,int**distance)
{
    int i;
    printf("\nDistances updated:\n");
    for(i=0; i<nrOfVerteces; i++)
    {
        printf("The initial distance from (%c->%c)was %d and now is %d\n",startNode+65,i+65,distance[startNode][i],dist[i]);
    }
    printf("\nThe paths from start to the other verteces:\n");
    for(i=0; i<nrOfVerteces; i++)
    {
        printpaths(i,startNode,parent);
        printf("\n");
    }
}
void BellmanFord(int startNode)
{
    printf("\nBellman Ford Starts\n");
    int i,j,u,v;
    int **distance=getCopyOfAdjecencyMatrix();
    int *parent=(int*)malloc(nrOfVerteces*sizeof(int));
    int *dist=(int*)malloc(nrOfVerteces*sizeof(int));

    for(i=0; i<nrOfVerteces; i++)
    {
        for(j=0; j<nrOfVerteces; j++)
        {
            if(distance[i][j]==0 && i!=j)
            {
                distance[i][j]=9999;
            }
        }
    }
    for(i=0; i<nrOfVerteces; i++)
    {
        if(i==startNode)
            dist[i]=0;
        else
            dist[i]=9999;
        parent[i]=0;
    }
    for(i=0; i<nrOfVerteces; i++)
    {
        for(u=0; u<nrOfVerteces; u++)
        {
            for(v=0; v<nrOfVerteces; v++)
            {
                if(adjMatrix[u][v]>0 && u!=v)
                {
                    if(dist[u]+adjMatrix[u][v]<dist[v])
                    {
                        dist[v]=dist[u]+adjMatrix[u][v];
                        parent[v]=u;
                    }
                    if(dist[u]+adjMatrix[u][v]<dist[v])
                    {
                        dist[v]=dist[u]+adjMatrix[u][v];
                        printf("error: Graph contains a negative-weight cycle");
                    }
                }
            }
        }
    }
   printDist(dist,parent,startNode,distance);
   printf("\nBellman's Algorithm ended\n");
}
