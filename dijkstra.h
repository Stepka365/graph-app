#pragma once

#include "names.h"

#include <limits>

struct Vertex {
    weight_t sum_to_this = std::numeric_limits<weight_t>::infinity();
    int prev = -1; // int to init with -1
    bool visited = false;
};

std::pair<weight_t, route_t> dijkstra(const graph_t& graph, node_name_t key_from, node_name_t key_to);

void preprocessing(size_t size, node_name_t key_from, node_name_t key_to);

void edges_record(const std::pair<node_name_t, weight_t>& elem,
                  std::vector<Vertex>& vertices, node_name_t chosen);

node_name_t choose_best_vertex(const graph_t& graph, std::vector<Vertex>& vertices);

route_t make_route(const std::vector<Vertex>& vertices, node_name_t key_from, node_name_t key_to);
