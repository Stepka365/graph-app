#include "dijkstra.h"


std::pair<weight_t, route_t> dijkstra(const graph_t& graph, node_name_t key_from, node_name_t key_to) {
    preprocessing(graph.size(), key_from, key_to);
    std::vector<Vertex> vertices(graph.size());
    vertices[key_from].sum_to_this = 0;
    node_name_t chosen = key_from;
    for (node_name_t i = 0; i < graph.size(); ++i) {
        for (const auto& elem: graph.find(chosen)->second) {
            edges_record(elem, vertices, chosen);
        }
        vertices[chosen].visited = true;
        chosen = choose_best_vertex(graph, vertices);
    }
    return std::pair<weight_t, route_t>{vertices[key_to].sum_to_this,
                                        make_route(vertices, key_from, key_to)};
}

void preprocessing(size_t size, node_name_t key_from, node_name_t key_to) {
    if (key_from >= size) { throw std::runtime_error("Dijkstra :: key_from is incorrect"); }
    if (key_to >= size) { throw std::runtime_error("Dijkstra :: key_to is incorrect"); }
    if (key_from == key_to) { throw std::runtime_error("route: There is the only vertex\nweight: 0"); }
}

void edges_record(const std::pair<node_name_t, weight_t>& elem,
                  std::vector<Vertex>& vertices, node_name_t chosen) {
    if (elem.second < 0) { throw std::runtime_error("Dijkstra :: incorrect graph :: weight < 0"); }
    Vertex& vertex_to = vertices[elem.first];
    if (!vertex_to.visited && vertices[chosen].sum_to_this + elem.second < vertex_to.sum_to_this) {
        vertex_to.sum_to_this = vertices[chosen].sum_to_this + elem.second;
        vertex_to.prev = chosen;
    }
}

node_name_t choose_best_vertex(const graph_t& graph, std::vector<Vertex>& vertices) {
    node_name_t chosen;
    weight_t min = std::numeric_limits<weight_t>::infinity();
    for (size_t i = 0; i < graph.size(); ++i) {
        if (!vertices[i].visited && vertices[i].sum_to_this < min) {
            min = vertices[i].sum_to_this;
            chosen = i;
        }
    }
    return chosen;
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

