#pragma once

#include "nodes/inst_node.h"
#include "parser.h"
#include <string>

class Compiler
{
public:
    Compiler();
    Compiler(std::string input);

    std::vector<InstNode *> get_global_instructions();

    Parser parser;

private:
    int global_count;
};