/*
    File: error_handler.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-22-2021
    Description: Implements the functionality of the static error methods of the Error Handler class
*/

#include "../include/error_handler.h"
#include <iostream>

void ErrorHandler::error(ErrorPhase err_phase, ErrorType err_type, std::string context, int line_number, ErrorCode err_code)
{
    Error err;

    err.type = err_type;
    err.phase = err_phase;
    err.context = context;
    err.line_number = line_number;
    err.message = code_to_msg(err_code);

    std::string err_output = print(err);
    exit_handler();
}

std::string ErrorHandler::print(Error err)
{
    std::string err_str;
    std::string type_str = type_to_str(err.type);
    std::string phase_str = phase_to_str(err.phase);
    std::string phase_info = "Error occurred in " + phase_str;

    err_str = type_str + "\n" + phase_info + "\n" + err.context + "\n" + err.message + "\n" + std::to_string(err.line_number) + "\n";
    // printf("%s", err_str);
    std::cout << err_str;

    return err_str;
}

void ErrorHandler::exit_handler()
{
    exit(EXIT_FAILURE);
}

std::string ErrorHandler::code_to_msg(ErrorCode code)
{

    switch (code)
    {
    case MISSING_MAIN:
    {
        return "Missing: Main Function";
    }
    case INVALID_TOKEN:
    {
        return "Invalid token";
    }
    case INVALID_NUM:
    {
        return "Invalid number";
    }
    case INVALID_STRING:
    {
        return "Invalid string";
    }
    case INVALID_DEF:
    {
        return "Invalid definition";
    }
    case INVALID_VAR_DEF:
    {
        return "Invalid variable definition";
    }
    case INVALID_PARAM:
    {
        return "Invalid function parameter(s)";
    }
    case INVALID_RET_TYPE:
    {
        return "Invalid return type";
    }
    case INVALID_STMT_LIST:
    {
        return "Invalid statement list";
    }
    case INVALID_STMT:
    {
        return "Invalid statement";
    }
    case INVALID_ALT_COND:
    {
        return "Invalid alternative if condition";
    }
    case INVALID_CTRL_FLOW:
    {
        return "Invalid control flow";
    }
    case INVALID_EXPR:
    {
        return "Invalid expression";
    }
    case INVALID_TERM:
    {
        return "Invalid term";
    }
    case INVALID_FACTOR:
    {
        return "Invalid factor";
    }
    case INVALID_ARG_LIST:
    {
        return "Invalid argument list";
    }
    case INVALID_TYPE:
    {
        return "Invalid type";
    }
    case INVALID_OPERATOR:
    {
        return "Invalid operator";
    }
    case FUNC_NOT_DEF:
    {
        return "Function not defined";
    }
    case FUNC_ALREADY_DEF:
    {
        return "Function already defined";
    }
    case VAR_ALREADY_DEC:
    {
        return "Variable has already been declared";
    }
    case VAR_NOT_DEC:
    {
        return "Variable is not declared";
    }
    case MISSING_FUNC_RETURN:
    {
        return "Return value from function is not available";
    }
    case INVALID_EVAL:
    {
        return "Expression has invalid evaluation";
    }
    case EMPTY_STK_TRACE:
    {
        return "Empty stack trace";
    }
    case INVALID_OPERAND:
    {
        return "Operand deemed invalid during evaluation";
    }
    case INVALID_OPERATION:
    {
        return "Operation is not valid";
    }
    case INVALID_RETURN_VALUE:
    {
        return "Return value does not match function return type";
    }
    default:
    {
        return "General Error";
    }
    }
}

std::string ErrorHandler::type_to_str(ErrorType type)
{
    switch (type)
    {
    case ErrorType::SYNTAX_ERROR:
    {
        return "SYNTAX ERROR";
    }
    case ErrorType::RUNTIME_ERROR:
    {
        return "RUNTIME ERROR";
    }
    case ErrorType::RUNTIME_EXCEPTION:
    {
        return "RUNTIME EXCEPTION";
    }
    default:
    {
        printf("Error type not found");
        exit(EXIT_FAILURE);
    }
    }
}

std::string ErrorHandler::phase_to_str(ErrorPhase phase)
{
    switch (phase)
    {
    case ErrorPhase::LEXICAL_ANALYSIS:
    {
        return "Lexical Analysis";
    }
    case ErrorPhase::PARSING:
    {
        return "Parsing";
    }
    case ErrorPhase::COMPILATION:
    {
        return "Compilation";
    }
    case ErrorPhase::EXECUTION:
    {
        return "Execution";
    }
    default:
    {
        printf("Error phase not found");
        exit(EXIT_FAILURE);
    }
    }
}