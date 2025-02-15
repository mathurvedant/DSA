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
#include <queue.h>
#include <Stack.h>

graph_t *
create_graph(uint64_t num_vertices, bool is_directed)
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

    /* Set directed or undirected. */
    new_graph->is_directed = is_directed;

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
    vertex->idx = index;
    vertex->edges = NULL;

    /* Increase index. */
    ++g->next_vertex_index;

done:
    return error;
}

static graph_vertex_t *
find_vertex_from_index(graph_t *g, uint16_t idx)
{
    graph_vertex_t *vertex = NULL;

    if (g == NULL) {
        goto done;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        vertex = &g->vertices[i];
        if (vertex->idx == idx) {
            break;
        }
    }

done:
    return vertex;
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
add_edge(graph_t *g, uint64_t src_vertex,
        uint64_t dst_vertex, uint64_t weight)
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
    if (!g->is_directed) {
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
            if (curr_edge->weight != 0) {
                printf("%llu (wt: %lld) ---> ", curr_edge->dst->key, curr_edge->weight);
            } else {
                printf("%llu ---> ", curr_edge->dst->key);
            }
            curr_edge = curr_edge->edge_next;
        }
        printf("##");
    }
}

graph_t*
graph_from_adjmatrix(int **adjm, uint64_t numvertices, bool isdirected)
{
    int error = 0;
    graph_t *g = NULL;

    /*
     * Adjacency matrix has directed edges only
     * so mark as directed to create graph and
     * add edges accordingly.
     *
     * Later once graph is ready, mark graph as directed
     * or undirected based on argument.
     */
    bool directed = true;
    g = create_graph(numvertices, directed);
    if (g == NULL) {
        goto done;
    }

    for (int i = 0; i < numvertices; i++) {
        error = add_vertex(g, i);
        if (error) {
            goto done;
        }
    }

    for (int i = 0; i < numvertices; i++) {
        for (int j = 0; j < numvertices; j++) {
            if (adjm[i][j]) {
                error = add_edge(g, i, j, 0);
                if (error) {
                    goto done;
                }
            }
        }
    }

    g->is_directed = isdirected;

done:
    if (error && g) {
        delete_graph(g);
        g = NULL;
    }
    return g;

}

static int
graph_dfs_connected(graph_t *g, graph_vertex_t *start,
                    bool *visited, bool *callstack,
                    bool *has_cycle, graphtraversalcb cb)
{
    int error = 0;
    dsa_stack_t *st = NULL;
    uint64_t num_vertices = g->num_vertices;
    graph_vertex_t *parent = NULL;
    graph_vertex_t *curr_vertex = start;

    st = create_dsa_stack(num_vertices);
    if (st == NULL) {
        error = ENOMEM;
        goto done;
    }

    dsa_stack_push(st, (uint64_t)(curr_vertex));

    while (!dsa_stack_is_empty(st)) {

        uint64_t temp = 0;
        graph_edge_t *curr_edge = NULL;

        // Extract Vertex from Stack
        dsa_stack_pop(st, &temp);
        curr_vertex = (graph_vertex_t *)(temp);
        curr_edge = curr_vertex->edges;

        // Process Vertex if not visited already.
        // Mark as visited
        if (!visited[curr_vertex->idx]) {
            visited[curr_vertex->idx] = true;
            callstack[curr_vertex->idx] = true;
            if (cb) {
                cb(curr_vertex);
            }
        }

        // Add adjacent vertices to stack if not
        // visited.
        while (curr_edge != NULL) {
            graph_vertex_t *v = curr_edge->dst;
            if (!visited[v->idx]) {
                dsa_stack_push(st, (uint64_t)(curr_edge->dst));
            } else {
                // Parent tracking based logic for
                // undirected graphs.
                if (!g->is_directed) {
                    if (v != parent) {
                        if (has_cycle) {
                            *has_cycle = true;
                        }
                    }
                } else {
                    // Callstack tracking based logic
                    // for directed graphs.
                    if (callstack[v->idx]) {
                        if (has_cycle) {
                            *has_cycle = true;
                        }
                    }
                }
            }
            curr_edge = curr_edge->edge_next;
        }
        parent = curr_vertex;
    }

done:
    if (st) {
        destroy_dsa_stack(st);
    }

    return error;
}

static void
reset_callstack(bool *callstack, uint64_t numvertices)
{
    for (int i = 0; i < numvertices; i++) {
        callstack[i] = false;
    }
}

int
graph_dfs(graph_t *g, uint64_t start_vertex, bool *has_cycle,
          graphtraversalcb cb)
{
    int error = 0;
    bool *visited = NULL;
    bool *incallstack = NULL;
    uint64_t num_vertices = 0;
    graph_vertex_t *start = NULL;

    if (g == NULL) {
        error = EINVAL;
        goto done;
    }
    num_vertices = g->num_vertices;

    start = find_vertex_from_key(g, start_vertex);
    if (start == NULL) {
        error = EINVAL;
        goto done;
    }

    visited = (bool *)malloc(sizeof(bool) * num_vertices);
    if (visited == NULL) {
        error = ENOMEM;
        goto done;
    }

    incallstack = (bool *)malloc(sizeof(bool) * num_vertices);
    if (incallstack == NULL) {
        error = ENOMEM;
        goto done;
    }

    for (int i = 0; i < num_vertices; i++) {
        visited[i] = false;
        incallstack[i] = false;
    }

    // DFS
    {
        /* DFS from given start vertex. */
        error = graph_dfs_connected(g, start, visited, incallstack,
                                    has_cycle, cb);
        if (error) {
            goto done;
        }

        /*
         * If we have unvisited nodes, pick the first one
         * and start DFS from there.
         */
        for (int i = 0; i < num_vertices; i++) {
            graph_vertex_t *v = find_vertex_from_index(g, i);
            if (visited[i] == false) {
                reset_callstack(incallstack, num_vertices);
                error = graph_dfs_connected(g, v, visited, incallstack,
                                            has_cycle, cb);
                if (error) {
                    goto done;
                }
            }
        }
    }

done:

    if (incallstack) {
        free(incallstack);
    }


    if (visited) {
        free(visited);
    }

    return error;
}

static int
graph_bfs_connected(graph_t *g, graph_vertex_t *start,
                    bool *visited, graphtraversalcb cb)
{
    int error = 0;
    simple_q *q = NULL;
    uint64_t num_vertices = g->num_vertices;

    q = create_simple_q(num_vertices);
    if (q == NULL) {
        error = ENOMEM;
        goto done;
    }

    // BFS
    {
        simple_q_enqueue(q, (uint64_t)(start));

        while (!simple_q_is_empty(q)) {
            uint64_t temp = 0;
            graph_vertex_t *curr_vertex = NULL;
            graph_edge_t *curr_edge = NULL;
            uint64_t level_length = q->curr_size;
            bool did_visit_in_curr_level = false;

            while (level_length > 0) {

                --level_length;

                // Extract Vertex from Queue
                simple_q_dequeue(q, &temp);
                curr_vertex = (graph_vertex_t *)(temp);
                curr_edge = curr_vertex->edges;

                // Process Vertex if not visited already.
                // Mark as visited
                if (!visited[curr_vertex->idx]) {
                    visited[curr_vertex->idx] = true;
                    if (cb) {
                        cb(curr_vertex);
                    }
                    did_visit_in_curr_level= true;
                }

                // Add adjacent vertices to stack if not
                // visited.
                while (curr_edge != NULL) {
                    graph_vertex_t *v = curr_edge->dst;
                    if (!visited[v->idx]) {
                        simple_q_enqueue(q, (uint64_t)(curr_edge->dst));
                    }
                    curr_edge = curr_edge->edge_next;
                }
            }
            if (cb && did_visit_in_curr_level) {
                printf(": ");
            }
        }
    }

done:
    if (q) {
        destroy_simple_q(q);
    }
    return error;
}

int
graph_bfs(graph_t *g, uint64_t start_vertex, graphtraversalcb cb)
{
    int error = 0;
    bool *visited = NULL;
    uint64_t num_vertices = 0;
    graph_vertex_t *start = NULL;

    if (g == NULL) {
        error = EINVAL;
        goto done;
    }
    num_vertices = g->num_vertices;

    start = find_vertex_from_key(g, start_vertex);
    if (start == NULL) {
        error = EINVAL;
        goto done;
    }

    visited = (bool *)malloc(sizeof(bool) * num_vertices);
    if (visited == NULL) {
        error = ENOMEM;
        goto done;
    }

    for (int i = 0; i < num_vertices; i++) {
        visited[i] = false;
    }

    // BFS
    {
        /* BFS from given start vertex. */
        error = graph_bfs_connected(g, start, visited, cb);
        if (error) {
            goto done;
        }

        /*
         * If we have unvisited nodes, pick the first one
         * and start BFS from there.
         */
        for (int i = 0; i < num_vertices; i++) {
            graph_vertex_t *v = find_vertex_from_index(g, i);
            if (visited[i] == false) {
                error = graph_bfs_connected(g, v, visited, cb);
                if (error) {
                    goto done;
                }
            }
        }
    }

done:
    if (visited) {
        free(visited);
    }
    return error;
}

bool
has_cycle(graph_t *g)
{
    bool has_cycle = false;

    if (g == NULL) {
        goto done;
    }

    graph_dfs(g, g->vertices[0].key , &has_cycle, NULL);

done:
    return has_cycle;
}

static graph_vertex_t *
vertex_with_min_distance(graph_t *g, int64_t *dist, bool *visited)
{
    graph_vertex_t *v = NULL;
    uint64_t min = INT64_MAX;;
    uint16_t min_idx = -1;

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visited[i] && (dist[i] <= min)) {
            min_idx = i;
            min = dist[i];
        }
    }

    if (min_idx >= 0) {
        v = find_vertex_from_index(g, min_idx);
    }

    return v;
}

static void
print_path_helper(uint64_t *parents, int start_idx, int end_idx)
{
    if (end_idx == start_idx) {
        return;
    }

    print_path_helper(parents, start_idx, parents[end_idx]);
    printf("%llu --> ", parents[end_idx]);
}

static void
print_shortest_path_info(graph_vertex_t *start, graph_vertex_t *end,
                         int64_t *dist, uint64_t *parents, int num_vertices)
{
    bool path_valid = (dist[end->idx] == INT64_MAX) ? false : true;

    printf("\n\t\tShortest Path from %llu to %llu - ", start->key, end->key);

    if (!path_valid) {
        printf("No Path Found");
    }

    printf("\n\t\t\tVertices - \t\t");
    for (int i = 0 ; i < num_vertices; i++) {
        printf(" %5d ", i);
    }

    printf("\n\t\t\tDistance Array - \t");
    for (int i = 0 ; i < num_vertices; i++) {
        if (dist[i] == INT64_MAX) {
            printf(" %5s ", "*");
        } else {
            printf(" %5lld ", dist[i]);
        }
    }

    printf("\n\t\t\tParents Array - \t");
    for (int i = 0 ; i < num_vertices; i++) {
        if (parents[i] == INT64_MAX) {
            printf(" %5s ", "*");
        } else {
            printf(" %5llu ", parents[i]);
        }
    }

    if (path_valid) {
        printf("\n\t\t\tPath - \t");
        print_path_helper(parents, start->idx, end->idx);
        printf("%d ", end->idx);
    }
}

int
shortest_path_dijkstra(graph_t *g, uint64_t src, uint64_t dst)
{
    int error = 0;
    uint64_t num_vertices = 0;
    graph_vertex_t *start = NULL;
    graph_vertex_t *end = NULL;
    int64_t *dist = NULL;
    uint64_t *parents = NULL;
    bool *visited = NULL;

    if (g == NULL) {
        error = EINVAL;
        goto done;
    }
    num_vertices = g->num_vertices;

    start = find_vertex_from_key(g, src);
    if (start == NULL) {
        error = EINVAL;
        goto done;
    }

    end = find_vertex_from_key(g, dst);
    if (end == NULL) {
        error = EINVAL;
        goto done;
    }


    dist = (int64_t *)malloc(sizeof(int64_t) * num_vertices);
    if (dist == NULL) {
        error = ENOMEM;
        goto done;
    }

    parents = (uint64_t *)malloc(sizeof(uint64_t) * num_vertices);
    if (parents == NULL) {
        error = ENOMEM;
        goto done;
    }

    visited = (bool *)malloc(sizeof(bool) * num_vertices);
    if (visited == NULL) {
        error = ENOMEM;
        goto done;
    }

    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INT64_MAX;
        parents[i] = UINT64_MAX;
        visited[i] = false;
    }

    dist[start->idx] = 0;
    parents[start->idx] = start->key;

    while (true) {
        graph_vertex_t *curr_vertex = NULL;
        graph_edge_t *curr_edge = NULL;

        curr_vertex = vertex_with_min_distance(g, dist, visited);
        if (visited[curr_vertex->idx]) {
            break;
        }

        visited[curr_vertex->idx] = true;

        curr_edge = curr_vertex->edges;
        while (curr_edge != NULL) {
            int dist_idx = curr_edge->dst->idx;
            if (!visited[dist_idx]) {
                uint64_t pathsum = dist[curr_vertex->idx] + curr_edge->weight;
                if (pathsum < dist[dist_idx]) {
                    dist[dist_idx] = pathsum;
                    parents[dist_idx] = curr_vertex->key;
                }
            }
            curr_edge = curr_edge->edge_next;
        }
    }


    print_shortest_path_info(start, end, dist, parents, num_vertices);

done:

    if (visited) {
        free(visited);
    }

    if (parents) {
        free(parents);
    }

    if (dist) {
        free(dist);
    }

    return error;
}

int
shortest_path_undirected(graph_t *g, uint64_t src, uint64_t dst)
{
    int error = 0;
    bool *visited = NULL;
    int64_t *dist = NULL;
    uint64_t *parents = NULL;
    uint64_t num_vertices = 0;
    simple_q *q = NULL;
    graph_vertex_t *start = NULL;
    graph_vertex_t *end = NULL;

    if (g == NULL) {
        error = EINVAL;
        goto done;
    }
    num_vertices = g->num_vertices;

    start = find_vertex_from_key(g, src);
    if (start == NULL) {
        error = EINVAL;
        goto done;
    }

    end = find_vertex_from_key(g, dst);
    if (end == NULL) {
        error = EINVAL;
        goto done;
    }

    visited = (bool *)malloc(sizeof(bool) * num_vertices);
    if (visited == NULL) {
        error = ENOMEM;
        goto done;
    }

    dist = (int64_t *)malloc(sizeof(int64_t) * num_vertices);
    if (dist == NULL) {
        error = ENOMEM;
        goto done;
    }

    parents = (uint64_t *)malloc(sizeof(uint64_t) * num_vertices);
    if (parents == NULL) {
        error = ENOMEM;
        goto done;
    }

    for (int i = 0; i < num_vertices; i++) {
        visited[i] = false;
        dist[i] = INT64_MAX;
        parents[i] = UINT64_MAX;
    }

    q = create_simple_q(num_vertices);
    if (q == NULL) {
        error = ENOMEM;
        goto done;
    }

    dist[start->idx] = 0;
    parents[start->idx] = 0;
    simple_q_enqueue(q, (uint64_t)(start));

    while (!simple_q_is_empty(q)) {
        graph_vertex_t *v = NULL;
        graph_edge_t *e = NULL;
        uint64_t temp = 0;

        simple_q_dequeue(q, &temp);
        v = (graph_vertex_t *)(temp);

        e = v->edges;
        while (e != NULL) {
            if (!visited[e->dst->idx]) {
                visited[e->dst->idx] = true;
                parents[e->dst->idx] = v->key;
                dist[e->dst->idx] = dist[v->idx] + 1;
                simple_q_enqueue(q, (uint64_t)(e->dst));
            }
            e = e->edge_next;
        }
    }

    print_shortest_path_info(start, end, dist, parents, num_vertices);

done:
    if (q) {
        destroy_simple_q(q);
    }

    if (parents) {
        free(parents);
    }

    if (dist) {
        free(dist);
    }

    if (visited) {
        free(visited);
    }
    return error;
}

static bool
relax_all_edges(graph_t *g, int64_t *dist, uint64_t *parents)
{
    bool dist_updated = false;
    graph_vertex_t *v = NULL;
    graph_edge_t *e = NULL;

    for (int i = 0; i < g->num_vertices; i++) {
        v = &g->vertices[i];
        e = v->edges;
        while (e != NULL) {
            graph_vertex_t *src = e->src;
            graph_vertex_t *dst = e->dst;
            if ((dist[src->idx] != INT64_MAX) &&
                 (dist[dst->idx] > dist[src->idx] + e->weight)) {
                dist[dst->idx] = dist[src->idx] + e->weight;
                parents[dst->idx] = src->key;
                dist_updated = true;
            }
            e = e->edge_next;
        }
    }

    return dist_updated;
}

int
shortest_path_bellmanford(graph_t *g, uint64_t src, uint64_t dst)
{
    int error = 0;
    int64_t *dist = NULL;
    uint64_t *parents = NULL;
    uint64_t num_vertices = 0;
    graph_vertex_t *start = NULL;
    graph_vertex_t *end = NULL;
    uint64_t relax = 0;

    if (g == NULL) {
        error = EINVAL;
        goto done;
    }
    num_vertices = g->num_vertices;
    relax = num_vertices - 1;

    start = find_vertex_from_key(g, src);
    if (start == NULL) {
        error = EINVAL;
        goto done;
    }

    end = find_vertex_from_key(g, dst);
    if (end == NULL) {
        error = EINVAL;
        goto done;
    }

    dist = (int64_t *)malloc(sizeof(int64_t) * num_vertices);
    if (dist == NULL) {
        error = ENOMEM;
        goto done;
    }

    parents = (uint64_t *)malloc(sizeof(uint64_t) * num_vertices);
    if (parents == NULL) {
        error = ENOMEM;
        goto done;
    }

    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INT64_MAX;
        parents[i] = UINT64_MAX;
    }

    dist[start->idx] = 0;
    parents[start->idx] = 0;

    while (relax > 0) {
        relax_all_edges(g, dist, parents);
        --relax;
    }

    /* Negative cycle detection. */
    if (relax_all_edges(g, dist, parents)) {
        printf("\n\t\tNegative Cycle Detected");
        goto done;
    }

    print_shortest_path_info(start, end, dist, parents, num_vertices);

done:
    if (parents) {
        free(parents);
    }

    if (dist) {
        free(dist);
    }

    return error;
}

