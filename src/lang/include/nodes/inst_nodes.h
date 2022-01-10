#pragma once

#include "inst_node.h"
#include "../expression.h"

class JmpNode : public InstNode
{
public:
    JmpNode();

    void inst_print() override
    {
        std::cout << "JMP // "
                  << "OFFSET : " << this->get_offset() << std::endl;
    }
};

class CjmpNode : public InstNode
{
public:
    CjmpNode();
    CjmpNode(Expression expr);

    void execute() override;

    void inst_print() override
    {
        std::cout << "CJMP // "
                  << "OFFSET : " << this->get_offset() 
                  << ", Expression: " << std::endl;
        expr.print_expr();
        std::cout << std::endl;
    }

private:
    Expression expr;
};

class StoreNode : public InstNode
{
public:
    StoreNode();
    StoreNode(Type type, std::string name, Expression expr, int global_count, bool is_param);

    void execute() override;

    void inst_print() override
    {
        std::unordered_map<Type, std::string> type_to_str = {
            {Type::Bool, "Bool"},
            {Type::Dec, "Dec"},
            {Type::Int, "Int"},
            {Type::Invalid, "Invalid"},
            {Type::String, "String"},
            {Type::Void, "Void"}};

        std::unordered_map<TokenType, Type> token_to_type =
            {
                {TokenType::BOOL, Type::Bool},
                {TokenType::TRUE, Type::Bool},
                {TokenType::FALSE, Type::Bool},
                {TokenType::STR, Type::String},
                {TokenType::STRING, Type::String},
                {TokenType::DEC, Type::Dec},
                {TokenType::DEC_NUM, Type::Dec},
                {TokenType::INT, Type::Int},
                {TokenType::INT_NUM, Type::Int},
                {TokenType::VOID, Type::Void}};

        std::cout << "STORE // "
                  << "OFFSET: " << this->get_offset()
                  << ", NAME: " << this->name
                  << ", GCOUNT: " << this->global_count
                  << ", IS PARAM: " << this->is_param
                  << ", TYPE: " << type_to_str[this->type]
                  << ", Expression: " << std::endl;
        expr.print_expr();

        std::cout << std::endl;
    }

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
    ReturnNode();

    void execute() override;
    void set_expr(Expression expr);

    void inst_print() override
    {
        std::cout << "RETURN // "
                  << "OFFSET: " << this->get_offset()
                  << ", Expression:" << std::endl;
        expr.print_expr();
        std::cout << std::endl;
    }

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

    void inst_print() override
    {
        std::cout << "SCOPE // "
                  << "OFFSET: " << this->get_offset()
                  << ", IS NEW SCOPE: " << is_new_scope << std::endl;
    }

private:
    bool is_new_scope;
};