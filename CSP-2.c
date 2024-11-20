#include <stdio.h>

#define N 10

char colr[7] = {'V', 'I', 'B', 'G', 'Y', 'O', 'R'};

struct M_List
{
    int num;
    int matrix[100][100];
};

void M_Edge(struct M_List *B, int a, int b)
{
    B->matrix[a][b] = 1;
    B->matrix[b][a] = 1;
}

void M_printGraph(struct M_List *B)
{
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < B->num; ++i)
    {
        for (int j = 0; j < B->num; ++j)
        {
            printf("%d ", B->matrix[i][j]);
        }
        printf("\n");
    }
}

int check(int node, struct M_List *B, int color[], int col, int n, int graph[10][7])
{
    for (int i = 0; i < n; i++)
    {
        if (B->matrix[node][i] == 1 && color[i] == col)
        {
            return 0;
        }
    }
    return 1;
}

int track(struct M_List *B, int m, int color[], int node, int n)
{
    if (node == n)
    {
        return 1;
    }
    int graph[10][7];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            graph[i][j] = 1;
        }
    }

    for (int col = 1; col <= m; col++)
    {
        if (check(node, B, color, col, n, graph))
        {
            color[node] = col;
            int A[10];
            for(int i=0;i<10;i++)
            {
                A[i]=0;
            }
            if (graph[node][col - 1] == 1)
            {
                if (track(B, m, color, node + 1, n))
                {
                    return 1;
                    for(int j=0;j<n;j++)
                    {
                        if(B->matrix[node][j]==1)
                        {
                            graph[node][col-1]==0;
                        }
                    }
                }
                color[node] = 0;
            }
            
        }
    }

    return 0;
}

int graphColoring(struct M_List *B, int m, int n)
{
    int color[N];
    for (int i = 0; i < n; i++)
    {
        color[i] = 0;
    }

    if (track(B, m, color, 0, n))
    {
        printf("Solution Exists: The following are the assigned colors:\n");
        for (int i = 0; i < n; i++)
        {
            printf("Node %d ---> Color %c\n", i + 1, colr[color[i] - 1]);
        }
        return 1;
    }
    else
    {
        printf("Solution does not exist\n");
        return 0;
    }
}

int main()
{
    int n, E;
    int i;
    struct M_List *B;
    printf("Enter the number of vertices : ");
    scanf("%d", &n);
    printf("\nvertices are :");
    for (i = 0; i < n; i++)
    {
        printf("   %d\t", i + 1);
    }
    printf("\n\nEnter the number of edges: ");
    scanf("%d", &E);

    B = (struct M_List *)malloc(sizeof(struct M_List));
    B->num = n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            B->matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < E; ++i)
    {
        int a, b;
        do
        {
            printf("\n\nEnter edge %d (start and end point): \n", i + 1);
            scanf("%d", &a);
            scanf("%d", &b);
            if (a > n || b > n || a == 0 || b == 0 || a == b)
            {
                printf("Invalid vertex. Please enter valid vertices.\n");
            }
        } while (a > n || b > n || a == 0 || b == 0 || a == b);
        M_Edge(B, a - 1, b - 1);
    }
    printf("\n\n");
    M_printGraph(B);
    printf("\n\n");

    int m;
    printf("Enter no of colours : ");
    scanf("%d", &m);

    graphColoring(B, m, n);

    return 0;
}
