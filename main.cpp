#include "procedure.h"

int main(int arg_count, char* arg_vars[]) {
    try {
        auto [file, from, to] = parse_args(arg_count, arg_vars);
        print_results(3.14, {from, to});
    }
    catch (std::exception& e) {
        error(e);
    }
    return 0;
}
