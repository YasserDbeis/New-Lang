#pragma once

#include "nodes/inst_node.h"
#include "parser.h"
#include <list>
#include <string>

class Compiler
{
public:
    Compiler();
    Compiler(std::string input);

    std::list<InstNode> get_global_nodes();

private:
    int global_count;
    std::list<InstNode> global_nodes;
    Parser parser;
};