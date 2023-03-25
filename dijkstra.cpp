#include "dijkstra.h"


std::pair<weight_t, route_t> dijkstra(const graph_t& graph, node_name_t key_from, node_name_t key_to) {
    preprocessing(key_from, graph.size());
    preprocessing(key_to, graph.size());
    std::vector<Vertex> vertices(graph.size());
    vertices[key_from].sum_to_this = 0;
    node_name_t chosen = key_from;
    auto edges_check = [&vertices, &chosen](std::pair<node_name_t, weight_t> it) {
        if (it.second < 0) { throw std::runtime_error("Dijkstra :: incorrect graph :: weight < 0"); }
        Vertex& vertex_to = vertices[it.first];
        if (!vertex_to.visited && vertices[chosen].sum_to_this + it.second < vertex_to.sum_to_this) {
            vertex_to.sum_to_this = vertices[chosen].sum_to_this + it.second;
            vertex_to.prev = chosen;
        }
    };
    for (node_name_t i = 0; i < graph.size(); ++i) {
        auto cur_node = graph.find(chosen)->second;
        std::for_each(cur_node.begin(), cur_node.end(), edges_check);
        vertices[chosen].visited = true;
        weight_t min = std::numeric_limits<weight_t>::infinity();
        for (size_t j = 0; j < graph.size(); ++j) {
            if (!vertices[j].visited && vertices[j].sum_to_this < min) {
                min = vertices[j].sum_to_this;
                chosen = j;
            }
        }
    }
    return std::pair<weight_t, route_t>{vertices[key_to].sum_to_this, make_route(vertices, key_from, key_to)};
}

void preprocessing(const node_name_t& key, size_t size) {
    if (key < 0 || key >= size) { throw std::runtime_error("Dijkstra :: key is incorrect"); }
}

route_t make_route(const std::vector<Vertex>& vertices, node_name_t key_from, node_name_t key_to) {
    if (vertices[key_to].prev == -1) {
        throw std::runtime_error("Impossible to reach " + std::to_string(key_to)
                                 + " from " + std::to_string(key_from));
    }
    route_t route;
    route.push_back(key_to);
    while (vertices[route.back()].prev != -1) {
        route.push_back(vertices[route.back()].prev);
    }
    std::reverse(route.begin(), route.end());
    return route;
}

