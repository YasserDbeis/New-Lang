#include "../include/scope_tree.h"

/*
class ScopeTree
{
public:
    std::vector<std::unordered_map<std::string, Value>> scope_list;

    void set_var(std::string name, Value val, int value); // throw error if already there
    std::pair<Value, bool> get_var(std::string name);

private:
    void push(std::unordered_map<std::string, Value>);
    void pop();
    bool in_curr_scope(std::string name);
    std::unordered_map<std::string, Value> peek();
};
*/

void ScopeTree::set_var(std::string name, Value val, int value)
{
}

std::pair<Value, bool> ScopeTree::get_var(std::string name)
{
    return std::make_pair(Value(), false);
}

void ScopeTree::push(std::unordered_map<std::string, Value>)
{
}
void ScopeTree::pop()
{
}

bool ScopeTree::in_curr_scope(std::string name)
{
    return false;
}

std::unordered_map<std::string, Value> ScopeTree::peek()
{
    return scope_list.at(scope_list.size() - 1);
}