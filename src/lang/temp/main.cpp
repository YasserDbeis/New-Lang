#include "node.h"

#include <iostream>
#include "../include/lexer.h"

namespace test
{
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::String;
    using v8::Value;

    std::string get_input();

    std::string get_input()
    {
        return "BRIGGS & YASSER";
    }

    void Main(const FunctionCallbackInfo<Value> &args)
    {
        std::string input = get_input();
        Lexer lex(input);
        std::string res = lex.print_tokens();
        Isolate *isolate = args.GetIsolate();

        args.GetReturnValue().Set(String::NewFromUtf8(
            isolate, res.c_str()));
    }

    void Initialize(Local<Object> exports)
    {
        NODE_SET_METHOD(exports, "testLang", Main);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
}