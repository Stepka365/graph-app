#pragma once

#include "names.h"

#include <fstream>

graph_t read_graph(const char* file_name);

graph_t read_first_line(std::fstream& file);

void read_line(std::fstream& file, graph_t& graph, size_t i);
