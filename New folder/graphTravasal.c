#include<stdio.h>
#include<stdlib.h>

#define MAX_VALUE 100

struct Graph{
    int no_vertex;
    int m[MAX_VALUE][MAX_VALUE];
};

struct Graph* createGraph(int n){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->no_vertex = n;
    graph->m[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            graph->m[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(struct Graph* graph,int src,int dest){
    graph->m[src][dest] = 1;
}

void bfs(struct Graph* graph,int src){
    int n = graph->no_vertex;
    
    int* queue = (int*)malloc(sizeof(int)*100);
    int front = 0,rare=0;

    int visited[n];
    for(int i=0;i<n;i++){
        visited[i] = 0;
    }

    queue[rare++] = src;
    visited[src] = 1;

    while(front<rare){
        int curr = queue[front++];
        printf("%d ",curr);
        for(int i=0;i<n;i++){
            if(graph->m[curr][i] == 1 && visited[i] == 0){
                queue[rare++] = i;
                visited[i] = 1;
            }
        }
    }
}

void dfs(struct Graph* graph,int src){
    int n = graph->no_vertex;

    int* stack = (int*)malloc(sizeof(int)*100);
    int top = -1;

    int visited[n];
    for(int i=0;i<n;i++){
        visited[i] = 0;
    }

    stack[++top] = src;
    visited[src] = 1;

    while(top!=-1){
        int curr = stack[top--];
        printf("%d ",curr);
        for(int i=0;i<n;i++){
            if(graph->m[curr][i] == 1 && visited[i] == 0){
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }
}

int main(){

    int n;
    int edge;
    int ele;
    int src;

    printf("\nEnter Size : ");
    scanf("%d",&n);
    struct Graph* graph = createGraph(n);

    printf("\nEnter edges :\n");
    
    for(int i=0;i<n;i++){
        printf("\nEnter no. of edges for vertex %d : ",i);
        scanf("%d",&edge);
        printf("\nEnter vertex connected : ");
        for(int j=0;j<edge;j++){
            scanf("%d",&ele);
            addEdge(graph,i,ele);
        }
    }

    printf("\nEnter Source vertex : ");
    scanf("%d",&src);
    printf("\nBFS : ");
    bfs(graph,src);
    printf("\nDFS : ");
    dfs(graph,src);

    return 0;
}