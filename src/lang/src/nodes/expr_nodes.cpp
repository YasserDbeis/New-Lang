#include "../../include/nodes/expr_nodes.h"
#include "../../include/state_mgmt.h"

/* --------------------------------------------
LoadNode implementation
--------------------------------------------- */

LoadNode::LoadNode()
{
}

LoadNode::LoadNode(ExprType type, Type var_type, std::string name, int global_count, bool is_constant)
{
    this->type = type;
    this->var_type = var_type;
    this->name = name;
    this->global_count = global_count;
    this->is_constant = is_constant;
}

LoadNode::LoadNode(ExprType type, Value value, int global_count, bool is_constant)
{
    this->type = type;
    this->value = value;
    this->global_count = global_count;
    this->is_constant = is_constant;
}

void LoadNode::evaluate()
{
    std::unordered_map<Type, std::string> type_to_str =
        {
            {Type::Void, "void"},
            {Type::Int, "int"},
            {Type::Dec, "dec"},
            {Type::String, "str"},
            {Type::Bool, "bool"},
            {Type::Invalid, "Invalid"}};

    if (is_constant == false)
    {
        value = StateMgmt::load_var_stack_trace(name);
    }
    // std::cout << "* * * * * * * * * * * *" << std::endl;
    // std::cout << "Loading evaluate() info" << std::endl;
    // std::cout << "Loading variable " << value.token.lexeme << " of type " << type_to_str[value.type] << std::endl;
    // std::cout << "* * * * * * * * * * * *" << std::endl;
}

void LoadNode::expr_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }

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

    std::cout << "[Load] "
              << "is_constant: " << is_constant
              << ", value: " << type_to_str[token_to_type[value.token.type]] << " " << value.token.lexeme
              << ", name: " << name
              << ", type: " << type_to_str[var_type]
              << ", global count: " << global_count << std::endl;
}

/* --------------------------------------------
ParenNode implementation
--------------------------------------------- */

ParenNode::ParenNode()
{
}

ParenNode::ParenNode(ExprType type, bool is_left)
{
    this->type = type;
    this->is_left = is_left;
}

void ParenNode::expr_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }

    if (is_left == true)
    {
        std::cout << "(" << std::endl;
    }
    else
    {
        std::cout << ")" << std::endl;
    }
}

// Nothing to do

/* --------------------------------------------
OperatorNode implementation
--------------------------------------------- */

OperatorNode::OperatorNode()
{
}

OperatorNode::OperatorNode(ExprType type, OperatorType op_type)
{
    this->type = type;
    this->operator_type = op_type;
}

// Nothing to do
void OperatorNode::expr_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }
    std::unordered_map<OperatorType, std::string> operator_type_to_str =
        {
            {OperatorType::PLUS, "+"},
            {OperatorType::MINUS, "-"},
            {OperatorType::MULT, "*"},
            {OperatorType::DIV, "/"},
            {OperatorType::GT, ">"},
            {OperatorType::LT, "<"},
            {OperatorType::GEQ, ">="},
            {OperatorType::LEQ, "<="},
            {OperatorType::IS, "is"},
            {OperatorType::AND, "and"},
            {OperatorType::OR, "or"},
            {OperatorType::XOR, "xor"},
            {OperatorType::NEQ, "!="}};

    std::cout << operator_type_to_str[operator_type] << std::endl;
}