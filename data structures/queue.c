// implement a queue

#include <stdio.h>
#include <stdlib.h>
#define SIZE 40

typedef struct queue
{
  int *data;
  int front;
  int rear;
  int size;
} queue;

queue *create_queue(int size)
{
  queue *q = (queue *)malloc(sizeof(queue));
  q->data = (int *)malloc(size * sizeof(int));
  q->front = 0;
  q->rear = 0;
  q->size = size;
  return q;
}

void enqueue(queue *q, int data)
{
  if (q->rear == q->size)
  {
    printf("queue is full\n");
    return;
  }
  q->data[q->rear++] = data;
}

int dequeue(queue *q)
{
  if (q->front == q->rear)
  {
    printf("queue is empty\n");
    return -1;
  }
  return q->data[q->front++];
}

int get_front(queue *q)
{
  if (q->front == q->rear)
  {
    printf("queue is empty\n");
    return -1;
  }
  return q->data[q->front];
}

int get_size(queue *q)
{
  return q->rear - q->front;
}

int pop(queue *q)
{
  if (q->front == q->rear)
  {
    printf("queue is empty\n");
    return -1;
  }
  return q->data[q->front++];
}

int main()
{
  queue *q = create_queue(SIZE);
  enqueue(q, 1);
  enqueue(q, 2);
  enqueue(q, 3);
  enqueue(q, 4);
  enqueue(q, 5);
  enqueue(q, 6);
  enqueue(q, 7);
  enqueue(q, 8);
  enqueue(q, 9);
  enqueue(q, 10);
  enqueue(q, 11);
  enqueue(q, 12);
  enqueue(q, 13);
  enqueue(q, 14);
  enqueue(q, 15);
  enqueue(q, 16);
  enqueue(q, 17);
  enqueue(q, 18);
  enqueue(q, 19);
  enqueue(q, 20);
  enqueue(q, 21);
  enqueue(q, 22);
  enqueue(q, 23);
  enqueue(q, 24);
  enqueue(q, 25);
  enqueue(q, 26);
  enqueue(q, 27);
  enqueue(q, 28);
  enqueue(q, 29);
  enqueue(q, 30);
  enqueue(q, 31);
  enqueue(q, 32);
  enqueue(q, 33);
  enqueue(q, 34);
  enqueue(q, 35);
  enqueue(q, 36);
  enqueue(q, 37);
  enqueue(q, 38);
  enqueue(q, 39);
  enqueue(q, 40);
  enqueue(q, 41);

  printf("%d\n", dequeue(q));
  printf("%d\n", dequeue(q));

  // pop(q);

  printf("%d\n", get_front(q));
  printf("%d\n", dequeue(q));

  // print size
  printf("%d\n", get_size(q));
}
