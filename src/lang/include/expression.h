#pragma once

#include "value.h"
#include "nodes/expr_nodes.h"
#include "nodes/inst_expr_nodes.h"
#include "func_def_table.h"
#include "assert.h"
#include <vector>
#include <deque>
#include <stack>
#include <unordered_map>

// class FuncCallNode;

enum class Assoc
{
    LEFT,
    RIGHT
};

class Expression
{
public:
    Value value;
    std::vector<ExprNode *> term_list;

    Expression();
    Expression(std::vector<ExprNode *> terms);
    Expression(Value value);
    void evaluate();

    void print_expr(int num_tabs = 0);

private:
    std::deque<ExprNode *> infix_to_rev_polish();
    bool compare_precedence(ExprNode *op1, ExprNode *op2);
    bool is_left_paren(ExprNode *op);
    Value get_expr_node_value(ExprNode *op);
    Value compute(Value val1, Value val2, OperatorType type);
    void assert_valid_type(Value val1, Value val2, OperatorType type);

    bool values_are_equal(Value val1, Value val2);

    bool values_xor(Value val1, Value val2);
    bool values_and(Value val1, Value val2);
    bool values_or(Value val1, Value val2);

    bool values_less_than(Value val1, Value val2);
    bool values_greater_than(Value val1, Value val2);

    std::unordered_map<OperatorType, int> op_to_prec =
        {
            {OperatorType::PLUS, 11},
            {OperatorType::MINUS, 11},
            {OperatorType::MULT, 12},
            {OperatorType::DIV, 12},
            {OperatorType::GT, 9},
            {OperatorType::LT, 9},
            {OperatorType::GEQ, 9},
            {OperatorType::LEQ, 9},
            {OperatorType::IS, 8},
            {OperatorType::AND, 4},
            {OperatorType::OR, 3},
            {OperatorType::XOR, 6},
            {OperatorType::NEQ, 8}};

    std::unordered_map<OperatorType, Assoc> op_to_assoc = {
        {OperatorType::PLUS, Assoc::LEFT},
        {OperatorType::MINUS, Assoc::LEFT},
        {OperatorType::MULT, Assoc::LEFT},
        {OperatorType::DIV, Assoc::LEFT},
        {OperatorType::GT, Assoc::LEFT},
        {OperatorType::LT, Assoc::LEFT},
        {OperatorType::GEQ, Assoc::LEFT},
        {OperatorType::LEQ, Assoc::LEFT},
        {OperatorType::IS, Assoc::LEFT},
        {OperatorType::AND, Assoc::LEFT},
        {OperatorType::OR, Assoc::LEFT},
        {OperatorType::XOR, Assoc::LEFT},
        {OperatorType::NEQ, Assoc::LEFT},
    };
};