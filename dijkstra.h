#pragma once

#include "names.h"

std::pair<weight_t, route_t> dijkstra(graph_t& graph, node_name_t key_from, node_name_t key_to);

void preprocessing(size_t size, node_name_t key_from, node_name_t key_to);

void edges_record(const std::pair<node_name_t, weight_t>& elem, graph_t& graph, node_name_t chosen);

node_name_t choose_best_vertex(graph_t& graph);

route_t make_route(graph_t& graph, node_name_t key_from, node_name_t key_to);
