#include "procedure.h"

#include <cstring>
#include <sstream>
#include <iostream>

void error(std::exception& error) {
    std::cerr << error.what();
}

void print_results(weight_t weight, const route_t& route) {
    std::cout << "route: ";
    for (auto elem: route) {
        std::cout << elem << ' ';
    }
    std::cout << "\nweight: " << weight;
}

node_name_t make_node_name(const char* from) {
    using namespace std::string_literals;
    std::stringstream sstr;
    sstr << from;
    size_t name;
    if (!(sstr >> name && sstr.eof())) {
        throw std::runtime_error("Invalid argument: "s + from);
    }
    return name;
}

std::tuple<const char*, node_name_t, node_name_t> parse_args(int arg_count, char* arg_vars[]) {
    using namespace std::string_literals;
    if (arg_count != 7) {
        throw std::runtime_error("Invalid number of arguments");
    }
    auto equal = [](const char* s1, const char* s2) { return strcmp(s1, s2) == 0; };
    auto hash = [](const char* s) { return strlen(s); };
    std::unordered_map<const char*, const char*, decltype(hash), decltype(equal)> args(3, hash, equal);
    args = {{"--file", nullptr},
            {"--from", nullptr},
            {"--to",   nullptr}};
    for (size_t i = 1; i < 7; i += 2) {
        auto it = args.find(arg_vars[i]);
        if (it == args.end()) {
            throw std::runtime_error("Invalid argument: "s + arg_vars[i]);
        }
        if (it->second) {
            throw std::runtime_error("Duplicated argument: "s + arg_vars[i]);
        }
        it->second = arg_vars[i + 1];
    }
    return {args["--file"], make_node_name(args["--from"]), make_node_name(args["--to"])};
}
