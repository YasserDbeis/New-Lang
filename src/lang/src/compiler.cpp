#include "../include/compiler.h"

Compiler::Compiler()
{
    global_count = 0;
}

Compiler::Compiler(std::string input) : parser(input)
{
    global_count = 0;
}

std::list<InstNode> Compiler::get_global_nodes()
{
    return global_nodes;
}