#pragma once

#include "inst_node.h"
#include "../expression.h"

class JmpNode : public InstNode
{
public:
    JmpNode();

    void inst_print(int num_tabs = 0) override;
};

class CjmpNode : public InstNode
{
public:
    CjmpNode();
    CjmpNode(Expression expr);

    void execute() override;
    int get_offset() override;

    void inst_print(int num_tabs = 0) override;

private:
    Expression expr;
};

class StoreNode : public InstNode
{
public:
    StoreNode();
    StoreNode(Type type, std::string name, Expression expr, int global_count, bool is_param);

    void execute() override;

    void inst_print(int num_tabs = 0) override;

private:
    Type type;
    std::string name;
    Expression expr;
    Value value;
    int global_count;
    bool is_param;

    void assert_valid_type(Value val, Type expected_type);
    void store_to_curr_context(Value val);
};

class ReturnNode : public InstNode
{
public:
    ReturnNode();

    void execute() override;
    void set_expr(Expression expr);

    void inst_print(int num_tabs = 0) override;

private:
    Expression expr;
    Value value;
};

class ScopeNode : public InstNode
{
public:
    ScopeNode();
    ScopeNode(bool is_new_scope);

    void execute() override;

    void inst_print(int num_tabs = 0) override;

private:
    bool is_new_scope;
};