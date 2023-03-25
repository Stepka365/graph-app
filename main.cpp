#include "procedure.h"
#include "input.h"

int main(int arg_count, char* arg_vars[]) {
    try {
        auto [file, from, to] = parse_args(arg_count, arg_vars);
        graph_t graph = read_graph(file);
        print_results(3.14, {from, to});
    }
    catch (std::exception& e) {
        error(e);
        return 1;
    }
    return 0;
}
