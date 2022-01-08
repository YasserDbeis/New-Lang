#pragma once

#include "inst_node.h"
#include "../expression.h"

class JmpNode : public InstNode
{
public:
    InstNode *target;
};

class CjmpNode : public InstNode
{
public:
    InstNode *target;
    Expression expr;

    void execute() override;
    InstNode *get_next() override;
};

class StoreNode : public InstNode
{

public:
    Type type;
    std::string name;
    Expression expr;
    Value value;
    int global_count;
    bool is_param;

    void execute() override;
};

class ReturnNode : public InstNode
{
public:
    Expression expr;
    Value value;

    void execute() override;
};

class ScopeNode : public InstNode
{
public:
    bool is_new_scope;

    void execute() override;
};