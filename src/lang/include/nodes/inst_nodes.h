#pragma once

#include "inst_node.h"
#include "../expression.h"

class JmpNode : public InstNode
{
public:
    InstNode *target;

    JmpNode();
    JmpNode(InstNode *target);
};

class CjmpNode : public InstNode
{
public:
    CjmpNode();
    CjmpNode(Expression expr);

    void execute() override;
    InstNode *get_next() override;

private:
    InstNode *target;
    Expression expr;
};

class StoreNode : public InstNode
{
public:
    StoreNode();
    StoreNode(Type type, std::string name, Expression expr, int global_count, bool is_param);

    void execute() override;

private:
    Type type;
    std::string name;
    Expression expr;
    Value value;
    int global_count;
    bool is_param;
};

class ReturnNode : public InstNode
{
public:
    bool expr_exists = true;

    ReturnNode();

    void execute() override;
    void set_no_expr();
    void set_expr(Expression expr);

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

private:
    bool is_new_scope;
};