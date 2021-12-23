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
#include "error.h"

enum class ErrorPhase
{
    LEXICAL_ANALYSIS,
    PARSING,
    COMPILATION
};
enum class ErrorType
{
    SYNTAX_ERROR,
    RUNTIME_ERROR,
    RUNTIME_EXCEPTION
};
enum ErrorCode
{

};

class ErrorHandler
{
private:
    static void syntax_error();
    static void runtime_error();
    static void runtime_exception();

public:
    static void error(ErrorPhase, ErrorType, Token);
};
