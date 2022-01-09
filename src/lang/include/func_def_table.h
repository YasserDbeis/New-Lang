#pragma once

#include "value.h"
#include "nodes/inst_node.h"
#include <list>
#include <unordered_map>
#include <string>
#include <vector>

class FuncDefTable
{
public:
    static std::list<InstNode> get_function(std::string id);
    static int get_global_count(std::string id);
    static std::vector<std::pair<Type, std::string>> get_params();
    static Type get_return_type(std::string id);

private:
    typedef struct FuncDef
    {
        std::list<InstNode> instruction_list;
        int max_global_count;
        std::vector<std::pair<Type, std::string>> params;
        Type return_type;
    } FuncDef;

    static std::unordered_map<std::string, FuncDef> table;
};