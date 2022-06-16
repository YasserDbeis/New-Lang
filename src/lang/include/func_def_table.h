#pragma once

#include "value.h"
#include "nodes/inst_node.h"
#include <list>
#include <unordered_map>
#include <string>
#include <vector>
#include "error_handler.h"

class FuncDefTable
{
public:
    static void reset_func_table();

    static std::vector<InstNode *> get_function(std::string id);
    static bool function_exists(std::string id);
    static int get_global_count(std::string id);
    static std::vector<std::pair<Type, std::string>> get_params(std::string id);
    static Type get_return_type(std::string id);

    static void add_entry(std::string id, int global_count, std::vector<std::pair<Type, std::string>> params, Type return_type, std::vector<InstNode *> inst_list);

private:
    typedef struct FuncDef
    {
        std::vector<InstNode *> instruction_list;
        int max_global_count;
        std::vector<std::pair<Type, std::string>> params;
        Type return_type;
    } FuncDef;

    inline static std::unordered_map<std::string, FuncDef> table;
    static void assert_func_exists(std::string id);
    static void assert_func_not_exists(std::string id);
};