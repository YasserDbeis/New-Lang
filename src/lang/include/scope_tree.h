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

    void set_var(std::string name, Value val, int value); // throw error if already there
    std::pair<Value, bool> get_var(std::string name);

private:
    int last_entry;

    void push(std::unordered_map<std::string, Value>);
    void pop();
    bool in_curr_scope(std::string name);
    std::unordered_map<std::string, Value> peek();
};