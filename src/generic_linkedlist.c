#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "../include/types.h"
#include "../include/generic_linkedlist.h"

void init_generic_table(NodeHead **node_head, void *data_array, const int data_count, size_t data_size, DataInitializer init_func)
{
    (*node_head) = (NodeHead *)malloc(sizeof(NodeHead));
    (*node_head)->total_node = 0;
    (*node_head)->head = NULL;
    for (int i = 0; i < data_count; i++)
    {
        void *data = (void *)(data_array + data_size * i);
        add_node((*node_head), data, init_func);
    }
}

void free_generic_table(NodeHead *node_head)
{
    Node *current = node_head->head;
    while (current != NULL)
    {
        GenericNode *g_node = (GenericNode *)current;
        node_head->head = current->next;
        free(g_node);
        current = node_head->head;
    }
    free(node_head);
}

void table_to_array(NodeHead *node_head, void *data_array, const int data_count, size_t data_size)
{
    int n = 0;
    Node *current = node_head->head;
    while (current != NULL && n < data_count)
    {
        GenericNode *g_node = (GenericNode *)current;

        void *datapointer = (void *)(data_array + n * data_size);
        memcpy(datapointer, g_node->data, data_size);

        current = current->next;
        n++;
    }
}

int get_node_count(NodeHead *node_head)
{
    return node_head->total_node;
}

Node *get_node_head(NodeHead *node_head)
{
    return node_head->head;
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

void find_nodes(NodeHead *node_head, void *data, int (*compare_func)(void *, void *), void *data_table_pointer, size_t data_size, int *data_count, const int MAX_COUNT)
{
    (*data_count) = 0;
    Node *current = node_head->head;

    while (current != NULL && (*data_count) < MAX_COUNT)
    {
        GenericNode *g_node = (GenericNode *)current;
        if (compare_func(g_node->data, data) == 0)
        {
            void *data_ptr = (void *)(data_table_pointer + (*data_count) * data_size);
            memcpy(data_ptr, g_node->data, data_size);

            (*data_count)++;
        }
        current = current->next;
    }
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