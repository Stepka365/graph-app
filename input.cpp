#include "input.h"

graph_t read_graph(const char* file_name) {
    std::fstream file(file_name);
    if (!file.is_open()) { throw std::runtime_error("read_graph :: Impossible to open file"); }
    graph_t graph = read_first_line(file);

    for (size_t i = 1; i < graph.size(); ++i) {
        read_line(file, graph, i);
    }
    char stick;
    if (file >> stick) {
        throw std::runtime_error("read_graph :: Incorrect input");
    }
    return graph;
}

graph_t read_first_line(std::fstream& file) {
    graph_t graph;
    weight_t weight;
    char stick;
    if (!(file >> stick && stick == '|' && file >> weight)) {
        throw std::runtime_error("read_graph :: Incorrect input :: | expected but not found");
    }
    graph.insert_node(0, {});
    if (weight != 0) { graph.insert_edge({0, 0}, weight); }
    while (file >> weight) {
        graph.insert_node(graph.size(), {});
        if (weight != 0) { graph.insert_edge({0, graph.size() - 1}, weight); }
    }
    file.clear();
    if (!(file >> stick && stick == '|')) {
        if (file >> stick && stick == '|') {
            throw std::runtime_error("read_graph :: Incorrect input :: | expected but not found");
        }
        throw std::runtime_error("read_graph :: Incorrect input :: incorrect weight");
    }
    return graph;
}

void read_line(std::fstream& file, graph_t& graph, size_t i) {
    if (file.eof()) {
        throw std::runtime_error("read_graph :: Incorrect input :: matrix shape is incorrect");
    }
    weight_t weight;
    char stick;
    if (!(file >> stick && stick == '|')) {
        throw std::runtime_error("read_graph :: Incorrect input :: | expected but not found");
    }
    for (size_t j = 0; j < graph.size(); ++j) {
        if (!(file >> weight)) {
            throw std::runtime_error("read_graph :: Incorrect input :: incorrect weight");
        }
        if (weight != 0) { graph.insert_edge({i, j}, weight); }
    }
    if (!(file >> stick && stick == '|')) {
        throw std::runtime_error("read_graph :: Incorrect input :: | expected but not found");
    }
}

