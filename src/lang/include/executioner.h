/*
- compiler: Compiler
+ Executioner(string input)
-  execute_program(global_nodes: InstNode*): void
*/

#pragma once

#include "nodes/inst_node.h"
#include "compiler.h"
#include "func_def_table.h"
#include <string>
#include <queue>
#include <stack>

class Executioner
{
public:
    Executioner();
    Executioner(std::string input);

    static void execute_instructions(std::vector<InstNode *> instructions);

private:
    Compiler compiler;

    void execute_program();
};