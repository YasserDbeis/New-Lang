#include "../include/scope_tree.h"
#include "../include/state_mgmt.h"
#include <iostream>

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

/*
    Inserts the {name, val} into the hashtable of the last element of the scope_list

    Use cases - int x = 5; OR x = 5 - var def or var dec

    Throws error if the scope_list is empty
*/
void ScopeTree::add_var(std::string name, Value val)
{
    if (in_curr_scope(name) == false)
    {
        scope_list.back()[name] = val;
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::RUNTIME_ERROR, "Variable " + name + " has already been declared in this scope", -1, VAR_ALREADY_DEC);
    }
}

/*
    Updates the value associated to the name key in the hashtable of the last element of the scope_list

    Use cases - x = 5

    Throws error if the scope_list is empty, or if the variable does not exist anywhere in the scope_list or global vars hashtable
*/
void ScopeTree::update_var(std::string name, Value val)
{
    int ix_in_scope_list = find_in_scope_list(name);

    if (ix_in_scope_list != -1)
    {
        scope_list[ix_in_scope_list][name] = val;
    }
    else
    {
        StateMgmt::store_global_var(name, val);
    }
}

Value ScopeTree::get_var(std::string name)
{
    int ix_in_scope_list = find_in_scope_list(name);

    if (ix_in_scope_list != -1)
    {
        return scope_list[ix_in_scope_list][name];
    }
    else
    {
        return StateMgmt::load_global_var(name);
    }
}

void ScopeTree::push()
{
    std::unordered_map<std::string, Value> new_hashtable;
    scope_list.push_back(new_hashtable);
}

void ScopeTree::pop()
{
    scope_list.pop_back();
}

bool ScopeTree::in_curr_scope(std::string name)
{
    if (scope_list.empty() == false)
    {
        return scope_list.back().count(name) == 1;
    }
    else
    {
        return false;
    }
}

int ScopeTree::find_in_scope_list(std::string id)
{
    int num_scopes = scope_list.size();
    for (int i = num_scopes - 1; i >= 0; i--)
    {
        auto search = scope_list[i].find(id);
        if (search != scope_list[i].end())
        {
            return i;
        }
    }

    // returning -1 (invalid index) indicates var not found
    return -1;
}

void ScopeTree::print_scope_tree()
{
    std::unordered_map<Type, std::string> type_to_str =
        {
            {Type::Void, "void"},
            {Type::Int, "int"},
            {Type::Dec, "dec"},
            {Type::String, "str"},
            {Type::Bool, "bool"},
            {Type::Invalid, "Invalid"}};

    if (scope_list.empty())
    {
        std::cout << "No variables to show" << std::endl;
    }

    int num_scopes = scope_list.size();
    for (int i = num_scopes - 1; i >= 0; i--)
    {
        std::cout << "-----------------" << std::endl;

        // print key value pairs
        for (const auto &[id, value] : scope_list[i])
        {
            std::cout << "variable: " << id << ": " << value.token.lexeme << ": " << type_to_str[value.type] << std::endl;
        }

        std::cout << "-----------------" << std::endl;
    }
}

bool ScopeTree::is_var_declared(std::string id)
{
    int ix = find_in_scope_list(id);
    return ix >= 0;
}