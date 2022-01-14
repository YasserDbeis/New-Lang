#pragma once

#include "value.h"
#include <unordered_map>
#include <vector>

// + scope_list:vector<unordered_map<string, Value>>
// - last_entry: int

// + set_var(string name, Value val, int value): bool
// + get_var(string name): Value
// - push(Map<string, Value> scope_map):void
// - pop(): void
// - peek(): Map<string, Value>

class ScopeTree
{
public:
    std::vector<std::unordered_map<std::string, Value>> scope_list;

    void add_var(std::string name, Value val);    // throw error if already there or scope list is empty
    void update_var(std::string name, Value val); // throw error if not declared, or scope list is empty
    Value get_var(std::string name);
    void push();
    void pop();

    void print_scope_tree();
    bool is_var_declared(std::string name);

private:
    bool in_curr_scope(std::string name);
    int find_in_scope_list(std::string name);
};