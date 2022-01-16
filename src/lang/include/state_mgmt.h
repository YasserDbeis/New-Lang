#pragma once

#include "value.h"
#include "error_handler.h"
#include "scope_tree.h"
#include "func_def_table.h"
#include <stack>
#include <string>
#include <unordered_map>
#include <queue>

class StateMgmt
{
public:
    typedef struct StackFrame
    {
        ScopeTree scope_tree;
        std::string func_id;
        Value return_value;
    } StackFrame;

    inline static std::queue<Value> arg_queue;
    inline static std::stack<StackFrame> stack_trace;

    static void create_new_stack_frame(std::string func_id); /* Stack trace helper function */
    static void delete_curr_stack_frame();                   /* Stack trace helper function */
    static Value get_func_return_value();                    /* Stack trace helper function */
    static std::string get_curr_func_name();

    static Value load_global_var(std::string id);
    static void store_global_var(std::string id, Value value, int global_count);
    static void store_global_var(std::string id, Value value);

    static void store_var_stack_trace(std::string name, Value value);
    static void store_return_val_stack_trace(Value value);
    static Value load_return_val_stack_trace();
    static Value load_var_stack_trace(std::string name);

    static bool is_var_declared(std::string name);
    
    static void print_stack_trace();

private:
    inline static std::unordered_map<std::string, std::pair<Value, int>> global_vars;

    static void print_stack_recursively(); // helper function to print stack trace
};
