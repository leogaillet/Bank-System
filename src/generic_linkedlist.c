#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "../include/types.h"
#include "../include/generic_linkedlist.h"

void init_generic_table(void *data_array, const int data_count, size_t data_size, DataInitializer init_func, NodeHead *node_head)
{
    node_head->total_node = 0;
    node_head->head = NULL;
    for (int i = 0; i < data_count; i++)
    {
        void *data = (void *)(data_array + data_size * i);
        add_node(node_head, data, init_func);
    }
}

void free_generic_table(NodeHead *node_head, int (*compare_func)(void *, void *))
{
    Node *nd = node_head->head;
    while (nd != NULL)
    {
        GenericNode *g_node = (GenericNode *)nd;
        delete_node(node_head, g_node->data, compare_func);
        nd = nd->next;
    };
    free(nd);
    free(node_head);
}

int get_node_count(NodeHead *node_head)
{
    return node_head->total_node;
}

void add_node(NodeHead *node_head, void *data, DataInitializer init_func)
{
    GenericNode *new_node = (GenericNode *)malloc(sizeof(GenericNode));
    init_func(new_node, data);
    new_node->base.next = node_head->head;
    node_head->head = (Node *)new_node;
    node_head->total_node++;
}

void delete_node(NodeHead *node_head, void *data, int (*compare_func)(void *, void *))
{
    Node *current = node_head->head;
    Node *prev = NULL;
    while (current != NULL)
    {
        GenericNode *g_node = (GenericNode *)current;
        if (compare_func(g_node->data, data) == 0)
        {
            if (prev == NULL)
                node_head->head = current->next;
            else
                prev->next = current->next;
            free(g_node); // Libérer le nœud
            node_head->total_node--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void *find_node(NodeHead *node_head, void *data, int (*compare_func)(void *, void *))
{
    Node *current = node_head->head;
    while (current != NULL)
    {
        GenericNode *g_node = (GenericNode *)current;
        if (compare_func(g_node->data, data) == 0)
            return g_node->data;
        current = current->next;
    }
    return NULL;
}

void *find_node_by_id(NodeHead *node_head, unsigned int id, int (*compare_func)(void *, void *))
{
    return find_node(node_head, &id, compare_func);
}

void print_graph(NodeHead *node_head, void (*print_data)(void *))
{
    Node *current = node_head->head;
    while (current != NULL)
    {
        GenericNode *g_node = (GenericNode *)current;
        print_data(g_node->data);
        current = current->next;
        if (current != NULL)
            printf(" -> ");
    }
    printf("\n");
}