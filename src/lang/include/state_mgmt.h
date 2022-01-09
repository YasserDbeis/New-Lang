#pragma once

#include "value.h"
#include "error_handler.h"
#include "scope_tree.h"
#include <stack>
#include <string>
#include <unordered_map>
#include <queue>

class StateMgmt
{
public:
    static std::queue<Value> arg_queue;

    static void create_new_scope();       /* Stack trace helper function */
    static void delete_curr_scope();      /* Stack trace helper function */
    static Value get_func_return_value(); /* Stack trace helper function */

    static Value load_var(std::string id);
    static void store_var(Value value, int global_count);

private:
    typedef struct StackFrame
    {
        ScopeTree scope_tree;
        std::string func_id;
        Value return_value;
    } StackFrame;

    static std::stack<StackFrame> stack_trace;
    static std::unordered_map<std::string, std::pair<Value, int>> global_vars;
};
