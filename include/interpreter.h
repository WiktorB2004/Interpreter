#pragma once
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/memory.h"

// FIXME: Move structs into separate file

ASTNode *evaluate(ASTNode *node, ScopeStack *memory);