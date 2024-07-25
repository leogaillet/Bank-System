#ifndef GENERNIC_LINKEDLIST_H
#define GENERNIC_LINKEDLIST_H

#include "./types.h"
#include <stdlib.h>

#define TABLE_SIZE 100

typedef void (*DataInitializer)(void *node, void *data);

typedef struct NodeHead
{
    int total_node;
    struct Node *head;
} NodeHead;

typedef struct Node
{
    struct Node *next;
} Node;

typedef struct GenericNode
{
    Node base;
    void *data;
} GenericNode;

void init_generic_table(void *data_array, const int data_count, size_t data_size, DataInitializer init_func, NodeHead *node_head);

void free_generic_table(NodeHead *node_head, int (*compare_func)(void *, void *));

int get_node_count(NodeHead *node_head);

void add_node(NodeHead *node_head, void *data, DataInitializer init_func);

void delete_node(NodeHead *node_head, void *data, int (*compare_func)(void *, void *));

void *find_node(NodeHead *node_head, void *data, int (*compare_func)(void *, void *));

void *find_node_by_id(NodeHead *node_head, unsigned int id, int (*compare_func)(void *, void *));

void print_graph(NodeHead *node_head, void (*print_func)(void *));

#endif // GENERNIC_LINKEDLIST_H