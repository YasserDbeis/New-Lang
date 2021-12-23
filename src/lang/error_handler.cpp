/*
    File: error_handler.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-22-2021
    Description: Implements the functionality of the static error methods of the Error Handler class
*/

/*/////////////////////////////////////////////////
TYPE OF ERROR
PHASE OF ERROR
LINE NUMBER
SPECIFICS
ADVICE/HINTS ?!
*/
///////////////////////////////////////////////

#include "error_handler.h"

void ErrorHandler::error(ErrorPhase err_phase, ErrorType err_type, Token token)
{
    Error err;

    err.type = err_type;
    err.phase = err_phase;
    err.token = token;
    err.print();
    // err.exit();
}