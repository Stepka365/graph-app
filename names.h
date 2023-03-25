#pragma once

#include "graph/graph.h"

#include <limits>
#include <vector>

struct Vertex;

using node_name_t = size_t;
using node_data_t = Vertex; // maybe temp
using weight_t = double;
using graph_t = graph::Graph<node_name_t, node_data_t, weight_t>;
using route_t = std::vector<node_name_t>;

struct Vertex {
    weight_t sum_to_this = std::numeric_limits<weight_t>::infinity();
    int prev = -1; // int to init with -1
    bool visited = false;
};
