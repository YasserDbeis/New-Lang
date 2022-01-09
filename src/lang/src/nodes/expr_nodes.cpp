#include "../../include/nodes/expr_nodes.h"

/* --------------------------------------------
LoadNode implementation
--------------------------------------------- */

Value LoadNode::evaluate()
{
    if (is_constant)
    {
        return value;
    }

    /* Search through scope tree for variable
        If not found, consult global hashtable of vars with global_count
        If still not found, throw an error
    */
}

/* --------------------------------------------
ParenNode implementation
--------------------------------------------- */

// Nothing to do

/* --------------------------------------------
OperatorNode implementation
--------------------------------------------- */

// Nothing to do
