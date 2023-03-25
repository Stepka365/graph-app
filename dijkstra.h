#pragma once

#include "names.h"

std::pair<weight_t, route_t> dijkstra(graph_t& graph, node_name_t key_from, node_name_t key_to);
