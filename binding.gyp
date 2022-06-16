{
    "targets": [
        {
            "target_name": "main",
            "sources": [
                "./src/lang/temp/main.cpp", 
                "./src/lang/src/compiler.cpp",
                "./src/lang/src/error_handler.cpp",
                "./src/lang/src/executioner.cpp",
                "./src/lang/src/expression.cpp",
                "./src/lang/src/func_def_table.cpp",
                "./src/lang/src/lexer.cpp",
                "./src/lang/src/output_handler.cpp",
                "./src/lang/src/parser.cpp",
                "./src/lang/src/scope_tree.cpp",
                "./src/lang/src/state_mgmt.cpp",
                "./src/lang/src/value.cpp",
                "./src/lang/src/nodes/expr_nodes.cpp",
                "./src/lang/src/nodes/inst_expr_nodes.cpp",
                "./src/lang/src/nodes/inst_node.cpp",
                "./src/lang/src/nodes/inst_nodes.cpp",
            ],
            "cflags" : [
			    "-std=c++17"
            ],
        }
    ]
}