#pragma once

#include "names.h"

void error(std::exception& error);

void print_results(weight_t weight, const route_t& route);

std::tuple<const char*, node_name_t, node_name_t> parse_args(int arg_count, char* arg_vars[]);