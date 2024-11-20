#include <stdio.h>
#include <stdlib.h>

int n;

struct node
{
    int data;
    int weight;
    struct node *next;
};

struct M_List
{
    int num;
    int weight[100];
    int matrix[100][100];
};

void M_Edge(struct M_List *B, int a, int b)
{
    int w;
    printf("Enter Weight :");
    scanf("%d", &w);
    B->matrix[a][b] = w;
}

void M_printGraph(struct M_List *B)
{
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < B->num; ++i)
    {
        for (int j = 0; j < B->num; ++j)
        {
            printf("%d\t", B->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void M_display(int *dist, int s)
{
    int i;
    printf("%d is Source vertex\n", s);
    for (i = 0; i < n; i++)
    {
        printf("%d ----->  %d\n", i + 1, dist[i]);
    }
}

int M_min(int *dist, int *visited,struct M_List *B)
{
    int min = 99, index, i;
    for (i = 0; i < n; i++)
    {
        if (visited[i] == 0 && dist[i] + B->weight[i] <= min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void BST(struct M_List *B)
{
    int visited[20], dist[20], i, j, u, s,parent[20];
    printf("Enter Source node : ");
    scanf("%d", &s);
    for (i = 0; i < 20; i++)
    {
        visited[i] = 0;
        dist[i] = 999;
        parent[i] = -1;
    }

    dist[s - 1] = 0;
    printf("%d\n", dist[s - 1]);

    for (i = 0; i < n; i++)
    {
        u = M_min(dist, visited,B);
        visited[u] = 1;
        for (j = 0; j < n; j++)
        {
            if (B->matrix[u][j] < dist[j] && visited[j] == 0)
            {
                dist[j] = B->matrix[u][j] ;
            }
        }
        printf("%d\t|||", u);
        for (j = 0; j < n; j++)
        {
            printf("%d\t", dist[j]);
        }
        printf("\n");
    }

    M_display(dist, s);
}

int main()
{
    int E;
    int i;
    struct M_List *B;

    printf("Enter the number of vertices : ");
    scanf("%d", &n);
    printf("\nvertices are :");
    for (i = 0; i < n; i++)
    {
        printf("   %d\t", i + 1);
    }


    B = (struct M_List *)malloc(sizeof(struct M_List));
    B->num = n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            B->matrix[i][j] = 999;
            B->weight[i] = 0;
        }
    }


    printf("\n\nEnter the number of edges: ");

    scanf("%d", &E);

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
    M_printGraph(B);

    BST(B);

    return 0;
}