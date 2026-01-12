#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


heap_t* create_heap(int capacity) {
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
    heap->nodes = (heap_node_t*)malloc(capacity * sizeof(heap_node_t));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(heap_node_t* a, heap_node_t* b) {
    heap_node_t temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(heap_t* heap, int index) {
    while (index > 0 && heap->nodes[index].cost < heap->nodes[(index - 1) / 2].cost) {
        swap(&heap->nodes[index], &heap->nodes[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void heapify_down(heap_t* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->nodes[left].cost < heap->nodes[smallest].cost)
        smallest = left;

    if (right < heap->size && heap->nodes[right].cost < heap->nodes[smallest].cost)
        smallest = right;

    if (smallest != index) {
        swap(&heap->nodes[index], &heap->nodes[smallest]);
        heapify_down(heap, smallest);
    }
}

void insert_heap(heap_t* heap, long int vertex, int cost) {
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Heap overflow\n");
        return;
    }

    heap_node_t node = { vertex, cost };
    heap->nodes[heap->size] = node;
    heapify_up(heap, heap->size);
    heap->size++;
}

heap_node_t extract_min(heap_t* heap) {
    if (heap->size == 0) {
        fprintf(stderr, "Heap underflow\n");
        exit(EXIT_FAILURE);
    }

    heap_node_t root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);

    return root;
}

int is_heap_empty(heap_t* heap) {
    return heap->size == 0;
}

void free_heap(heap_t* heap) {
    free(heap->nodes);
    free(heap);
}
