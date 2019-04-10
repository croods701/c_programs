#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define New_MemVar(type, n) ((type *)malloc(sizeof(type) * n))
#define NL printf("\n")

int ask_choice(char *ques, int m, int n)
{
    int ch;
    printf("%s :", ques);
    scanf("%d", &ch);
    while (ch < m || ch > n)
    {
        printf("%s :", ques);
        scanf("%d", &ch);
    }

    return ch;
}

void clear()
{
    system("cls||clear");
}
void pause()
{
    fflush(stdin);
    fflush(stdin);
    getchar();
}

void draw_seprator(char sep, int len)
{
    for (int i = 0; i < len; i++)
    {
        putchar(sep);
    }
    printf("\n");
}

#define MAX_LEN 50
int QUEUE[MAX_LEN];
int bottom = -1;
int top = -1;

int enqueue(int v)
{
    if (bottom < MAX_LEN)
    {
        if (bottom == -1)
            bottom++;
        QUEUE[++top] = v;
        return 0;
    }
    else
    {
        return -1;
    }
}

int dequeue()
{
    assert(top >= 0);
    return QUEUE[bottom++];
}

typedef struct
{
    int V;
    int **adjmatrix;
} graph_adjmatrix;

graph_adjmatrix create_graph(int V)
{
    graph_adjmatrix graph = {V, 0};
    int **adj = New_MemVar(int *, V);
    for (int i = 0; i < V; i++)
        adj[i] = (int *)calloc(sizeof(int), V);

    graph.adjmatrix = adj;
    return graph;
}

int set_edge(graph_adjmatrix *graph, int src, int des)
{
    if (src < graph->V && des < graph->V)
    {
        graph->adjmatrix[src][des] = 1;
        return 0;
    }
    else
    {
        return 1;
    }
}

typedef void (*callback)(void *context);
void print_graph_node(void *v)
{
    printf("%d ", *(int *)v);
}

void DFS_helper(graph_adjmatrix *graph, int v, int visited[], callback hook)
{
    visited[v] = 1;
    hook(&v);

    for (int i = 0; i < graph->V; i++)
        if (graph->adjmatrix[v][i] == 1)
            if (!visited[i])
                DFS_helper(graph, i, visited, hook);
}

void DFS_graph(graph_adjmatrix *graph, int v, callback hook)
{
    int visited[graph->V];
    for (int i = 0; i < graph->V; i++)
        visited[i] = 0;
    DFS_helper(graph, v, visited, hook);
}

void BFS_graph(graph_adjmatrix *graph, int v, callback hook)
{
    int visited[graph->V];
    for (int i = 0; i < graph->V; i++)
        visited[i] = 0;

    visited[v] = 1;
    enqueue(v);

    while (bottom <= top)
    {
        v = dequeue();
        hook(&v);

        for (int j = 0; j < graph->V; j++)
        {
            if (graph->adjmatrix[v][j] == 1)
            {
                if (!visited[j])
                {
                    visited[j] = 1;
                    enqueue(j);
                }
            }
        }
    }
}

int test()
{
    graph_adjmatrix new_graph = create_graph(4);
    set_edge(&new_graph, 0, 1);
    set_edge(&new_graph, 0, 2);
    set_edge(&new_graph, 1, 2);
    set_edge(&new_graph, 2, 0);
    set_edge(&new_graph, 2, 3);
    set_edge(&new_graph, 3, 3);
    DFS_graph(&new_graph, 0, &print_graph_node);
    NL;
    BFS_graph(&new_graph, 2, &print_graph_node);
    NL;

    DFS_graph(&new_graph, 2, &print_graph_node);
    NL;

    return 0;
}

int print_2d_array(int m, int n, int **arr)
{

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", *(*(arr + i) + j));
        NL;
    }

    NL;
}

void print_welcome_message()
{
    draw_seprator('-', 40);
    printf("\t Welcome to Graph program \n");
    draw_seprator('-', 40);
}

void graph_prgm()
{
    print_welcome_message();
    int vert = ask_choice("Enter the nodes/vertices in graph", 1, 100);
    graph_adjmatrix _graph = create_graph(vert);
    printf("Graph created sucessfully AND Adjacency Matix is created. \n");
    print_2d_array(vert, vert, _graph.adjmatrix);
    //Vertices Connect
    draw_seprator('-', 40);
    printf("\t Connect Vertices \n");
    draw_seprator('-', 40);

    printf("[Enter -1 and -1 to finish]\n");
    int flag = 1;
    while (flag)
    {
        int f, t;
        printf("Set Edges(from to) : ");
        scanf("%d %d", &f, &t);
        if (f == -1 || t == -1)
            flag = 0;
        else
            set_edge(&_graph, f, t);
    }
    NL;
    printf("New Adjancey Matrix :- \n");
    print_2d_array(vert, vert, _graph.adjmatrix);
    //Travesal
    draw_seprator('-', 40);
    printf("\t Traversal \n");
    draw_seprator('-', 40);
    printf("[Enter -1 to Exit]\n");
    int flag2 = 1;
    while (flag2)
    {
        int v = ask_choice("Enter the vertice:", -1, _graph.V - 1);
        if (v == -1)
            break;
        printf("BFS - ");
        BFS_graph(&_graph, v, &print_graph_node);
        NL;

        printf("DFS - ");
        DFS_graph(&_graph, v, &print_graph_node);
        NL;
        NL;
    }
}

int main()
{
    graph_prgm();
}