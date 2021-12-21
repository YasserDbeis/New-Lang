#pragma once

#include <string>
using namespace std;

class Lexer
{
private:
    int[] terminals;
    int[] tokens;

public:
    void lexical_analysis();
};