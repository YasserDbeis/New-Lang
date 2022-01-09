/*
- compiler: Compiler
+ Executioner(string input)
-  execute_program(global_nodes: InstNode*): void
*/

#pragma once
#include <string>
#include <queue>
#include <stack>
#include "compiler.h"

class Executioner
{
public:
    Executioner();
    Executioner(std::string input);

private:
    Compiler compiler;
};