/*
 * Copyright (c) 2025 Vedant Mathur
 *
 * Graph Data Structure Operations
 */

#include <stdint.h>
#include <stdbool.h>

struct graph_vertex_s;
struct graph_edge_s;

/*
 * Representation of a vertex in a graph.
 *
 * This object contains -
 *      key - Key of the vertex
 *      idx - Index of this vertex in Graph array of vertices.
 *      edges - List of all edges from this vertex.
 */
typedef struct graph_vertex_s {
    uint64_t key;
    uint16_t idx;
    struct graph_edge_s *edges;
} graph_vertex_t;

/*
 * Representation of a edge in a graph.
 *
 * This object contains -
 *
 *      src - vertex from which the edge originates
 *      dst - vertex to which the edge points at.
 *      weight - weight of the edge
 */
typedef struct graph_edge_s {
    graph_vertex_t *src;
    graph_vertex_t *dst;
    int64_t weight;
    struct graph_edge_s *edge_next;
} graph_edge_t;

/*
 * Primary Graph Structure which is represented
 * by a linked list of vertices. The vertices
 * internally hold the edges information for each
 * graph.
 */
typedef struct graph_s {
    graph_vertex_t *vertices;
    uint64_t num_vertices;
    uint16_t next_vertex_index;
    bool is_directed;
} graph_t;


/*
 * Graph LifeCycle.
 */
graph_t *create_graph(uint64_t num_vertices, bool is_directed);
void delete_graph(graph_t *g);

/*
 * Graph Vertex and Edge additions.
 */
int add_vertex(graph_t *g, uint64_t key);
int add_edge(graph_t *g, uint64_t src_vertex, uint64_t dst_vertex,
             uint64_t weight);

/*
 * Graph Print.
 */
void print_graph(graph_t *g);

/*
 * Graph Traversals - DFS and BFS
 */
typedef void (*graphtraversalcb)(graph_vertex_t *v);
int graph_dfs(graph_t *g, uint64_t start_vertex, bool *has_cycle,
              graphtraversalcb cb);
int graph_bfs(graph_t *g, uint64_t start_vertex, graphtraversalcb cb);

/*
 * Graph utility functions.
 */
graph_t *
graph_from_adjmatrix(int **adjm, uint64_t numvertices, bool isdirected);

/*
 * Graph Cycle Detection
 */
bool has_cycle(graph_t *g);

/*
 * Graph Shortest Path Algos.
 */
int shortest_path_dijkstra(graph_t *g, uint64_t src, uint64_t dst);
int shortest_path_undirected(graph_t *g, uint64_t src, uint64_t dst);
int shortest_path_bellmanford(graph_t *g, uint64_t src, uint64_t dst);
