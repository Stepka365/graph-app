#include "procedure.h"
#include "input.h"
#include "dijkstra.h"

int main(int arg_count, char* arg_vars[]) {
    try {
        auto [file, from, to] = parse_args(arg_count, arg_vars);
        graph_t graph = read_graph(file);
        auto [length, route] = dijkstra(graph, from, to);
        print_results(length, route);
    }
    catch (std::exception& e) {
        error(e);
        return 1;
    }
    return 0;
}
