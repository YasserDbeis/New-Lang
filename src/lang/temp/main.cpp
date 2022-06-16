#include <node.h>
#include <string>

#include <iostream>
#include "../include/executioner.h"

namespace main
{
    using v8::Context;
    using v8::Exception;
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
        // std::string input = get_input();
        // Lexer lex(input);
        // Executioner exec(args[0]);
        // std::string res = exec.execute_program();
        // // std::string res = lex.print_tokens();
        // Isolate *isolate = args.GetIsolate();

        // args.GetReturnValue().Set(String::NewFromUtf8(
        //     isolate, res.c_str()));

        Isolate *isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();

        // Check the number of arguments passed.
        if (args.Length() != 1)
        {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        // Check the argument types
        if (!args[0]->IsString())
        {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }

        v8::String::Utf8Value input_code_ptr(isolate, args[0]);
        std::string input_code(*input_code_ptr);

        Executioner exec(input_code);
        std::string res = exec.execute_program();

        args.GetReturnValue().Set(
            String::NewFromUtf8(isolate, res.c_str()));
    }

    void Initialize(Local<Object> exports)
    {
        NODE_SET_METHOD(exports, "testLang", Main);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
}