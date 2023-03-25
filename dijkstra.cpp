#include "dijkstra.h"

std::pair<weight_t, route_t> dijkstra(graph_t& graph, node_name_t key_from, node_name_t key_to) {
    preprocessing(graph.size(), key_from, key_to);
    graph[key_from].value().sum_to_this = 0;
    node_name_t chosen = key_from;
    for (node_name_t i = 0; i < graph.size(); ++i) {
        for (const auto& elem: graph.find(chosen)->second) {
            edges_record(elem, graph, chosen);
        }
        graph[chosen].value().visited = true;
        chosen = choose_best_vertex(graph);
    }
    return std::pair<weight_t, route_t>{
            graph[key_to].value().sum_to_this, make_route(graph, key_from, key_to)};
}

void preprocessing(size_t size, node_name_t key_from, node_name_t key_to) {
    if (key_from >= size) { throw std::runtime_error("Dijkstra :: key_from is incorrect"); }
    if (key_to >= size) { throw std::runtime_error("Dijkstra :: key_to is incorrect"); }
    if (key_from == key_to) { throw std::runtime_error("route: There is the only vertex\nweight: 0"); }
}

void edges_record(const std::pair<node_name_t, weight_t>& elem,
                  graph_t& graph, node_name_t chosen) {
    if (elem.second < 0) { throw std::runtime_error("Dijkstra :: incorrect graph :: weight < 0"); }
    Vertex& vertex_to = graph[elem.first].value();
    if (!vertex_to.visited && graph[chosen].value().sum_to_this + elem.second < vertex_to.sum_to_this) {
        vertex_to.sum_to_this = graph[chosen].value().sum_to_this + elem.second;
        vertex_to.prev = chosen;
    }
}

node_name_t choose_best_vertex(graph_t& graph) {
    node_name_t chosen;
    weight_t min = std::numeric_limits<weight_t>::infinity();
    for (size_t i = 0; i < graph.size(); ++i) {
        if (!graph[i].value().visited && graph[i].value().sum_to_this < min) {
            min = graph[i].value().sum_to_this;
            chosen = i;
        }
    }
    return chosen;
}

route_t make_route(graph_t& graph, node_name_t key_from, node_name_t key_to) {
    if (graph[key_to].value().prev == -1) {
        throw std::runtime_error("Impossible to reach " + std::to_string(key_to)
                                 + " from " + std::to_string(key_from));
    }
    route_t route;
    route.push_back(key_to);
    while (graph[route.back()].value().prev != -1) {
        route.push_back(graph[route.back()].value().prev);
    }
    std::reverse(route.begin(), route.end());
    return route;
}
