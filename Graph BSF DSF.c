#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

/*


                        ADJACENCY LIST


*/

struct List
{
    int num;
    struct node *array[100];
};

void Edge(struct List *A, int a, int b)
{
    struct node *temp1 = (struct node *)malloc(sizeof(struct node));
    temp1->data = b;
    temp1->next = NULL;

    if (A->array[a] == NULL)
    {
        A->array[a] = temp1;
    }
    else
    {
        struct node *P = A->array[a];
        while (P->next != NULL)
        {
            P = P->next;
        }
        P->next = temp1;
    }

    struct node *temp2 = (struct node *)malloc(sizeof(struct node));
    temp2->data = a;
    temp2->next = NULL;

    if (A->array[b] == NULL)
    {
        A->array[b] = temp2;
    }
    else
    {
        struct node *P = A->array[b];
        while (P->next != NULL)
        {
            P = P->next;
        }
        P->next = temp2;
    }
}

void printGraph(struct List *A)
{
    for (int i = 0; i < A->num; ++i)
    {
        struct node *currentNode = A->array[i];
        printf("Adjacency list of vertex %d: ", i + 1);
        while (currentNode)
        {
            printf("%d -> ", currentNode->data + 1);
            currentNode = currentNode->next;
        }
        printf("NULL\n");
    }
}

void L_DFS_rec(struct List *A, int vertex, int visited[])
{
    visited[vertex] = 1;
    printf("%d ", vertex + 1);
    struct node *currentNode = A->array[vertex];
    while (currentNode)
    {
        int data = currentNode->data;
        if (!visited[data])
        {
            L_DFS_rec(A, data, visited);
        }
        currentNode = currentNode->next;
    }
}

void push(int stack[], int *top, int vertex)
{
    stack[++(*top)] = vertex;
}

int pop(int stack[], int *top)
{
    return stack[(*top)--];
}

void L_DFS(struct List *A)
{
    int visited[100] = {0};
    int stack[100];
    int top = -1;
    int startvertex;

    startvertex = 0;

    push(stack, &top, startvertex);
    visited[startvertex] = 1;

    while (top != -1)
    {
        int currentVertex = pop(stack, &top);
        printf("%d ", currentVertex + 1);

        struct node *currentNode = A->array[currentVertex];
        while (currentNode)
        {
            int adjacentVertex = currentNode->data;
            if (!visited[adjacentVertex])
            {
                push(stack, &top, adjacentVertex);
                visited[adjacentVertex] = 1;
            }
            currentNode = currentNode->next;
        }
    }

    printf("\n\nDFS with Recursion and DFS without Recursion  is different as Recursion is performed with 'Visted array' and without Recursion is performed with 'Stack' ");
}

void L_BFS(struct List *A)
{
    int visited[100] = {0};
    int queue[100];
    int front = -1, rear = -1;
    int start;
    start = 0;

    visited[start] = 1;
    queue[++rear] = start;

    while (front < rear)
    {
        int currentVertex = queue[++front];
        printf("%d ", currentVertex + 1);

        struct node *currentNode = A->array[currentVertex];
        while (currentNode)
        {
            int prev = currentNode->data;
            if (!visited[prev])
            {
                visited[prev] = 1;
                queue[++rear] = prev;
            }
            currentNode = currentNode->next;
        }
    }
}

/*


                        ADJACENCY MATRIX


*/

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

void M_DFS(struct M_List *B, int vertex, int visited[])
{
    visited[vertex] = 1;
    printf("%d ", vertex + 1);

    for (int i = 0; i < B->num; ++i)
    {
        if (B->matrix[vertex][i] == 1 && !visited[i])
        {
            M_DFS(B, i, visited);
        }
    }
}

void recM_DFS(struct M_List *B)
{
    int visited[100] = {0};
    int stack[100];
    int top = -1;
    int startvertex;
    int n = B->num;

    startvertex = 0;

    push(stack, &top, startvertex);
    visited[startvertex] = 1;

    while (top != -1)
    {
        int currentVertex = pop(stack, &top);
        printf("%d ", currentVertex + 1);

        for (int i = 0; i < n; i++)
        {
            if (B->matrix[currentVertex][i] == 1 && visited[i] == 0)
            {
                push(stack, &top, i);
                visited[i] = 1;
            }
        }
    }

    printf("\n\nDFS with Recursion and DFS without Recursion  is different as Recursion is performed with 'Visted array' and without Recursion is performed with 'Stack' ");
}

void M_BFS(struct M_List *B, int start)
{
    int visited[100] = {0};
    int queue[100];
    int front = 0, rear = -1;

    visited[start] = 1;
    queue[++rear] = start;

    while (front <= rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex + 1);

        for (int i = 0; i < B->num; ++i)
        {
            if (B->matrix[currentVertex][i] == 1 && !visited[i])
            {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

/*


                        Bipartite


*/

int Bipartite(struct List *A, int Z)
{
    int color[100];
    int i;
    for (i = 0; i < A->num; i++)
    {
        color[i] = 0;
    }

    int queue[100];
    int front = 0, rear = -1;

    color[Z] = 1;
    queue[++rear] = Z;

    while (front <= rear)
    {
        int currentVertex = queue[front++];
        struct node *currentNode = A->array[currentVertex];

        while (currentNode)
        {
            int data = currentNode->data;
            if (color[data] == color[currentVertex])
                return 0;
            if (color[data] == 0)
            {
                color[data] = 3 - color[currentVertex];
                queue[++rear] = data;
            }
            currentNode = currentNode->next;
        }
    }

    return 1;
}

int main()
{
    int n, E;
    int i;
    int choice;
    struct List *A;
    struct M_List *B;

    int visited[100] = {0};

    printf("Enter the number of vertices : ");
    scanf("%d", &n);
    printf("\nvertices are :");
    for (i = 0; i < n; i++)
    {
        printf("   %d\t", i + 1);
    }
    printf("\n\nEnter the number of edges: ");
    scanf("%d", &E);

    while (1)
    {
        printf("\n\n1)Adjacency List \n");
        printf("2)Adjacency Matrix\n");
        printf("NOTE:Bipartite check is in Adjacency List\n\n");
        printf("enter your choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            A = (struct List *)malloc(sizeof(struct List));
            A->num = n;
            for (i = 0; i < n; ++i)
            {
                A->array[i] = NULL;
            }

            for (i = 0; i < E; ++i)
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
                Edge(A, a - 1, b - 1);
            }
            printf("\n\n");
            printGraph(A);
            printf("\n\n");

            while (1)
            {
                printf("\n\n\n1) DSF with Recursion");
                printf("\n2) DSF without Recursion");
                printf("\n3) BSF without Recursion");
                printf("\n4) Check if the input graph is bipartite ");
                printf("\n5) EXIT");

                printf("\nEnter choice:");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:

                    L_DFS_rec(A, 0, visited);
                    break;

                case 2:
                    L_DFS(A);
                    break;

                case 3:
                    L_BFS(A);
                    break;

                case 4:

                    if (Bipartite(A, 0))
                    {
                        printf("The graph is bipartite.\n");
                    }
                    else
                    {
                        printf("The graph is not bipartite.\n");
                    }
                    break;
                    break;

                case 5:
                    return 1;
                    break;
                }
            }
            break;

        case 2:

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

            while (1)
            {
                printf("\n\n\n1) DFS with Recursion");
                printf("\n2) BFS without Recursion");
                printf("\n3) DFS without Recursion");
                printf("\n4) EXIT");

                printf("\nEnter choice:");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    M_DFS(B, 0, visited);
                    for (int i = 0; i < n; ++i)
                    {

                        visited[i] = 0;
                    }

                    break;

                case 2:

                    M_BFS(B, 0);
                    break;

                case 3:
                    recM_DFS(B);
                    break;
                case 4:
                    return 1;
                    break;
                }
            }
            break;
        }
    }
    return 0;
}