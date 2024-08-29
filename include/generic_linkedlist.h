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

void init_generic_table(NodeHead **node_head, void *data_array, const int data_count, size_t data_size, DataInitializer init_func);

void free_generic_table(NodeHead *node_head);

void table_to_array(NodeHead *node_head, void *data_array, const int data_count, size_t data_size);

int get_node_count(NodeHead *node_head);

Node *get_node_head(NodeHead *node_head);

void add_node(NodeHead *node_head, void *data, DataInitializer init_func);

void delete_node(NodeHead *node_head, void *data, int (*compare_func)(void *, void *));

void *find_node(NodeHead *node_head, void *data, int (*compare_func)(void *, void *));

void find_nodes(NodeHead *node_head, void *data, int (*compare_func)(void *, void *), void *data_table_pointer, size_t data_size, int *data_count, const int MAX_COUNT);

void print_graph(NodeHead *node_head, void (*print_func)(void *));

void print_address(void *data);

#endif // GENERNIC_LINKEDLIST_H