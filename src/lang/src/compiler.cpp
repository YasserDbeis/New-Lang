#include "../include/compiler.h"

Compiler::Compiler()
{
    global_count = 0;
}

Compiler::Compiler(std::string input) : parser(input)
{
    global_count = 0;
}

std::vector<InstNode *> Compiler::get_global_instructions()
{
    return parser.get_global_instructions();
}