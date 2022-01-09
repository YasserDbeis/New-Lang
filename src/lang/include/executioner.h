/*
- compiler: Compiler
+ Executioner(string input)
-  execute_program(global_nodes: InstNode*): void
*/

#pragma once

#include "nodes/inst_node.h"
#include "compiler.h"
#include <string>
#include <queue>
#include <stack>

class Executioner
{
public:
    Executioner();
    Executioner(std::string input);

private:
    Compiler compiler;

    void execute_program();
    void execute_inst_list(std::list<InstNode> inst_list);
};