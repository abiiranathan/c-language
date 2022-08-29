// bfs.c

#include <stdio.h>
#include <stdlib.h>
#define SIZE 40

// implement a bfs
typedef struct graph
{
  int v;
  int e;
  int **adj;
} graph;

graph *create_graph(int v, int e)
{
  graph *g = (graph *)malloc(sizeof(graph));
  g->v = v;
  g->e = e;
  g->adj = (int **)malloc(v * sizeof(int *));
  for (int i = 0; i < v; i++)
  {
    g->adj[i] = (int *)malloc(v * sizeof(int));
  }
  return g;
}

void add_edge(graph *g, int v, int w)
{
  g->adj[v][w] = 1;
  g->adj[w][v] = 1;
}

void print_graph(graph *g)
{
  for (int i = 0; i < g->v; i++)
  {
    for (int j = 0; j < g->v; j++)
    {
      printf("%d ", g->adj[i][j]);
    }
    printf("\n");
  }
}

void bfs(graph *g, int s)
{
  int *visited = (int *)malloc(g->v * sizeof(int));
  for (int i = 0; i < g->v; i++)
  {
    visited[i] = 0;
  }
  int *queue = (int *)malloc(g->v * sizeof(int));
  int front = 0;
  int rear = 0;
  queue[rear++] = s;
  visited[s] = 1;

  while (front != rear)
  {
    int u = queue[front++];
    printf("%d ", u);
    for (int i = 0; i < g->v; i++)
    {
      if (g->adj[u][i] && !visited[i])
      {
        queue[rear++] = i;
        visited[i] = 1;
      }
    }
  }

  printf("\n");
  free(visited);
  free(queue);
}

void dfss(graph *g, int s, int *visited)
{
  visited[s] = 1;
  printf("%d ", s);
  for (int i = 0; i < g->v; i++)
  {
    if (g->adj[s][i] && !visited[i])
    {
      dfss(g, i, visited);
    }
  }
}

int main()
{
  graph *g = create_graph(SIZE, SIZE * (SIZE - 1));
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      g->adj[i][j] = 0;
    }
  }
  for (int i = 0; i < SIZE; i++)
  {
    add_edge(g, i, (i + 1) % SIZE);
  }

  print_graph(g);
  printf("\n\n");
  bfs(g, 0);

  int *visited = (int *)malloc(g->v * sizeof(int));
  for (int i = 0; i < g->v; i++)
  {
    visited[i] = 0;
  }

  dfss(g, 0, visited);
  printf("\n");
  return 0;
}
