#pragma once
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/memory.h"

ASTNode *evaluate(ASTNode *node, ScopeStack *memory);