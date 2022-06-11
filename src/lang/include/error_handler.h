/*
    File: error_handler.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-22-2021
    Description: Declares the Error Handler class. The goal of this class is to
                 have unified error/exception handling for the lexer, parser, and compiler.
                 Handling errors involves returning detailed error feedback concerning
                 what went wrong and where in the code it occured.
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "token.h"

enum class ErrorPhase
{
    LEXICAL_ANALYSIS,
    PARSING,
    COMPILATION,
    EXECUTION
};
enum class ErrorType
{
    SYNTAX_ERROR,
    RUNTIME_ERROR,
    RUNTIME_EXCEPTION
};
enum ErrorCode
{
    MISSING_MAIN,
    INVALID_TOKEN,
    INVALID_NUM,
    INVALID_STRING,
    INVALID_DEF,
    INVALID_VAR_DEF,
    INVALID_PARAM,
    INVALID_RET_TYPE,
    INVALID_STMT_LIST,
    INVALID_STMT,
    INVALID_ALT_COND,
    INVALID_CTRL_FLOW,
    INVALID_EXPR,
    INVALID_TERM,
    INVALID_FACTOR,
    INVALID_ARG_LIST,
    INVALID_TYPE,
    INVALID_OPERATOR,
    FUNC_NOT_DEF,
    FUNC_ALREADY_DEF,
    VAR_ALREADY_DEC,
    VAR_NOT_DEC,
    MISSING_FUNC_RETURN,
    INVALID_EVAL,
    EMPTY_STK_TRACE,
    INVALID_OPERAND,
    INVALID_OPERATION,
    INVALID_RETURN_VALUE,
    INVALID_ARG_TYPE,
    DIV_BY_0,
    EMPTY_ARGS
};

class ErrorHandler
{
public:
    static void error(ErrorPhase, ErrorType, std::string, int, ErrorCode);

    static std::string error_code_vec[];

private:
    typedef struct Error
    {
        ErrorType type;
        ErrorPhase phase;
        std::string context;
        int line_number;
        std::string message;
    } Error;

    static std::string print(Error);
    static std::string type_to_str(ErrorType);
    static std::string phase_to_str(ErrorPhase);
    static std::string code_to_msg(ErrorCode);
    static void exit_handler();
    static void syntax_error();
    static void runtime_error();
    static void runtime_exception();
};
