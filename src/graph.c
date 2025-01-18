/*
 * Copyright (c) 2025 Vedant Mathur
 *
 * Graph Data Structure Operations Implementation.
 */

#include <graph.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <strings.h>
#include <stdio.h>

graph_t *
create_graph(uint64_t num_vertices)
{
    /* Allocate graph object. */
    graph_t *new_graph = (graph_t *)malloc(sizeof(graph_t));
    if (NULL == new_graph) {
        goto done;
    }

    /* Allocate memory for all vertices. */
    new_graph->vertices = (graph_vertex_t *)malloc(sizeof(graph_vertex_t) * num_vertices);
    if (NULL == new_graph->vertices) {
        free(new_graph);
        goto done;

    }

    /* Zero memory for all vertices. */
    bzero(new_graph->vertices, sizeof(graph_vertex_t) * num_vertices);

    /* Set num vertices. */
    new_graph->num_vertices = num_vertices;
    new_graph->next_vertex_index = 0;

done:
    return new_graph;
}

int
add_vertex(graph_t *g, uint64_t key)
{
    int error = 0;
    uint16_t index = 0;

    if (g == NULL) {
        error = ENOENT;
        goto done;
    }

    /*
     * Find next free vertex index.
     * If graph is full retun error.
     */
    index = g->next_vertex_index;
    if (index == g->num_vertices) {
        error = ENOMEM;
        goto done;
    }

    /* Populate new vertex. */
    graph_vertex_t *vertex = &g->vertices[index];
    vertex->key = key;
    vertex->edges = NULL;

    /* Increase index. */
    ++g->next_vertex_index;

done:
    return error;
}

static graph_vertex_t *
find_vertex_from_key(graph_t *g, uint64_t key)
{
    graph_vertex_t *vertex = NULL;

    if (g == NULL) {
        goto done;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        vertex = &g->vertices[i];
        if (vertex->key == key) {
            break;
        }
    }

done:
    return vertex;
}

static int
add_edge_directed(graph_t *g, uint64_t src_vertex,
                  uint64_t dst_vertex, uint64_t weight)
{
    int error = 0;
    graph_vertex_t *src = find_vertex_from_key(g, src_vertex);
    graph_vertex_t *dst = find_vertex_from_key(g, dst_vertex);

    if (g == NULL) {
        error = ENOENT;
        goto done;
    }

    if (src == NULL || dst == NULL) {
        error = ENOENT;
        goto done;
    }

    graph_edge_t *new_edge = (graph_edge_t *)malloc(sizeof(graph_edge_t));
    if (NULL == new_edge) {
        error = ENOMEM;
        goto done;
    }

    new_edge->src = src;
    new_edge->dst = dst;
    new_edge->weight = weight;
    new_edge->edge_next = NULL;

    /* Insert to list of edges at head. */
    {
        graph_edge_t *curr = src->edges;
        if (curr == NULL) {
            src->edges = new_edge;
            goto done;
        } else {
            new_edge->edge_next = src->edges;
            src->edges = new_edge;
        }
    }

done:
    return error;
}

int
add_edge(graph_t *g, uint64_t src_vertex, uint64_t dst_vertex,
         uint64_t weight, bool undirected)
{
    int error = 0;

    if (g == NULL) {
        error = ENOENT;
        goto done;
    }

    error = add_edge_directed(g, src_vertex, dst_vertex, weight);
    if (error) {
        goto done;
    }

    /* Add reverse edge if undirecte with same weight. */
    if (undirected) {
        error = add_edge_directed(g, dst_vertex, src_vertex, weight);
        if (error) {
            goto done;
        }
    }

done:
    return error;

}

void
delete_graph(graph_t *g)
{
    if (g == NULL) {
        return;
    }

    /* Delete edges of all vertices. */
    for (int i = 0; i < g->num_vertices; i++) {
        graph_vertex_t *vertex = &g->vertices[i];
        graph_edge_t *curr_edge = vertex->edges;
        if (curr_edge == NULL) {
            continue;
        }
        graph_edge_t *next_edge = curr_edge->edge_next;
        while (curr_edge != NULL) {
            free(curr_edge);
            curr_edge = next_edge;
            if (next_edge) {
                next_edge = next_edge->edge_next;
            }
        }
    }

    /* Delete vertices. */
    free(g->vertices);

    /* Delete graph. */
    free(g);
}

void
print_graph(graph_t *g)
{
    if (g == NULL) {
        printf("\nEmpty Graph!!");
    }

    printf("\n\t\tGRAPH INFO:");

    printf("\n\t\t\t# of Vertices: %llu", g->num_vertices);
    printf("\n\t\t\tNext Free Vertex Index: %u", g->next_vertex_index);

    printf("\n\t\t\tAdjacency List: ");
    for (int i = 0; i < g->num_vertices; i++) {
        graph_vertex_t *vertex = &g->vertices[i];
        printf("\n\t\t\t\t Key: %llu --> ", vertex->key);
        graph_edge_t *curr_edge = vertex->edges;
        while (curr_edge != NULL) {
            if (curr_edge->weight > 0) {
                printf("%llu (wt: %llu) ---> ", curr_edge->dst->key, curr_edge->weight);
            } else {
                printf("%llu ---> ", curr_edge->dst->key);
            }
            curr_edge = curr_edge->edge_next;
        }
        printf("##");
    }
    printf("\n\t\tGRAPH INFO DONE");
}
