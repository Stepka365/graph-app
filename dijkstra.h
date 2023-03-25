#pragma once

#include "names.h"

#include <limits>

struct Vertex {
    weight_t sum_to_this = std::numeric_limits<weight_t>::infinity();
    int prev = -1; // int to init with -1
    bool visited = false;
};

using route_t = std::vector<node_name_t>;

std::pair<weight_t, route_t> dijkstra(const graph_t& graph, node_name_t key_from, node_name_t key_to);

void preprocessing(const node_name_t& key, size_t size);

route_t make_route(const std::vector<Vertex>& vertices, node_name_t key_from, node_name_t key_to);
