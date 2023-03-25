#pragma once

#include "graph/graph.h"

#include <vector>

using node_name_t = unsigned int;
using node_data_t = bool; // maybe temp
using weight_t = double;
using graph_t = graph::Graph<node_name_t, node_data_t, weight_t>;
using route_t = std::vector<node_name_t>;
