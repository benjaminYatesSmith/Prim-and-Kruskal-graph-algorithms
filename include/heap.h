#ifndef HEAP_H
#define HEAP_H

typedef struct {
    long int vertex;
    int cost;
} heap_node_t;

typedef struct {
    heap_node_t *nodes;
    int size;
    int capacity;
} heap_t;

heap_t* create_heap(int capacity);
void insert_heap(heap_t* heap, long int vertex, int cost);
heap_node_t extract_min(heap_t* heap);
int is_heap_empty(heap_t* heap);
void free_heap(heap_t* heap);

#endif 
