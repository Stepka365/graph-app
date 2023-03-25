#include "input.h"

#include <fstream>

graph_t read_graph(const char* file_name) {
    std::fstream file(file_name);
    if (!file.is_open()) { throw std::runtime_error("File doesn't exist"); }
    graph_t graph;
    weight_t weight;
    char test;
    if (!(file >> test && test == '|' && file >> weight)) {
        throw std::runtime_error("Incorrect input");
    }
    graph.insert_node(0, {});
    if (weight != 0) { graph.insert_edge({0, 0}, weight); }
    while (file >> weight) {
        graph.insert_node(graph.size(), {});
        if (weight != 0) { graph.insert_edge({0, graph.size() - 1}, weight); }
    }
    file.clear();
    if (!(file >> test && test == '|')) { throw std::runtime_error("Incorrect input"); }
    for (size_t i = 1; i < graph.size(); ++i) {
        if (!(file >> test && test == '|')) { throw std::runtime_error("Incorrect input"); }
        for (size_t j = 0; j < graph.size(); ++j) {
            if (!(file >> weight)) { throw std::runtime_error("Incorrect input"); }
            if (weight != 0) { graph.insert_edge({i, j}, weight); }
        }
        if (!(file >> test && test == '|')) { throw std::runtime_error("Incorrect input"); }
    }
    return graph;
}
